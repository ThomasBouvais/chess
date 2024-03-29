#include "bishop.h"

Bishop::Bishop(const QString& color) : ChessPiece("images/bishop_" + color + ".png", color) {}

QVector<QPoint> Bishop::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;

    // Define directions: up-left, up-right, down-left, down-right
    QVector<QPoint> directions = {QPoint(-1, -1), QPoint(-1, 1), QPoint(1, -1), QPoint(1, 1)};

    // Iterate through each direction
    for (const auto& dir : directions) {
        int newRow = row + dir.x();
        int newCol = col + dir.y();

        // Continue in the same direction until we encounter a piece or reach the board's edge
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && (!board[newRow][newCol] || board[newRow][newCol]->color() != color())) {
            moves.append(QPoint(newCol, newRow));

            // If the square is occupied by an opponent's piece, stop further movement in this direction
            if (board[newRow][newCol] && board[newRow][newCol]->color() != color()) {
                break;
            }

            // Move to the next square in the same direction
            newRow += dir.x();
            newCol += dir.y();
        }
    }

    // Remove moves that result in check
    if(check) {
        moves = removeCheckMoves(row, col, board);
    }

    return moves;
}
