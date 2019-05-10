#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"
#include "game.h"
extern Game *game;

class Rook:public ChessPiece
{
public:
    Rook(QString team, QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();
    void getAttack();

};

Rook::Rook(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setName(QString("Rook"));
    setImage();
    firstMove = true;
}

void Rook::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/image_resource/imgs/rook_w.png"));
    else
        setPixmap(QPixmap(":/image_resource/imgs/rook_b.png"));
}

void Rook::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //up
    for(int i = row-1,j = col; i >= 0 ; i--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
    //down
    for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
    //left
    for(int i = row,j = col-1; j >= 0 ; j--) {
        if(game->collection[i][j]->getChessPieceColor() == team )break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
    //Right
    for(int i = row,j = col+1; j <= 7 ; j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
}

void Rook::getAttack(){
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //up
    for(int i = row-1,j = col; i >= 0 ; i--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
    //down
    for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
    //left
    for(int i = row,j = col-1; j >= 0 ; j--) {
        if(game->collection[i][j]->getChessPieceColor() == team )break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
    //Right
    for(int i = row,j = col+1; j <= 7 ; j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(location.last()->getHasChessPiece()) break;
        }
    }
}

#endif // ROOK_H
