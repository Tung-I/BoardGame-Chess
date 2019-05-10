#include "chesspiece.h"
#include "game.h"
#include <QDebug>

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
    castling_flag = false;
}

ChessPiece::~ChessPiece(){
//    qDebug()<<"delete a chesspiece"<<endl;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->getAddMode()==true)return;
    //deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = nullptr;
        return;
    }
    //if pick the wrong side && no pieceToMove
    if((game->getTurn() != this->getSide()) && (!game->pieceToMove))
        return;
    //select
    if((game->getTurn() == this->getSide()) && (!game->pieceToMove)){
        game->pieceToMove = this;
        game->pieceToMove->getCurrentBox()->setColor(Qt::red);
        //mark available box and save the loaction
        game->pieceToMove->moves();
        //boxsetting() will change box color
    }
    //has pieceToMove and pick different color
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void ChessPiece::setCurrentBox(ChessBox *box){currentBox = box;}

ChessBox *ChessPiece::getCurrentBox(){return currentBox;}

void ChessPiece::setSide( QString value){side = value;}

QString ChessPiece::getSide(){return side;}

void ChessPiece::setIsPlaced(bool value){isPlaced = value;}

bool ChessPiece::getIsPlaced(){return isPlaced;}

QList<ChessBox *> ChessPiece::moveLocation(){return location;}

void ChessPiece::decolor()
{
    int n = location.size();
    for(int i = 0; i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

bool ChessPiece::boxSetting(ChessBox *box)
{
    if(box->getHasChessPiece()) {
        box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::red);
    return false;
}

void ChessPiece::setName(QString _name){
    chess_name = _name;
}

QString ChessPiece::getName(){
    return chess_name;
}

void ChessPiece::checkCheck(){
    getAttack();
    int n = location.size();
    for(int i=0;i<n;++i){
        if(location[i]->getHasChessPiece()==true){
            if(location[i]->currentPiece->getName()=="King"){
                game->check->setVisible(true);
                return;
            }
        }
    }
    game->check->setVisible(false);
}
