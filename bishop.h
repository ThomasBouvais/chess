#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
#include <QPoint>
#include <QVector>

class Bishop : public ChessPiece {
public:
    Bishop(const QString& color);
    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // BISHOP_H
