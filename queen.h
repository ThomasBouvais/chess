#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"
#include <QPoint>
#include <QVector>

class Queen : public ChessPiece {
public:
    Queen(const QString& color);
    QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
};

#endif // QUEEN_H
