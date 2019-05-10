#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
#include "game.h"

extern Game *game;
class Bishop:public ChessPiece
{
public:
    Bishop(QString team,QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();
    void getAttack();
};

Bishop::Bishop(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setName(QString("Bishop"));
    setImage();
}

void Bishop::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/image_resource/imgs/bishop_w.png"));
    else
        setPixmap(QPixmap(":/image_resource/imgs/bishop_b.png"));
}

void Bishop::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    //up Left
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last()) ) break;
        }
    }
    //up right
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
    //down right
    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }

    //down left
    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
}

void Bishop::getAttack(){
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    //upper Left
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
    //upper right
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
    //For downward right
    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }

    //For downward left
    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
}

#endif // BISHOP_H
