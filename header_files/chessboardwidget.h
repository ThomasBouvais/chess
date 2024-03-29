#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "chessboard.h"

class ChessBoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoardWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    ChessBoard chessBoard;
    QPoint selectedSquare;
    bool isPieceSelected;
    QString currentPlayer;

    void selectSquare(const QPoint& position);
    void movePiece(const QPoint& newPosition);
};

#endif // CHESSBOARDWIDGET_H
