#include "chessboardwidget.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <cstdlib>

class VictoryDialog : public QDialog {
public:
    VictoryDialog(QWidget* parent = nullptr, const QString& message = "") : QDialog(parent) {
        setWindowTitle("Victory");
        setFixedSize(300, 150); // Set the fixed size of the dialog

        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* titleLabel = new QLabel("Victory", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

        QLabel* messageLabel = new QLabel(message, this);
        messageLabel->setAlignment(Qt::AlignCenter);
        messageLabel->setStyleSheet("font-size: 16px;");

        layout->addWidget(titleLabel);
        layout->addWidget(messageLabel);

        setLayout(layout);
    }
};

ChessBoardWidget::ChessBoardWidget(QWidget *parent) : QWidget(parent), isPieceSelected(false), currentPlayer("white") {
    setFixedSize(800, 800);
}

void ChessBoardWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int nbMoves = 0;
    bool isChecked = false;

    // Draw the chessboard
    int squareSize = width() / 8;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            QRect squareRect(i * squareSize, j * squareSize, squareSize, squareSize);
            QColor color = (i + j) % 2 == 0 ? Qt::white : Qt::lightGray;

            auto piece = chessBoard.pieceAt(j, i);
            // Highlight the squares behind all of the current player's pieces when no square is selected
            if (!isPieceSelected) {
                if (piece && piece->color() == currentPlayer) {
                    auto moves = piece->getAvailableMoves(chessBoard.getBoardState(), j, i, true);
                    if (!moves.isEmpty()) {
                        nbMoves = nbMoves + 1;
                        color = (i + j) % 2 == 0 ? QColor(255, 255, 225) : QColor(230, 230, 200);
                    }
                }
                // Highlight the square behind the king if in check
                if (piece && dynamic_cast<King*>(piece.get()) && piece->color() == currentPlayer) {
                    QPoint kingPosition(j, i);
                    if (isInCheck(chessBoard.getBoardState(), kingPosition.y(), kingPosition.x(), currentPlayer)) {
                        isChecked = true;
                        color = QColor(255, 150, 150); // Light red color for the king's square
                    }
                }
            }

            painter.fillRect(squareRect, color);

            // Draw the selected square in blue if a piece is selected
            if (isPieceSelected && selectedSquare == QPoint(i, j)) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(200, 200, 255));
                painter.drawRect(squareRect);
            }

            // Draw available moves in light red if a piece is selected
            if (isPieceSelected) {
                auto piece = chessBoard.pieceAt(selectedSquare.y(), selectedSquare.x());
                if (piece) {
                    auto moves = piece->getAvailableMoves(chessBoard.getBoardState(), selectedSquare.y(), selectedSquare.x(), true);
                    if (moves.contains(QPoint(i, j))) {
                        painter.setPen(Qt::NoPen);
                        painter.setBrush(QColor(255, 150, 150));
                        painter.drawRect(squareRect);
                    }
                }
            }

            // Draw pieces
            if (piece) {
                QPixmap pixmap(piece->imageName());
                painter.drawPixmap(squareRect, pixmap);
            }
        }
    }
    if (nbMoves == 0 && !isPieceSelected) {
        if (isChecked) {
            // Current player is in checkmate, so they lose
            QString winnerColor = (currentPlayer == "white") ? "Black" : "White";
            QString victoryMessage = winnerColor + " Wins";
            QTimer::singleShot(0, [=]() {
                // Display victory screen for the opposing player
                VictoryDialog victoryDialog(this, victoryMessage);
                QObject::connect(&victoryDialog, &QDialog::finished, []() {
                    std::exit(0); // Exit the program when the dialog is closed
                });
                victoryDialog.exec();
            });
        } else {
            // Display draw screen
            QTimer::singleShot(0, [=]() {
                VictoryDialog victoryDialog(this, "Draw");
                QObject::connect(&victoryDialog, &QDialog::finished, []() {
                    std::exit(0); // Exit the program when the dialog is closed
                });
                victoryDialog.exec();
            });
        }
    }
}

void ChessBoardWidget::mousePressEvent(QMouseEvent *event) {
    QPoint position = event->pos();
    int row = position.y() / (height() / 8);
    int col = position.x() / (width() / 8);

    auto piece = chessBoard.pieceAt(row, col);

    if (isPieceSelected) {
        // A piece is already selected
        if (selectedSquare == QPoint(col, row)) {
            // Clicked the same square as selected, deselect
            isPieceSelected = false;
            update();
        } else if (piece && piece->color() == currentPlayer) {
            // Clicked on another piece of the same color, swap selection
            selectedSquare = QPoint(col, row);
            update();
        } else {
            // Clicked on an empty square or opponent's piece, check for valid move
            auto moves = chessBoard.pieceAt(selectedSquare.y(), selectedSquare.x())->getAvailableMoves(chessBoard.getBoardState(), selectedSquare.y(), selectedSquare.x(), true);
            if (moves.contains(QPoint(col, row))) {
                // Valid move, move the piece
                movePiece(QPoint(col, row));
            } else {
                // Invalid move, deselect
                isPieceSelected = false;
                update();
            }
        }
    } else {
        // No piece is selected
        if (piece && piece->color() == currentPlayer) {
            // Clicked on a piece of the current player's color, select
            selectedSquare = QPoint(col, row);
            isPieceSelected = true;
            update();
        }
    }
}

void ChessBoardWidget::selectSquare(const QPoint& position) {
    selectedSquare = position;
    isPieceSelected = true;
    update();
}

void ChessBoardWidget::movePiece(const QPoint& newPosition) {
    // Update the board state
    chessBoard.movePiece(selectedSquare, newPosition);

    // Check if a pawn reached the opposite side and promote it to a queen
    auto piece = chessBoard.pieceAt(newPosition.y(), newPosition.x());
    if (piece && dynamic_cast<Pawn*>(piece.get())) {
        QString color = piece->color();
        if ((color == "white" && newPosition.y() == 0) || (color == "black" && newPosition.y() == 7)) {
            // Promote the pawn to a queen
            chessBoard.addPiece(std::make_shared<Queen>(color), newPosition.y(), newPosition.x());
        }
    }

    // Switch player
    currentPlayer = (currentPlayer == "white") ? "black" : "white";

    isPieceSelected = false;

    update();
}
