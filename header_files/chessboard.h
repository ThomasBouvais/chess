#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chesspiece.h"
#include <array>
#include <memory>
#include <QPoint>
#include <QVector>

class ChessBoard {
public:
    ChessBoard();

    std::shared_ptr<ChessPiece> pieceAt(int row, int col) const;
    void addPiece(std::shared_ptr<ChessPiece> piece, int row, int col);
    void movePiece(const QPoint& from, const QPoint& to);
    QVector<QVector<std::shared_ptr<ChessPiece>>> getBoardState() const;
    QPoint getKingPosition(const QString& color) const;
    QPoint getKingPosition( const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, const QString& color) const;

private:
    std::array<std::array<std::shared_ptr<ChessPiece>, 8>, 8> board;
};

bool isInCheck(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int kingRow, int kingCol, const QString& kingColor);

#endif // CHESSBOARD_H
