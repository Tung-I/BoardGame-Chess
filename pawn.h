#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"
#include "game.h"
extern Game * game;

class Pawn:public ChessPiece
{
public:
    Pawn(QString team,QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();
    void getAttack();

private:

};

Pawn::Pawn(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    setName(QString("Pawn"));
    firstMove = true;
}

void Pawn::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/image_resource/imgs/pawn_w.png"));
    else
        setPixmap(QPixmap(":/image_resource/imgs/pawn_b.png"));
}

void Pawn::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    if(this->getSide() == "BLACK")  {
        if(col > 0 && row < 7 && game->collection[row+1][col-1]->getChessPieceColor() == "WHITE") {
            location.append(game->collection[row+1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row < 7 && game->collection[row+1][col+1]->getChessPieceColor() == "WHITE") {
            location.append(game->collection[row+1][col+1]);
            boxSetting(location.last());
        }
        if(row<7 && (!game->collection[row+1][col]->getHasChessPiece())) {
            location.append(game->collection[row+1][col]);
            boxSetting(location.last());
            //if first move, can move 2 boxes
            if(firstMove && !game->collection[row+2][col]->getHasChessPiece()){
                location.append(game->collection[row+2][col]);
                boxSetting(location.last());
            }
        }
    }
    else{
        if(col > 0 && row > 0 && game->collection[row-1][col-1]->getChessPieceColor() == "BLACK") {//left
            location.append(game->collection[row-1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row >  0 && game->collection[row-1][col+1]->getChessPieceColor() == "BLACK") {//right
            location.append(game->collection[row-1][col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!game->collection[row-1][col]->getHasChessPiece())) {
            location.append(game->collection[row-1][col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[row-2][col]->getHasChessPiece()){
                location.append(game->collection[row-2][col]);
                boxSetting(location.last());
            }

        }
    }
}

void Pawn::getAttack(){
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    if(this->getSide() == "BLACK")  {
        if(col > 0 && row < 7) {
            location.append(game->collection[row+1][col-1]);
        }
        if(col < 7 && row < 7) {
            location.append(game->collection[row+1][col+1]);
        }
    }
    else{
        if(col > 0 && row > 0) {
            location.append(game->collection[row-1][col-1]);
        }
        if(col < 7 && row > 0) {
            location.append(game->collection[row-1][col+1]);
        }
    }
}


#endif // PAWN_H
