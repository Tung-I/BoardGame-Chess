#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "chessboard.h"
#include "chesspiece.h"
#include "chessbox.h"

class Game;
extern Game *game;
class Button;

class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = nullptr);

    //public Methods
    void drawDeadHolder(int x, int y, QColor color);
    void drawChessBoard();
    void displayMainMenu();
    void gameover(QString win_color);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //the chess picked up now
    ChessPiece *pieceToMove;

    //turn related
    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();

    //show promotion buttons
    void promotionSelect();

    //chess adding info related
    void setAddPlace(ChessBox *_box);
    ChessBox *getAddPlace();
    void setAddColor(QString _color);
    QString getAddColor();
    bool getAddMode();
    void setAddMode(bool value);

    //game public info
    ChessBox *collection[8][8];
    QGraphicsTextItem *check;

    //recording related
    void recordUpdate(ChessBox *oldBox, ChessBox *newBox, QString _name, \
                      QString _color, QString _name2, QString _color2, bool fmove1, bool fmove2);
    void recordShow();


public slots:
    void start();
    void resetBoard();
    void clearBoard();
    void again();
    void retract();

    //into add-chess mode
    void addModeWhiteSlot();
    void addModeBlackSlot();

    void addQueen();
    void addRook();
    void addKnight();
    void addBishop();
    void addKing();
    void addPawn();



private:
    QGraphicsScene *gameScene;
    QGraphicsRectItem * gameTerminal;
    QGraphicsRectItem * gameTerminal2;
    QString turn;
    ChessBoard *chess;

    //save the object should be deleted when game starting
    QList <QGraphicsItem *> listG;

    QGraphicsTextItem * turnDisplay;

    //chess-add info
    ChessBox *addPlace;
    QString addColor;

    //mode flag
    bool addMode;
    bool promotion_flag;

    //gameover window related
    QGraphicsRectItem *overWindow;
    QGraphicsRectItem *overWindow2;
    QGraphicsTextItem *overText;
    Button *againButton;
    Button *overQuitButton;

    //record
    QList <ChessBox*> oldPlace;
    QList <ChessBox*> newPlace;
    QList <QString> moveChess;
    QList <QString> moveChessSide;
    QList <QString> eatedChess;
    QList <QString> eatedChessSide;
    QList <bool> firstMove1;
    QList <bool> firstMove2;
    int listPtr;
    int moveCnt;
    QList <QGraphicsTextItem *> line;

};


#endif // GAME_H
