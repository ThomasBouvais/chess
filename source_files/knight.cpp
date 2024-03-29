#include "knight.h"

Knight::Knight(const QString& color) : ChessPiece("images/knight_" + color + ".png", color) {}

QVector<QPoint> Knight::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;

    // Define all possible knight moves
    QVector<QPoint> knightMoves = {
        QPoint(-2, -1), QPoint(-2, 1), QPoint(-1, -2), QPoint(-1, 2),
        QPoint(1, -2), QPoint(1, 2), QPoint(2, -1), QPoint(2, 1)
    };

    // Iterate through each possible move
    for (const auto& move : knightMoves) {
        int newRow = row + move.y();
        int newCol = col + move.x();

        // Check if the new position is within the board bounds and not occupied by a friendly piece
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (!board[newRow][newCol] || board[newRow][newCol]->color() != color())) {
            moves.append(QPoint(newCol, newRow));
        }
    }

    // Remove moves that result in check
    if(check) {
        moves = removeCheckMoves(row, col, board);
    }

    return moves;
}
