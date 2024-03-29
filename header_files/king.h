#ifndef KING_H
#define KING_H

#include "chesspiece.h"
#include <QPoint>
#include <QVector>

class King : public ChessPiece {
public:
    King(const QString& color);
    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // KING_H
