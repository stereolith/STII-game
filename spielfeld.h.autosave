#include "piece.h"
#include "fallingpiece.h"
#include "lives.h"

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

class spielFeld : public QWidget //Renderbereich des Spieles selbst
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
signals:
    void signalActive(bool a);
private:
    bool active;
    int buttonPressed;
    QTimer *timer;
    QLabel *pointsLabel;
    QLabel *gameOverLabel;
    QLabel *gameOverPointsLabel;
    int points;

    piece *player;
    lives *playerLives;
    std::vector<fallingPiece*> fallingPieces;
    const int timeToSpawn = 30;
    const int hitTimeout = 50;
    const int invincibleTimeout = 50;
    const int gameOverTimeout = 100;
    bool playerHit;
    bool invincible;
    bool gameIsOver;
    void spawnFallingPiece();
    void deleteFallingPieces();
    void gameOver();
private slots:
    void updateEvent();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
