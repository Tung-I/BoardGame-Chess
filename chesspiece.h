#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QGraphicsPixmapItem>
#include "chessbox.h"
#include <QGraphicsSceneMouseEvent>

class ChessBox;
class ChessPiece:public QGraphicsPixmapItem
{
public:
    ChessPiece(QString team = "",QGraphicsItem *parent = nullptr);
    ~ChessPiece();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setCurrentBox(ChessBox *box);
    ChessBox *getCurrentBox() ;

    QString getSide() ;
    void setSide( QString value);

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    //return available move
    QList <ChessBox *> moveLocation();

    virtual void setImage() = 0;
    virtual void moves() = 0;
    virtual void getAttack() = 0;

    //reset current box color
    void decolor();

    bool firstMove;
    bool castling_flag;

    //set box color and return whether the box is available
    bool boxSetting(ChessBox *box);

    //chess type
    void setName(QString _name);
    QString getName();

    //check
    void checkCheck();

protected:
    QString chess_name;
    ChessBox *currentBox;
    QString side;
    bool isPlaced;
    QList <ChessBox *> location;

};

#endif // CHESSPIECE_H
