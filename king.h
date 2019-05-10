#ifndef KING_H
#define KING_H

#include <QDebug>
#include "chesspiece.h"
#include "game.h"
#include "chessbox.h"

extern Game *game;

class King:public ChessPiece
{
public:
    King(QString team,QGraphicsItem *parent = nullptr);
    void setImage();
    void findUnSafeLocation();
    void moves();
    void getAttack();
    bool castlingAttackCheck(ChessBox *kingPos);
};

King::King(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setName(QString("King"));
    setImage();
    firstMove = true;
}

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/image_resource/imgs/king_w.png"));
    else
        setPixmap(QPixmap(":/image_resource/imgs/king_b.png"));
}

bool King::castlingAttackCheck(ChessBox *kingPos){
    ChessBox *pos1 = nullptr;
    ChessBox *pos2 = nullptr;
    ChessBox *pos3 = nullptr;
    ChessBox *pos4 = nullptr;
    if(kingPos==game->collection[7][2]){
        pos1 = game->collection[7][4];
        pos2 = game->collection[7][3];
        pos3 = game->collection[7][2];
        pos4 = game->collection[7][0];
    }
    else if(kingPos==game->collection[7][6]){
        pos1 = game->collection[7][4];
        pos2 = game->collection[7][5];
        pos3 = game->collection[7][6];
        pos4 = game->collection[7][7];
    }
    else if(kingPos==game->collection[0][2]){
        pos1 = game->collection[0][4];
        pos2 = game->collection[0][3];
        pos3 = game->collection[0][2];
        pos4 = game->collection[0][0];
    }
    else if(kingPos==game->collection[0][6]){
        pos1 = game->collection[0][4];
        pos2 = game->collection[0][5];
        pos3 = game->collection[0][6];
        pos4 = game->collection[0][7];
    }
    else return false;
    //if any of pos is attacked
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            if(game->collection[i][j]->getHasChessPiece()==true){
                //if different color
                if(game->collection[i][j]->currentPiece->getSide()!=\
                        game->pieceToMove->getSide()){
                    //try move
                    game->collection[i][j]->currentPiece->getAttack();
                    QList <ChessBox *> movLoc = game->collection[i][j]->currentPiece->moveLocation();
                    int n = movLoc.size();
                    bool return_check = false;
                    for(int k=0; k<n; k++) {
                        if(movLoc[k] == pos1 || movLoc[k] == pos2\
                                || movLoc[k] == pos3 || movLoc[k] == pos4){
                            return_check = true;
                            break;
                        }
                    }
                    if(return_check)return true;
                }
            }
        }
    }
    return false;
}

void King::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //castling
    if(firstMove==true){
        ChessPiece *_rook = nullptr;
        //if chess is there
        if(getSide()=="WHITE"){
            //white left side
            if(game->collection[7][0]->getHasChessPiece()==true){
                _rook = game->collection[7][0]->currentPiece;
                if(_rook->getName()=="Rook" && _rook->firstMove==true){
                    //if empty
                    if(game->collection[7][1]->getHasChessPiece()==false &&\
                            game->collection[7][2]->getHasChessPiece()==false &&\
                            game->collection[7][3]->getHasChessPiece()==false){
                        if(castlingAttackCheck(game->collection[7][2])==false){
                            location.append(game->collection[7][2]);
                            location.last()->setColor(Qt::red);
                            location.last()->castling_flag = true;
                        }
                    }
                }
            }
            //white right side
            if(game->collection[7][7]->getHasChessPiece()==true){
                _rook = game->collection[7][7]->currentPiece;
                if(_rook->getName()=="Rook" && _rook->firstMove==true){
                    //if empty
                    if(game->collection[7][6]->getHasChessPiece()==false &&\
                            game->collection[7][5]->getHasChessPiece()==false){
                        if(castlingAttackCheck(game->collection[7][6])==false){
                            location.append(game->collection[7][6]);
                            location.last()->setColor(Qt::red);
                            location.last()->castling_flag = true;
                        }
                    }
                }
            }
        }
        else if(getSide()=="BLACK"){
            //black left side
            if(game->collection[0][0]->getHasChessPiece()==true){
                _rook = game->collection[0][0]->currentPiece;
                if(_rook->getName()=="Rook" && _rook->firstMove==true){
                    //if empty
                    if(game->collection[0][1]->getHasChessPiece()==false &&\
                            game->collection[0][2]->getHasChessPiece()==false &&\
                            game->collection[0][3]->getHasChessPiece()==false){
                        if(castlingAttackCheck(game->collection[0][2])==false){
                            location.append(game->collection[0][2]);
                            location.last()->setColor(Qt::red);
                            location.last()->castling_flag = true;
                        }
                    }
                }
            }
            //black right side
            if(game->collection[0][7]->getHasChessPiece()==true){
                _rook = game->collection[0][7]->currentPiece;
                if(_rook->getName()=="Rook" && _rook->firstMove==true){
                    //if empty
                    if(game->collection[0][6]->getHasChessPiece()==false &&\
                            game->collection[0][5]->getHasChessPiece()==false){
                        if(castlingAttackCheck(game->collection[0][6])==false){
                            location.append(game->collection[0][6]);
                            location.last()->setColor(Qt::red);
                            location.last()->castling_flag = true;
                        }
                    }
                }
            }
        }
    }
    //up left
    if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col-1]);
        game->collection[row-1][col-1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //up right
    if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col+1]);
        game->collection[row-1][col+1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //up
    if(row>0 && !(game->collection[row-1][col]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col]);
        game->collection[row-1][col]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //down
    if(row<7 && !(game->collection[row+1][col]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col]);
        game->collection[row+1][col]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //left
    if(col>0 && !(game->collection[row][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row][col-1]);
        game->collection[row][col-1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //right
    if(col<7 && !(game->collection[row][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row][col+1]);
        game->collection[row][col+1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //down left
    if(col > 0 && row < 7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col-1]);
        game->collection[row+1][col-1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }
    //down right
    if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col+1]);
        game->collection[row+1][col+1]->setColor(Qt::red);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::red);
        }
    }

}

void King::getAttack(){
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //up left
    if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col-1]);
    }
    //up right
    if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col+1]);
    }
    //up
    if(row>0 && !(game->collection[row-1][col]->getChessPieceColor() == team)){
        location.append(game->collection[row-1][col]);
    }
    //down
    if(row<7 && !(game->collection[row+1][col]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col]);
    }
    //left
    if(col>0 && !(game->collection[row][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row][col-1]);
    }
    //right
    if(col<7 && !(game->collection[row][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row][col+1]);
    }
    //down left
    if(col > 0 && row < 7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col-1]);
    }
    //down right
    if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)){
        location.append(game->collection[row+1][col+1]);
    }

}


#endif // KING_H
