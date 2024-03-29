#include "pawn.h"

Pawn::Pawn(const QString& color) : ChessPiece("images/pawn_" + color + ".png", color) {}

QVector<QPoint> Pawn::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;

    int direction = (color() == "white") ? -1 : 1;

    // Check if the square directly in front is empty
    if (row + direction >= 0 && row + direction < 8 && !board[row + direction][col]) {
        moves.append(QPoint(col, row + direction));

        // Check if it's the pawn's first move and the square two steps ahead is also empty
        if ((row == 6 && direction == -1) || (row == 1 && direction == 1) && !board[row + 2 * direction][col] && !board[row + direction][col]) {
            moves.append(QPoint(col, row + 2 * direction));
        }
    }

    // Check for diagonal captures
    if (col - 1 >= 0 && row + direction >= 0 && row + direction < 8 &&
        board[row + direction][col - 1] && board[row + direction][col - 1]->color() != color()) {
        moves.append(QPoint(col - 1, row + direction));
    }
    if (col + 1 < 8 && row + direction >= 0 && row + direction < 8 &&
        board[row + direction][col + 1] && board[row + direction][col + 1]->color() != color()) {
        moves.append(QPoint(col + 1, row + direction));
    }

    // Remove moves that result in check
    if(check) {
        moves = removeCheckMoves(row, col, board);
    }

    return moves;
}
