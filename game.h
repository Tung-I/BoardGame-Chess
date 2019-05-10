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

    //current pick
    ChessPiece *pieceToMove;

    //turn
    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();

    //show promotion button
    void promotionSelect();

    //chess adding info
    void setAddPlace(ChessBox *_box);
    ChessBox *getAddPlace();
    void setAddColor(QString _color);
    QString getAddColor();
    bool getAddMode();
    void setAddMode(bool value);

    //info
    ChessBox *collection[8][8];
    QGraphicsTextItem *check;

    //record
    void recordUpdate(ChessBox *oldBox, ChessBox *newBox, QString _name, \
                      QString _color, QString _name2, QString _color2, bool fmove1, bool fmove2);
    void recordShow();


public slots:
    void start();
    void resetBoard();
    void clearBoard();
    void again();
    void retract();


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
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;

    //chess adding info
    ChessBox *addPlace;
    QString addColor;

    //mode
    bool addMode;
    bool promotion_flag;

    //gameover window
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
