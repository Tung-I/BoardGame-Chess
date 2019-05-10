#ifndef QUEEN_H
#define QUEEN_H

#include "game.h"
#include "chesspiece.h"
extern Game *game;

class Queen:public ChessPiece
{
public:
    Queen(QString team,QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();
    void getAttack();

};

Queen::Queen(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setName(QString("Queen"));
    setImage();
}

void Queen::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/image_resource/imgs/queen_w.png"));
    else
        setPixmap(QPixmap(":/image_resource/imgs/queen_b.png"));
}

void Queen::moves()
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
    //upper Left
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last()) ) break;
        }
    }
    //upper right
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
    //For downward right
    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }

    //For downward left
    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
        if(game->collection[i][j]->getChessPieceColor() == team ) break;
        else{
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())) break;
        }
    }
}

void Queen::getAttack(){
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


#endif // QUEEN_H
