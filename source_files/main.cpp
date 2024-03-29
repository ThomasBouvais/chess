#include <QApplication>
#include "chessboardwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ChessBoardWidget chessBoard;
    chessBoard.show();

    return app.exec();
}
