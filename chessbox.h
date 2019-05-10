#ifndef CHESSBOX_H
#define CHESSBOX_H
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>


class ChessPiece;
class ChessBox:public QGraphicsRectItem
{
public:
    ChessBox(QGraphicsItem *parent = nullptr);
    ~ChessBox();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setColor(QColor color);
    void resetOriginalColor();
    void setOriginalColor(QColor value);

    void placePiece(ChessPiece *piece);

    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = nullptr);

    QString getChessPieceColor() ;
    void setChessPieceColor(QString value);

    int rowLoc;
    int colLoc;
    ChessPiece * currentPiece;
    //whether this box is castling place
    bool castling_flag;

private:
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    QString chessPieceColor;
};

#endif // CHESSBOX_H
