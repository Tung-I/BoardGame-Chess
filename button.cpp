#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>


Button::Button(QString name, QColor _color, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //
    buttonColor = _color;
    buttonHoverColor = QColor(50, 61, 61, 255);
    //draw the rect
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_color);
    setBrush(brush);

    //draw Text
    text = new QGraphicsTextItem(name,this);
    int xPos = int(rect().width()/2 - text->boundingRect().width()/2);
    int yPos = int(rect().height()/2 - text->boundingRect().height()/2);
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(QColor(41, 255, 41, 255));

    //Allow responding to hover
    setAcceptHoverEvents(true);


}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event) emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(buttonHoverColor);
    setBrush(brush);
    }
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(buttonColor);
    setBrush(brush);
    }
}

void Button::setTextColor(QColor _color){
    text->setDefaultTextColor(_color);
}

void Button::setButtonColor(QColor _color, QColor _hoverColor){
    buttonColor = _color;
    buttonHoverColor = _hoverColor;
}
