#include "piece.h"
#include "fallingpiece.h"
#include "lives.h"

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

class spielFeld : public QWidget
{
Q_OBJECT
public:
    spielFeld(QWidget *parent = 0);

    void serialize(QFile &file);
    void deserialize(QFile &file);
    bool getActive() {return active;}
    void setActive(bool a);
    void setPointsPtr(QLabel *ptr){pointsLabel = ptr;}
    spielFeld *t;
private:
    bool active;
    int buttonPressed;
    QTimer *timer;
    QLabel *pointsLabel;
    int points;

    piece player;
    lives *playerLives;
    std::vector<fallingPiece*> fallingPieces;
    int timeToSpawn;
    void spawnFallingPiece();
private slots:
    void updateEvent();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
