#include "chessbox.h"
#include "game.h"
#include "chesspiece.h"
#include "button.h"
#include <QDebug>

extern Game *game;

ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent){
    //create the Square Chess Boxes
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = nullptr;
    castling_flag = false;
}

ChessBox::~ChessBox(){
//    qDebug()<<"delete a chessbox"<<endl;
}

void ChessBox::setColor(QColor color){brush.setColor(color);setBrush(color);}
void ChessBox::resetOriginalColor(){setColor(originalColor);}
void ChessBox::setOriginalColor(QColor value){originalColor = value;setColor(originalColor);}

bool ChessBox::getHasChessPiece(){return hasChessPiece;}
void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}

QString ChessBox::getChessPieceColor(){return chessPieceColor;}
void ChessBox::setChessPieceColor(QString value){chessPieceColor = value;}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{   //info of the chesspiece which is eated
    QString eatedName = "NONE";
    QString eatedColor = "NONE";
    bool fmove1 = false;
    bool fmove2 = false;
    //if in add mode
    if(game->getAddMode()==true){
        if(getHasChessPiece()==true)return;
        if(game->getAddPlace()==this){
            resetOriginalColor();
            game->setAddMode(false);
            game->setAddPlace(nullptr);
            game->setAddColor("NONE");
            return;
        }
        game->setAddPlace(this);
        setColor(QColor(41, 148, 255, 255));
        return;
    }
    //deselect
    if(currentPiece == game->pieceToMove && currentPiece){
        currentPiece->mousePressEvent(event);
        return;
    }
    //if pieceToMove has been selected
    if(game->pieceToMove){
        //make sure this box is in the move zone
        QList <ChessBox *> movLoc = game->pieceToMove->moveLocation();
        int check = 0;
        int n = movLoc.size();
        for(int i=0; i<n; i++) {
            if(movLoc[i] == this) {
                check++;
            }
        }
        if(check == 0) return;
        //if has chess in this box
        if(this->getHasChessPiece()){
            //if same side
            if(this->currentPiece->getSide() == game->pieceToMove->getSide())
                return;
            //if different side, eat it
            else{
                //record
                eatedName = currentPiece->getName();
                eatedColor = currentPiece->getSide();
                fmove2 = this->currentPiece->firstMove;
                //if the king is eated
                if(currentPiece->getName()=="King"){
                    game->gameover(game->pieceToMove->getSide());
                }
                //delete the chess
                this->setChessPieceColor("NONE");
                this->setHasChessPiece(false);
                this->currentPiece->~ChessPiece();
            }
        }
        //no chess in this box now
        //save record info 
        fmove1 = game->pieceToMove->firstMove;
        game->recordUpdate(game->pieceToMove->getCurrentBox(), this, \
                           game->pieceToMove->getName(), game->pieceToMove->getSide(),\
                           eatedName, eatedColor, fmove1, fmove2);
        game->recordShow();
        //leave the old place and locate in the new place
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->getCurrentBox()->setHasChessPiece(false);
        game->pieceToMove->getCurrentBox()->currentPiece = nullptr;
        game->pieceToMove->decolor();
        game->pieceToMove->firstMove = false;
        this->placePiece(game->pieceToMove);
        game->pieceToMove = nullptr;
        //check check
        currentPiece->checkCheck();
        //if this box is castling box
        if(castling_flag==true && currentPiece->getName()==QString("King")){
            //move rook
            if(colLoc==2){
                ChessPiece *rook_piece = game->collection[rowLoc][0]->currentPiece;
                //reset piece
                rook_piece->firstMove = false;
                game->collection[rowLoc][3]->placePiece(rook_piece);
                //reset box
                game->collection[rowLoc][0]->setHasChessPiece(false);
                game->collection[rowLoc][0]->currentPiece = nullptr;
            }
            else if(colLoc==6){
                ChessPiece *rook_piece = game->collection[rowLoc][7]->currentPiece;
                //reset piece
                rook_piece->firstMove = false;
                game->collection[rowLoc][5]->placePiece(rook_piece);
                //reset box
                game->collection[rowLoc][7]->setHasChessPiece(false);
                game->collection[rowLoc][7]->currentPiece = nullptr;
            }
        }
        castling_flag = false;
        //if promote
        if(this->currentPiece->getName()==QString("Pawn") && \
                (rowLoc==0 || rowLoc==7)){
            //delete
            QString _color = this->currentPiece->getSide();
            this->setChessPieceColor("NONE");
            this->setHasChessPiece(false);
            this->currentPiece->~ChessPiece();
            //send info to game, open select menu
            game->setAddPlace(this);
            game->setAddColor(_color);
            game->promotionSelect();
        }
        //changing turn
        game->changeTurn();
    }
    //if pieceToMove has not selected
    else{
        //if this box has chesspiece && turn is correct
        if(getHasChessPiece()==true && chessPieceColor==game->getTurn()){
            game->pieceToMove = currentPiece;
            game->pieceToMove->getCurrentBox()->setColor(Qt::red);
            game->pieceToMove->moves();  //boxsetting() will change box color
        }
        else return;
    }
}

void ChessBox::placePiece(ChessPiece *piece){
    piece->setPos(x()+50 - piece->pixmap().width()/2  ,y()+50 - piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

