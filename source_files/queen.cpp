#include "queen.h"

Queen::Queen(const QString& color) : ChessPiece("images/queen_" + color + ".png", color) {}

QVector<QPoint> Queen::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    QVector<QPoint> moves;

    // Calculate available moves like a rook
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; // Skip the current position
            for (int i = 1; i < 8; ++i) {
                int newRow = row + dr * i;
                int newCol = col + dc * i;
                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) break; // Out of bounds
                if (board[newRow][newCol]) {
                    if (board[newRow][newCol]->color() != color()) {
                        moves.append(QPoint(newCol, newRow));
                    }
                    break; // Stop if a piece is encountered
                }
                moves.append(QPoint(newCol, newRow));
            }
        }
    }

    // Calculate available moves like a bishop
    for (int dr = -1; dr <= 1; dr += 2) {
        for (int dc = -1; dc <= 1; dc += 2) {
            for (int i = 1; i < 8; ++i) {
                int newRow = row + dr * i;
                int newCol = col + dc * i;
                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) break; // Out of bounds
                if (board[newRow][newCol]) {
                    if (board[newRow][newCol]->color() != color()) {
                        moves.append(QPoint(newCol, newRow));
                    }
                    break; // Stop if a piece is encountered
                }
                moves.append(QPoint(newCol, newRow));
            }
        }
    }

    // Remove moves that result in check
    if(check) {
        moves = removeCheckMoves(row, col, board);
    }

    return moves;
}
