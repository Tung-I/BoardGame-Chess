#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.h"

class ChessBoard
{
public:
    ChessBoard();

    void drawBoxes(int x, int y);
    void setUpWhite();
    void setUpBlack();
    void addChessPiece();

    void clearAll();
    void resetAll();

    void addQueen(ChessBox *_place, QString _color);
    void addRook(ChessBox *_place, QString _color);
    void addKnight(ChessBox *_place, QString _color);
    void addBishop(ChessBox *_place, QString _color);
    void addKing(ChessBox *_place, QString _color);
    void addPawn(ChessBox *_place, QString _color);

private:
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;
};

#endif // CHESSBOARD_H
