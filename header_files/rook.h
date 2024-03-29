#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"
#include <QPoint>
#include <QVector>

class Rook : public ChessPiece {
public:
    Rook(const QString& color);
    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // ROOK_H
