#include "chessboard.h"
#include "game.h"
#include "chessbox.h"
#include "QDebug"
#include "king.h"
#include "queen.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"

extern Game *game;

ChessBoard::ChessBoard(){
    setUpBlack();
    setUpWhite();
}

void ChessBoard::drawBoxes(int x,int y){
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0){
                box->setOriginalColor(Qt::white);
            }
            else{
                box->setOriginalColor(QColor(60, 60, 60, 255));
            }
            game->addToScene(box);
        }
    }
}

void ChessBoard::addChessPiece(){
    int k = 0;
    int h = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            ChessBox *box = game->collection[i][j];
            if(i < 2) {
                box->placePiece(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 5) {
                box->placePiece(white[h]);
                game->addToScene(white[h++]);
            }
        }
    }
}

void ChessBoard::setUpBlack(){
    ChessPiece *piece;
    piece = new Rook("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Queen("BLACK");
    black.append(piece);
    piece = new King("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Rook("BLACK");
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        black.append(piece);
    }
}

void ChessBoard::setUpWhite(){
    ChessPiece *piece;
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        white.append(piece);
    }
    piece = new Rook("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Queen("WHITE");
    white.append(piece);
    piece = new King("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Rook("WHITE");
    white.append(piece);
}

void ChessBoard::clearAll(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(game->collection[i][j]->getHasChessPiece()==true){
                game->collection[i][j]->currentPiece->~ChessPiece();
                game->collection[i][j]->setHasChessPiece(false);
                game->collection[i][j]->currentPiece = nullptr;
            }
        }
    }
}

void ChessBoard::resetAll(){
    clearAll();
    black.clear();
    white.clear();
    setUpBlack();
    setUpWhite();
    addChessPiece();
}

void ChessBoard::addQueen(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new Queen(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
}
void ChessBoard::addRook(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new Rook(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
};
void ChessBoard::addKnight(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new Knight(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
};
void ChessBoard::addBishop(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new Bishop(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
};
void ChessBoard::addKing(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new King(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
};
void ChessBoard::addPawn(ChessBox *_place, QString _color){
    ChessPiece *pieceToAdd = new Pawn(_color);
    pieceToAdd->firstMove = false;
    _place->placePiece(pieceToAdd);
    game->addToScene(pieceToAdd);
};
