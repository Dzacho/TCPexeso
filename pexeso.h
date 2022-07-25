#ifndef PEXESO_H
#define PEXESO_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

class QAction;
class QComboBox;
class QGridLayout;
class QLabel;
class QLCDNumber;
class QMenu;
class QPushButton;
class QStackedWidget;
class QToolBar;
class indexedButton;

class Pexeso : public QMainWindow
{
    Q_OBJECT
    unsigned int cols = 8;
    unsigned int rows = 9;
    unsigned int n = cols*rows/2;
    static const unsigned int all = 72;
    QAction *actConnect;
    QAction *actEnd;
    QAction *actSet;
    QAction *actStart;
    QMenu *mnuStart;
    QStackedWidget *card[all];
    bool card_flipped;
    QWidget *centralWidget;
    indexedButton *clickField[all];
    QGridLayout *field;
    QWidget *grid;
    QLabel *image[all/2];
    unsigned int *mix;
    QMenu *mnuGame;
    QToolBar *myToolBar;
    QLabel *name[all/2];
    unsigned int opposite_index;
    QLabel *player;
    QLabel *Player_1;
    QLabel *Player_2;
    QLCDNumber *playing;
    QLCDNumber *score[2];

    void closeEvent(QCloseEvent *evt);
    void endGame();
    void loadImages();
    void mixing();
    void setupMenu();

public:
    Pexeso(QWidget *parent = nullptr);
    ~Pexeso();
public slots:
    void configure();
    void loadSettings();
    void saveSettings();
    void stackedWidget_clicked(unsigned int index);
    void startGame();
    void stopGame();
};
#endif // PEXESO_H
