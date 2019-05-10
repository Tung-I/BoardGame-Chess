#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:

    Button(QString name, QColor _color = QColor(70, 70, 70, 255), QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void setTextColor(QColor _color);
    void setButtonColor(QColor _color, QColor _hoverColor);

signals:
    void clicked();

private:
    QGraphicsTextItem *text;
    QColor buttonColor;
    QColor buttonHoverColor;
};

#endif // BUTTON_H
