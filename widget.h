#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include "zeichenfeld.h"
class meinWidget : public QWidget
{
     Q_OBJECT
public:
    zeichenFeld *meinZeichenFeld;
    meinWidget(QWidget *parent = 0);

private:
    QPushButton *start;
private slots:
    void startPause(void);
    void saveFile(void);
    void loadFile(void);
};

#endif // WIDGET_H
