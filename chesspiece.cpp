#include "chesspiece.h"
#include "chessboard.h"
#include "king.h"

ChessPiece::ChessPiece(const QString& name, const QString& color) : m_name(name), m_color(color) {}

QString ChessPiece::imageName() const {
    return m_name;
}

QString ChessPiece::color() const {
    return m_color;
}

QVector<QPoint> ChessPiece::getAvailableMoves(const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, int row, int col, bool check) const {
    // Default implementation returns an empty vector (no available moves)
    return QVector<QPoint>();
}

//QVector<QPoint> ChessPiece::removeCheckMoves(int row, int col, const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, const QPoint& kingPosition) const{
QVector<QPoint> ChessPiece::removeCheckMoves(int row, int col, const QVector<QVector<std::shared_ptr<ChessPiece>>>& board) const{
    QVector<QPoint> validMoves;
    QPoint kingPosition = getKingPosition(board, board[row][col]->color());

    // Get all available moves for the piece
    QVector<QPoint> moves = getAvailableMoves(board, row, col, false);

    // Filter out moves that result in the king being in check
    for (const auto& move : moves) {
        // Simulate the move
        auto newBoard = board;
        newBoard[row][col].reset(); // Clear the current position
        newBoard[move.y()][move.x()] = std::make_shared<ChessPiece>(*this); // Move the piece

        // Check if the king is in check after the move
        bool isInCheck = ::isInCheck(newBoard,kingPosition.x(), kingPosition.y(), color());

        // If the king is not in check after the move, add it to validMoves
        if (!isInCheck) {
            validMoves.push_back(move);
        }
    }

    return validMoves;
}

QPoint ChessPiece::getKingPosition( const QVector<QVector<std::shared_ptr<ChessPiece>>>& board, const QString& color) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = board[row][col];
            if (piece && piece->color() == color && dynamic_cast<King*>(piece.get())) {
                return QPoint(col, row); // Return king's position
            }
        }
    }
    return QPoint(-1, -1); // King not found (shouldn't happen in a valid game)
}
