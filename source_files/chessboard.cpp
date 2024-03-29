#include "chessboard.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <QPoint>

ChessBoard::ChessBoard() {
    // Initialize the board with pieces
    // Black pieces
    board[0][0] = std::make_shared<Rook>("black");
    board[0][1] = std::make_shared<Knight>("black");
    board[0][2] = std::make_shared<Bishop>("black");
    board[0][3] = std::make_shared<Queen>("black");
    board[0][4] = std::make_shared<King>("black");
    board[0][5] = std::make_shared<Bishop>("black");
    board[0][6] = std::make_shared<Knight>("black");
    board[0][7] = std::make_shared<Rook>("black");
    for (int i = 0; i < 8; ++i) {
        board[1][i] = std::make_shared<Pawn>("black");
    }

    // White pieces
    board[7][0] = std::make_shared<Rook>("white");
    board[7][1] = std::make_shared<Knight>("white");
    board[7][2] = std::make_shared<Bishop>("white");
    board[7][3] = std::make_shared<Queen>("white");
    board[7][4] = std::make_shared<King>("white");
    board[7][5] = std::make_shared<Bishop>("white");
    board[7][6] = std::make_shared<Knight>("white");
    board[7][7] = std::make_shared<Rook>("white");
    for (int i = 0; i < 8; ++i) {
        board[6][i] = std::make_shared<Pawn>("white");
    }
}

std::shared_ptr<ChessPiece> ChessBoard::pieceAt(int row, int col) const {
    return board[row][col];
}

void ChessBoard::addPiece(std::shared_ptr<ChessPiece> piece, int row, int col) {
    board[row][col] = piece;
}

void ChessBoard::movePiece(const QPoint& from, const QPoint& to) {
    auto piece = board[from.y()][from.x()]; // Get the piece at 'from' position
    board[from.y()][from.x()] = nullptr;    // Remove the piece from 'from' position
    board[to.y()][to.x()] = piece;          // Place the piece at 'to' position
}

QVector<QVector<std::shared_ptr<ChessPiece>>> ChessBoard::getBoardState() const {
    QVector<QVector<std::shared_ptr<ChessPiece>>> state;
    state.reserve(8);
    for (int i = 0; i < 8; ++i) {
        QVector<std::shared_ptr<ChessPiece>> row;
        row.reserve(8);
        for (int j = 0; j < 8; ++j) {
            row.push_back(board[i][j]);
        }
        state.push_back(row);
    }
    return state;
}

bool isInCheck(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int kingRow, int kingCol, const QString& kingColor) {
    QVector<QPoint> kingDirections = {
        QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
        QPoint(-1, 0),                 QPoint(1, 0),
        QPoint(-1, 1), QPoint(0, 1),   QPoint(1, 1)
    };

    for (const auto& dir : kingDirections) {
        int newRow = kingRow + dir.y();
        int newCol = kingCol + dir.x();
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            auto piece = board[newCol][newRow];
            if (piece && piece->color() != kingColor && dynamic_cast<King*>(piece.get())) {
                return true; // King is next to another king
            }
        }
    }

    // Test for every opponent's piece if the king at (kingRow, kingCol) is in check
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = board[row][col];
            if (piece && piece->color() != kingColor && !dynamic_cast<King*>(piece.get())) {
                auto moves = piece->getAvailableMoves(board, row, col, false);
                if (moves.contains(QPoint(kingRow, kingCol))) {
                    return true; // King is in check
                }
            }
        }
    }

    return false; // King is not in check
}

QPoint ChessBoard::getKingPosition(const QString& color) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = board[row][col];
            if (piece && piece->color() == color && dynamic_cast<King*>(piece.get())) {
                return QPoint(col, row); // Return king's position
            }
        }
    }
    return QPoint(-1, -1); // King not found (shouldn't happen in a valid game)
}
