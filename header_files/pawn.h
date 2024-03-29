#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(const QString& color);

    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // PAWN_H
