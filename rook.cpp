#include "rook.h"

Rook::Rook(const QString& color) : ChessPiece("images/rook_" + color + ".png", color) {}

QVector<QPoint> Rook::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;

    // Check available moves along rows
    for (int dr = -1; dr <= 1; dr += 2) {
        for (int i = 1; i < 8; ++i) {
            int newRow = row + dr * i;
            int newCol = col;
            if (newRow < 0 || newRow >= 8) break; // Out of bounds
            if (board[newRow][newCol]) {
                if (board[newRow][newCol]->color() != color()) {
                    moves.append(QPoint(newCol, newRow));
                }
                break; // Stop if a piece is encountered
            }
            moves.append(QPoint(newCol, newRow));
        }
    }

    // Check available moves along columns
    for (int dc = -1; dc <= 1; dc += 2) {
        for (int i = 1; i < 8; ++i) {
            int newRow = row;
            int newCol = col + dc * i;
            if (newCol < 0 || newCol >= 8) break; // Out of bounds
            if (board[newRow][newCol]) {
                if (board[newRow][newCol]->color() != color()) {
                    moves.append(QPoint(newCol, newRow));
                }
                break; // Stop if a piece is encountered
            }
            moves.append(QPoint(newCol, newRow));
        }
    }

    // Remove moves that result in check
    if(check) {
        moves = removeCheckMoves(row, col, board);
    }

    return moves;
}
