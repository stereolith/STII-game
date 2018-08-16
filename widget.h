#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

#include "spielFeld.h"
class meinWidget : public QWidget
{
     Q_OBJECT
public:
    spielFeld *meinspielFeld;
    meinWidget(QWidget *parent = 0);
    QLabel *getPointsPrt(){return points;}
private:
    QPushButton *start;
    QLabel *points;
private slots:
    void startPause(void);
    void saveFile(void);
    void loadFile(void);
};

#endif // WIDGET_H
