#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>
#include <QVector>
#include <QPoint>

class ChessPiece {
public:
    ChessPiece(const QString& name, const QString& color);
    virtual ~ChessPiece() = default; // Add virtual destructor

    QString imageName() const;
    virtual QString color() const;

    virtual QVector<QPoint> getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const;
    QVector<QPoint> removeCheckMoves(int row, int col, const QVector<QVector<std::shared_ptr<ChessPiece>>>& board) const;
    QPoint getKingPosition( const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, const QString& color) const;

private:
    QString m_name;
    QString m_color;
};

#endif // CHESSPIECE_H
