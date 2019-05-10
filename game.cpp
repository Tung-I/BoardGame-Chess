#include "game.h"
#include "button.h"
#include <QPixmap>
#include <QDebug>



Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);

    //Making the view
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBackgroundBrush(brush);
    pieceToMove = nullptr;

    //game terminal
    gameTerminal = new QGraphicsRectItem();
    gameTerminal->setRect(0, 0, 450, 400);
    gameTerminal->setPos(875, 25);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 255));
    gameTerminal->setBrush(brush);
    gameTerminal->setZValue(2);

    gameTerminal2 = new QGraphicsRectItem();
    gameTerminal2->setRect(0, 0, 470, 420);
    gameTerminal2->setPos(865, 15);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(143, 143, 143, 255));
    gameTerminal2->setBrush(brush);
    gameTerminal2->setZValue(1);

    //create turn text
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setDefaultTextColor(QColor(41, 255, 41, 255));
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");
    turnDisplay->setPos(875+gameTerminal->rect().width()/2 - \
                        turnDisplay->boundingRect().width()/2, 35);
    turnDisplay->setZValue(3);

    //create check text
    check = new QGraphicsTextItem();
    check->setZValue(3);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",25));
    check->setPlainText("CHECK!");
    check->setPos(875+gameTerminal->rect().width()/2 - \
                  check->boundingRect().width()/2,70);
    check->setVisible(false);

    //create record text
    QGraphicsTextItem *temp;
    for(int i=0;i<8;++i){
        temp = new QGraphicsTextItem();
        line.append(temp);
        line[i]->setZValue(3);
        line[i]->setDefaultTextColor(QColor(41, 255, 41, 255));
        line[i]->setFont(QFont("",18));
        line[i]->setPlainText(" ");
        line[i]->setVisible(false);
        addToScene(line[i]);
    }

    int xPos = int(880);
    line[0]->setPos(xPos,120);
    line[1]->setPos(xPos,155);
    line[2]->setPos(xPos,190);
    line[3]->setPos(xPos,225);
    line[4]->setPos(xPos,260);
    line[5]->setPos(xPos,295);
    line[6]->setPos(xPos,330);
    line[7]->setPos(xPos,365);

    //gameover window
    overWindow = new QGraphicsRectItem();
    overWindow->setRect(0, 0, 450, 400);
    overWindow->setPos(700 - 225, 250);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 255));
    overWindow->setBrush(brush);
    overWindow->setZValue(11);

    overWindow2 = new QGraphicsRectItem();
    overWindow2->setRect(0, 0, 470, 420);
    overWindow2->setPos(700 - 235, 240);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(143, 143, 143, 255));
    overWindow2->setBrush(brush);
    overWindow2->setZValue(10);

    overText = new QGraphicsTextItem();
    overText->setDefaultTextColor(QColor(41, 255, 41, 255));
    overText->setFont(QFont("",40));
    overText->setPlainText(" WIN!");
    overText->setPos(700-overText->boundingRect().width(), 275);
    overText->setZValue(12);

    againButton = new Button("Play Again");
    againButton->setPos(700-againButton->rect().width()/2, 375);
    againButton->setZValue(12);
    connect(againButton, SIGNAL(clicked()) , this, SLOT(again()));

    overQuitButton = new Button("Quit");
    overQuitButton->setPos(700-overQuitButton->rect().width()/2, 475);
    overQuitButton->setZValue(12);
    connect(overQuitButton, SIGNAL(clicked()) , this, SLOT(close()));
    //show
    addToScene(overWindow);
    addToScene(overWindow2);
    addToScene(overText);
    addToScene(againButton);
    addToScene(overQuitButton);
    //hide
    overWindow->setVisible(false);
    overWindow2->setVisible(false);
    overText->setVisible(false);
    againButton->setVisible(false);
    overQuitButton->setVisible(false);

    //initial info
    setTurn("WHITE");
    addPlace = nullptr;
    addColor = "NONE";
    addMode = false;
    promotion_flag = false;
    listPtr = -1;
    moveCnt = 0;


}


void Game::drawChessBoard()
{
    chess = new ChessBoard();
    chess->drawBoxes(10,25);
}


void Game::addToScene(QGraphicsItem *item){gameScene->addItem(item);}
void Game::removeFromScene(QGraphicsItem *item){gameScene->removeItem(item);}

QString Game::getTurn(){return turn;}
void Game::setTurn(QString value){turn = value;}
void Game::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());
}

ChessBox *Game::getAddPlace(){return addPlace;}
void Game::setAddPlace(ChessBox *_box){addPlace = _box;}

QString Game::getAddColor(){return addColor;}
void Game::setAddColor(QString _color){addColor = _color;}

bool Game::getAddMode(){return addMode;}
void Game::setAddMode(bool value){addMode = value;}

void Game::displayMainMenu()
{
    //create background
    QGraphicsRectItem *background = new QGraphicsRectItem();
    background->setRect(0, 0, 1400, 900);
    background->setPos(0, 0);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    background->setBrush(brush);
    addToScene(background);
    listG.append(background);
    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("AlphaChess");
    QGraphicsTextItem *verText = new QGraphicsTextItem("ver 8.7");
    QFont titleFont("arial" , 50);
    QFont verFont("arial" , 15);
    titleFont.setBold(true);
    titleFont.setFamily("Ubuntu");
    verFont.setItalic(true);
    titleText->setFont(titleFont);
    verText->setFont(verFont);
    int xPos = int(width()/2 - titleText->boundingRect().width()/2);
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    xPos = int(width()/2 - verText->boundingRect().width()/2);
    yPos = 250;
    verText->setPos(xPos, yPos);
    titleText->setZValue(5);
    verText->setZValue(5);
    addToScene(titleText);
    addToScene(verText);
    listG.append(titleText);
    listG.append(verText);
    //create figure
    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/image_resource/imgs/doooog.jpg"));
    p1->setPos(350,100);
    p1->setScale(1.2);
    p1->setZValue(2);
    addToScene(p1);
    listG.append(p1);
    QGraphicsPixmapItem *p2 = new QGraphicsPixmapItem();
    p2->setPixmap(QPixmap(":/image_resource/imgs/doooog2.jpg"));
    p2->setPos(1050-p2->boundingRect().width()-40,100);
    p2->setScale(1.2);
    p2->setZValue(2);
    addToScene(p2);
    listG.append(p2);
    QGraphicsPixmapItem *p3 = new QGraphicsPixmapItem();
    p3->setPixmap(QPixmap(":/image_resource/imgs/catdiscuss.png"));
    p3->setPos(700- p3->boundingRect().width()/2-20, 550);
    p3->setScale(1.2);
    p3->setZValue(2);
    addToScene(p3);
    listG.append(p3);
    QGraphicsPixmapItem *p4 = new QGraphicsPixmapItem();
    p4->setPixmap(QPixmap(":/image_resource/imgs/catcross.png"));
    p4->setPos(700-p4->boundingRect().width(), 30);
    p4->setScale(2);
    p4->setZValue(2);
    addToScene(p4);
    listG.append(p4);
    QGraphicsPixmapItem *p5 = new QGraphicsPixmapItem();
    p5->setPixmap(QPixmap(":/image_resource/imgs/doooog2.png"));
    p5->setPos(0, 200);
    p5->setScale(3.3);
    p5->setZValue(3);
    addToScene(p5);
    listG.append(p5);
    QGraphicsPixmapItem *p6 = new QGraphicsPixmapItem();
    p6->setPixmap(QPixmap(":/image_resource/imgs/catleave.png"));
    p6->setPos(900, 350);
    p6->setScale(2);
    p6->setZValue(2);
    addToScene(p6);
    listG.append(p6);
    QGraphicsPixmapItem *p7 = new QGraphicsPixmapItem();
    p7->setPixmap(QPixmap(":/image_resource/imgs/uwaaaaa.png"));
    p7->setPos(0, 150);
    p7->setScale(2);
    p7->setZValue(3);
    addToScene(p7);
    listG.append(p7);
    QGraphicsPixmapItem *p8 = new QGraphicsPixmapItem();
    p8->setPixmap(QPixmap(":/image_resource/imgs/aaaaa.png"));
    p8->setPos(0, 200);
    p8->setScale(2);
    p8->setZValue(3);
    addToScene(p8);
    listG.append(p8);
    //create Button
    Button * playButton = new Button("Player  vs  Player");
    int pxPos = int(width()/2 - playButton->boundingRect().width()/2);
    int pyPos = 400;
    playButton->setPos(pxPos,pyPos);
    playButton->setZValue(2);
    connect(playButton, SIGNAL(clicked()) , this, SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);
    Button * quitButton = new Button("Quit");
    int qxPos = int(width()/2 - quitButton->boundingRect().width()/2);
    int qyPos = 480;
    quitButton->setPos(qxPos,qyPos);
    quitButton->setZValue(2);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    addToScene(quitButton);
    listG.append(quitButton);
    //draw board
    drawChessBoard();
}


void Game::start()
{
    int n = listG.size();
    for(int i =0; i < n; i++){
        removeFromScene(listG[i]);
    }
    addToScene(turnDisplay);
    addToScene(gameTerminal2);
    addToScene(gameTerminal);
    addToScene(check);
    chess->addChessPiece();

    //create game button
    QBrush brush;
    Button * quit_button = new Button("Quit");
    quit_button->setPos(875,775);
    connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));
    addToScene(quit_button);

    Button * reset_button = new Button("Reset");
    reset_button->setPos(875,725);
    connect(reset_button, SIGNAL(clicked()), this, SLOT(resetBoard()));
    addToScene(reset_button);

    Button * clear_button = new Button("Clear");
    clear_button->setPos(875,675);
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clearBoard()));
    addToScene(clear_button);

    Button * retract_button = new Button("Retract");
    retract_button->setPos(875,625);
    connect(retract_button, SIGNAL(clicked()), this, SLOT(retract()));
    addToScene(retract_button);

    Button * add_button_white = new Button("Box Select", Qt::white);
    add_button_white->setPos(875,475);
    add_button_white->setTextColor(Qt::black);
    add_button_white->setButtonColor(Qt::white, QColor(220, 220, 220, 255));
    connect(add_button_white, SIGNAL(clicked()), this, SLOT(addModeWhiteSlot()));
    addToScene(add_button_white);

    Button * add_button_black = new Button("Box Select", Qt::black);
    add_button_black->setPos(875,525);
    add_button_black->setTextColor(Qt::white);
    add_button_black->setButtonColor(Qt::black, QColor(30, 30, 30, 255));
    connect(add_button_black, SIGNAL(clicked()), this, SLOT(addModeBlackSlot()));
    addToScene(add_button_black);

    Button * queen_add_button = new Button("Add Queen");
    queen_add_button->setPos(1100,500);
    connect(queen_add_button, SIGNAL(clicked()), this, SLOT(addQueen()));
    addToScene(queen_add_button);

    Button * rook_add_button = new Button("Add Rook");
    rook_add_button->setPos(1100,550);
    connect(rook_add_button, SIGNAL(clicked()), this, SLOT(addRook()));
    addToScene(rook_add_button);

    Button * knight_add_button = new Button("Add Knight");
    knight_add_button->setPos(1100,600);
    connect(knight_add_button, SIGNAL(clicked()), this, SLOT(addKnight()));
    addToScene(knight_add_button);

    Button * bishop_add_button = new Button("Add Bishop");
    bishop_add_button->setPos(1100,650);
    connect(bishop_add_button, SIGNAL(clicked()), this, SLOT(addBishop()));
    addToScene(bishop_add_button);

    Button * king_add_button = new Button("Add King");
    king_add_button->setPos(1100,700);
    connect(king_add_button, SIGNAL(clicked()), this, SLOT(addKing()));
    addToScene(king_add_button);

    Button * pawn_add_button = new Button("Add Pawn");
    pawn_add_button->setPos(1100,750);
    connect(pawn_add_button, SIGNAL(clicked()), this, SLOT(addPawn()));
    addToScene(pawn_add_button);
}

void Game::clearBoard(){
    setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());
    chess->clearAll();
    //clear record
    while(!oldPlace.isEmpty()){
        oldPlace.removeLast();
        newPlace.removeLast();
        moveChess.removeLast();
        moveChessSide.removeLast();
        eatedChess.removeLast();
        eatedChessSide.removeLast();
    }
    listPtr = -1;
    recordShow();
}

void Game::resetBoard(){
    setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());
    chess->resetAll();
    //clear record
    while(!oldPlace.isEmpty()){
        oldPlace.removeLast();
        newPlace.removeLast();
        moveChess.removeLast();
        moveChessSide.removeLast();
        eatedChess.removeLast();
        eatedChessSide.removeLast();
    }
    listPtr = -1;
    recordShow();
}

void Game::addModeWhiteSlot(){
    if(addMode == false){
        setAddColor("WHITE");
        addMode = true;
    }
    else{
        addMode = false;
        if(addPlace!=nullptr) addPlace->resetOriginalColor();
    }
}
void Game::addModeBlackSlot(){
    if(addMode == false){
        setAddColor("BLACK");
        addMode = true;
    }
    else{
        addMode = false;
        if(addPlace!=nullptr) addPlace->resetOriginalColor();
    }
}

void Game::promotionSelect(){
    promotion_flag = true;
    //create Button
    int pxPos, pyPos;
    Button * queen_button = new Button("Queen");
    pxPos = int(game->width()/2 - queen_button->rect().width()/2);
    pyPos = int(game->height()/2-100);
    queen_button->setPos(pxPos,pyPos);
    Button * rook_button = new Button("Rook");
    pxPos = int(game->width()/2 - rook_button->rect().width()/2);
    pyPos = int(game->height()/2-50);
    rook_button->setPos(pxPos,pyPos);
    Button * knight_button = new Button("Knight");
    pxPos = int(game->width()/2 - knight_button->rect().width()/2);
    pyPos = int(game->height()/2);
    knight_button->setPos(pxPos,pyPos);
    Button * bishop_button = new Button("Bishop");
    pxPos = int(game->width()/2 - bishop_button->rect().width()/2);
    pyPos = int(game->height()/2+50);
    bishop_button->setPos(pxPos,pyPos);
    //connect
    connect(queen_button, SIGNAL(clicked()) , this, SLOT(addQueen()));
    connect(rook_button, SIGNAL(clicked()) , this, SLOT(addRook()));
    connect(knight_button, SIGNAL(clicked()) , this, SLOT(addKnight()));
    connect(bishop_button, SIGNAL(clicked()) , this, SLOT(addBishop()));
    //show
    addToScene(queen_button);
    addToScene(rook_button);
    addToScene(knight_button);
    addToScene(bishop_button);
    //add to list
    listG.clear();
    listG.append(queen_button);
    listG.append(rook_button);
    listG.append(knight_button);
    listG.append(bishop_button);
}

void Game::addQueen(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addQueen(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}
void Game::addRook(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addRook(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}
void Game::addKnight(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addKnight(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}
void Game::addBishop(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addBishop(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}

void Game::addKing(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addKing(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}

void Game::addPawn(){
    if(addMode==false && promotion_flag==true){
        int n = listG.size();
        for(int i =0; i < n; i++){
            removeFromScene(listG[i]);
        }
        promotion_flag = false;
    }
    if(addPlace!=nullptr && addColor!="NONE"){
        chess->addPawn(addPlace, addColor);
        addPlace->resetOriginalColor();
        addPlace = nullptr;
        addColor = nullptr;
        addMode = false;
    }
}

void Game::gameover(QString win_color){
    overText->setPlainText(win_color + " WIN!");
    overWindow->setVisible(true);
    overWindow2->setVisible(true);
    overText->setVisible(true);
    againButton->setVisible(true);
    overQuitButton->setVisible(true);
}

void Game::again(){
    overWindow->setVisible(false);
    overWindow2->setVisible(false);
    overText->setVisible(false);
    againButton->setVisible(false);
    overQuitButton->setVisible(false);
    resetBoard();
}

void Game::recordUpdate(ChessBox *oldBox, ChessBox *newBox, QString _name, \
                        QString _color, QString _name2, QString _color2, \
                        bool fmove1, bool fmove2){
    int showLen = 8;
    if(listPtr+1<showLen){
        oldPlace.append(oldBox);
        newPlace.append(newBox);
        moveChess.append(_name);
        moveChessSide.append(_color);
        eatedChess.append(_name2);
        eatedChessSide.append(_color2);
        firstMove1.append(fmove1);
        firstMove2.append(fmove2);
        moveCnt++;
        listPtr++;
    }
    else{
        for(int i=0;i<showLen-1;++i){
            oldPlace[i] = oldPlace[i+1];
            newPlace[i] = newPlace[i+1];
            moveChess[i] = moveChess[i+1];
            moveChessSide[i] = moveChessSide[i+1];
            eatedChess[i] = eatedChess[i+1];
            eatedChessSide[i] = eatedChessSide[i+1];
            firstMove1[i] = firstMove1[i+1];
            firstMove2[i] = firstMove2[i+1];
        }
        oldPlace[showLen-1] = oldBox;
        newPlace[showLen-1] = newBox;
        moveChess[showLen-1] = _name;
        moveChessSide[showLen-1] = _color;
        eatedChess[showLen-1] = _name2;
        eatedChessSide[showLen-1] = _color2;
        firstMove1[showLen-1] = fmove1;
        firstMove2[showLen-1] = fmove2;
        moveCnt++;
        listPtr = showLen-1;
    }
}

void Game::recordShow(){
    //hide all
    for(int i=0;i<8;++i){
        line[i]->setVisible(false);
    }
    //show
    int n = listPtr+1;
    QString s1, s2, s3, s4;
    int i1, i2, i3, i4;
    for(int i=0;i<n;++i){
        i1 = oldPlace[i]->colLoc+1;
        i2 = 8-oldPlace[i]->rowLoc;
        i3 = newPlace[i]->colLoc+1;
        i4 = 8-newPlace[i]->rowLoc;
        s2 = QString::number(i2);
        s4 = QString::number(i4);
        switch(i1){
        case 1: s1 = "A"; break;
        case 2: s1 = "B"; break;
        case 3: s1 = "C"; break;
        case 4: s1 = "D"; break;
        case 5: s1 = "E"; break;
        case 6: s1 = "F"; break;
        case 7: s1 = "G"; break;
        case 8: s1 = "H"; break;
        }
        switch(i3){
        case 1: s3 = "A"; break;
        case 2: s3 = "B"; break;
        case 3: s3 = "C"; break;
        case 4: s3 = "D"; break;
        case 5: s3 = "E"; break;
        case 6: s3 = "F"; break;
        case 7: s3 = "G"; break;
        case 8: s3 = "H"; break;
        }
        line[i]->setPlainText("$ " + moveChessSide[i] + "  " + \
                              moveChess[i] + "  from  " + \
                              s1+s2 + "  to  " + s3+s4);
        line[i]->setVisible(true);
    }
}

void Game::retract(){
    if(listPtr>=0){
        ChessBox *oldBox = oldPlace[listPtr];
        ChessBox *newBox = newPlace[listPtr];
        QString movePiece = moveChess[listPtr];
        QString moveSide = moveChessSide[listPtr];
        QString eatedPiece = eatedChess[listPtr];
        QString eatedSide = eatedChessSide[listPtr];
        bool fmove1 = firstMove1[listPtr];
        bool fmove2 = firstMove2[listPtr];

        oldPlace.pop_back();
        newPlace.pop_back();
        moveChess.pop_back();
        moveChessSide.pop_back();
        eatedChess.pop_back();
        eatedChessSide.pop_back();
        firstMove1.pop_back();
        firstMove2.pop_back();

        listPtr--;
        recordShow();
        //set chess
        newBox->setChessPieceColor("NONE");
        newBox->setHasChessPiece(false);
        newBox->currentPiece->~ChessPiece();

        if(movePiece=="Queen")chess->addQueen(oldBox, moveSide);
        else if(movePiece=="Rook")chess->addRook(oldBox, moveSide);
        else if(movePiece=="Knight")chess->addKnight(oldBox, moveSide);
        else if(movePiece=="Bishop")chess->addBishop(oldBox, moveSide);
        else if(movePiece=="Pawn")chess->addPawn(oldBox, moveSide);
        else if(movePiece=="King")chess->addKing(oldBox, moveSide);
        if(oldBox->getHasChessPiece()==true)oldBox->currentPiece->firstMove = fmove1;

        if(eatedPiece=="Queen")chess->addQueen(newBox, eatedSide);
        else if(eatedPiece=="Rook")chess->addRook(newBox, eatedSide);
        else if(eatedPiece=="Knight")chess->addKnight(newBox, eatedSide);
        else if(eatedPiece=="Bishop")chess->addBishop(newBox, eatedSide);
        else if(eatedPiece=="Pawn")chess->addPawn(newBox, eatedSide);
        if(newBox->getHasChessPiece()==true)newBox->currentPiece->firstMove = fmove2;
        //retract casteling
        if(movePiece=="King"){
            ChessBox *rook_place;
            //rook right by king
            if((oldBox->colLoc - newBox->colLoc)==2){
                rook_place = collection[oldBox->rowLoc][newBox->colLoc+1];
                rook_place->setChessPieceColor("NONE");
                rook_place->setHasChessPiece(false);
                rook_place->currentPiece->~ChessPiece();
                rook_place = collection[oldBox->rowLoc][0];
                chess->addRook(rook_place, moveSide);
                oldBox->currentPiece->firstMove = true;
                rook_place->currentPiece->firstMove = true;
            }
            //rook left by king
            else if((oldBox->colLoc - newBox->colLoc)==-2){
                rook_place = collection[oldBox->rowLoc][newBox->colLoc-1];
                rook_place->setChessPieceColor("NONE");
                rook_place->setHasChessPiece(false);
                rook_place->currentPiece->~ChessPiece();
                rook_place = collection[oldBox->rowLoc][7];
                chess->addRook(rook_place, moveSide);
                oldBox->currentPiece->firstMove = true;
                rook_place->currentPiece->firstMove = true;
            }
        }
        //set turn
        changeTurn();
    }
}
