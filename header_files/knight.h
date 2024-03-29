#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"
#include <QPoint>
#include <QVector>

class Knight : public ChessPiece {
public:
    Knight(const QString& color);
    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // KNIGHT_H
