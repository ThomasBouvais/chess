#include "king.h"

King::King(const QString& color) : ChessPiece("images/king_" + color + ".png", color) {}

QVector<QPoint> King::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;
    QVector<QPoint> directions = {
        QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
        QPoint(-1, 0),                 QPoint(1, 0),
        QPoint(-1, 1), QPoint(0, 1),   QPoint(1, 1)
    };

    // Iterate through all possible directions
    for (const auto& dir : directions) {
        int newRow = row + dir.y();
        int newCol = col + dir.x();
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (!board[newRow][newCol] || board[newRow][newCol]->color() != color()) {
                QVector<QPoint> badMoves;
                // Simulate the move by copying the board and moving the king
                auto newBoard = board; // Make a copy of the board
                newBoard[newRow][newCol] = newBoard[row][col]; // Move the king to the new position
                newBoard[row][col].reset(); // Clear the original position of the king
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        auto piece = newBoard[r][c];
                        if (piece && piece->color() != color()) {
                            if (dynamic_cast<King*>(piece.get())) {
                                for (const auto& dir : directions) {
                                    auto kingMove = QPoint(c+dir.x(),r+dir.y());
                                    if (kingMove.y() >= 0 && kingMove.y() < 8 && kingMove.x() >= 0 && kingMove.x() < 8) {
                                        badMoves.append(kingMove);
                                    }
                                }
                            } else {
                                auto oppMoves = piece->getAvailableMoves(newBoard, r, c, false);
                                for (const auto& oppMove : oppMoves) {
                                    badMoves.append(oppMove);
                                }
                            }
                        }
                    }
                }
                QPoint currentMove = QPoint(newCol, newRow);
                if (!badMoves.contains(currentMove)) {
                    moves.append(currentMove);
                }
            }
        }
    }
    return moves;
}
