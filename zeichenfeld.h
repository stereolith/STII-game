#ifndef ZEICHENFELD_H
#define ZEICHENFELD_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

class zeichenFeld : public QWidget
{
Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);

    void serialize(QFile &file);
    void deserialize(QFile &file);
    bool getActive() {return active;}
    void setActive(bool a);
private:
    bool active;
    QPoint posPlayer;
    QColor playerColor;
    int buttonPressed;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};


#endif // ZEICHENFELD_H