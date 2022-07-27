#include "client.h"
#include "debug.h"
#include "pexeso.h"
#include "indexedbutton.h"
#include "preferences.h"
#include "server.h"

#include <QAction>
#include <QCloseEvent>
#include <QComboBox>
#include <QGridLayout>
#include <QIcon>
#include <QImage>
#include <QLabel>
#include <QLCDNumber>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStackedWidget>
#include <QStatusBar>
#include <stdlib.h>
#include <time.h>
#include <QToolBar>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

Pexeso::Pexeso(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
    loadSettings();
    loadImages();
    setupMenu();
//    startGameServer();
    setWindowTitle(tr("Flag alphabet Pexeso"));
    resize(1024, 768);
}

void Pexeso::closeEvent(QCloseEvent *evt){
    if(QMessageBox::question(this, tr("Really quit?"),
                          tr("Do you really want to quit?"))
            == QMessageBox::Yes){
        saveSettings();
        evt->accept();
    } else{
        evt->ignore();
    }
}

void Pexeso::configure()
{
    preferences p;
    p.setMaxCards(all);
    p.setCols(cols);
    p.setRows(rows);
    if(p.exec() == QDialog::Accepted && (cols != p.getCols() || rows != p.getRows()))
    {
        stopGame();
        cols = p.getCols();
        rows = p.getRows();
        n = cols*rows/2;
        startGameServer();
    }
}

void Pexeso::joinGameServer()
{
    Client Pexeclient;
//    Pexeclient.onReadyRead();
}

void Pexeso::loadImages()
{
    for(unsigned int i = 0; i < all/2; i++)
    {
        image[i] = new QLabel();
    }
    image[0]->setPixmap(QPixmap(":/pictures/0.png"));
    image[1]->setPixmap(QPixmap(":/pictures/1.png"));
    image[2]->setPixmap(QPixmap(":/pictures/2.png"));
    image[3]->setPixmap(QPixmap(":/pictures/3.png"));
    image[4]->setPixmap(QPixmap(":/pictures/4.png"));
    image[5]->setPixmap(QPixmap(":/pictures/5.png"));
    image[6]->setPixmap(QPixmap(":/pictures/6.png"));
    image[7]->setPixmap(QPixmap(":/pictures/7.png"));
    image[8]->setPixmap(QPixmap(":/pictures/8.png"));
    image[9]->setPixmap(QPixmap(":/pictures/9.png"));
    image[10]->setPixmap(QPixmap(":/pictures/A.png"));
    image[11]->setPixmap(QPixmap(":/pictures/B.png"));
    image[12]->setPixmap(QPixmap(":/pictures/C.png"));
    image[13]->setPixmap(QPixmap(":/pictures/D.png"));
    image[14]->setPixmap(QPixmap(":/pictures/E.png"));
    image[15]->setPixmap(QPixmap(":/pictures/F.png"));
    image[16]->setPixmap(QPixmap(":/pictures/G.png"));
    image[17]->setPixmap(QPixmap(":/pictures/H.png"));
    image[18]->setPixmap(QPixmap(":/pictures/I.png"));
    image[19]->setPixmap(QPixmap(":/pictures/J.png"));
    image[20]->setPixmap(QPixmap(":/pictures/K.png"));
    image[21]->setPixmap(QPixmap(":/pictures/L.png"));
    image[22]->setPixmap(QPixmap(":/pictures/M.png"));
    image[23]->setPixmap(QPixmap(":/pictures/N.png"));
    image[24]->setPixmap(QPixmap(":/pictures/O.png"));
    image[25]->setPixmap(QPixmap(":/pictures/P.png"));
    image[26]->setPixmap(QPixmap(":/pictures/Q.png"));
    image[27]->setPixmap(QPixmap(":/pictures/R.png"));
    image[28]->setPixmap(QPixmap(":/pictures/S.png"));
    image[29]->setPixmap(QPixmap(":/pictures/T.png"));
    image[30]->setPixmap(QPixmap(":/pictures/U.png"));
    image[31]->setPixmap(QPixmap(":/pictures/V.png"));
    image[32]->setPixmap(QPixmap(":/pictures/W.png"));
    image[33]->setPixmap(QPixmap(":/pictures/X.png"));
    image[34]->setPixmap(QPixmap(":/pictures/Y.png"));
    image[35]->setPixmap(QPixmap(":/pictures/Z.png"));
    name[0] = new QLabel("Una one"); //neprekladam, nebot preklad neexistuje
    name[1] = new QLabel("Bisso two");
    name[2] = new QLabel("Terra three");
    name[3] = new QLabel("Karte four");
    name[4] = new QLabel("Panta five");
    name[5] = new QLabel("Soxi six");
    name[6] = new QLabel("Sette seven");
    name[7] = new QLabel("Okto eight");
    name[8] = new QLabel("Nove niner");
    name[9] = new QLabel("Nada zero");
    name[10] = new QLabel("Alpha");
    name[11] = new QLabel("Bravo");
    name[12] = new QLabel("Charlie");
    name[13] = new QLabel("Delta");
    name[14] = new QLabel("Echo");
    name[15] = new QLabel("Foxtrot");
    name[16] = new QLabel("Golf");
    name[17] = new QLabel("Hotel");
    name[18] = new QLabel("India");
    name[19] = new QLabel("Juliet");
    name[20] = new QLabel("Kilo");
    name[21] = new QLabel("Lima");
    name[22] = new QLabel("Mike");
    name[23] = new QLabel("November");
    name[24] = new QLabel("Oscar");
    name[25] = new QLabel("Papa");
    name[26] = new QLabel("Quebec");
    name[27] = new QLabel("Romeo");
    name[28] = new QLabel("Sierra");
    name[29] = new QLabel("Tango");
    name[30] = new QLabel("Uniform");
    name[31] = new QLabel("Victor");
    name[32] = new QLabel("Whiskey");
    name[33] = new QLabel("X-Ray");
    name[34] = new QLabel("Yankee");
    name[35] = new QLabel("Zulu");
    for(unsigned int i = 0; i < all/2; i++)
    {
        card[i] = new QStackedWidget;
        clickField[i] = new indexedButton(i);
        card[i]->insertWidget(0, clickField[i]);
        card[i]->insertWidget(1, image[i]);
        connect(clickField[i], SIGNAL(clicked_index(unsigned int)), this, SLOT(stackedWidget_clicked(unsigned int)));

        card[i+all/2] = new QStackedWidget;
        clickField[i+all/2] = new indexedButton(i+all/2);
        card[i+all/2]->insertWidget(0, clickField[i+all/2]);
        card[i+all/2]->insertWidget(1, name[i]);
        connect(clickField[i+all/2], SIGNAL(clicked_index(unsigned int)), this, SLOT(stackedWidget_clicked(unsigned int)));
    }
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);
}

void Pexeso::loadSettings()
{
    QSettings settings("Jachym Lis", "PexesoQt");
    cols = settings.value("cols", cols).toUInt();
    rows = settings.value("rows", rows).toUInt();
    n = cols*rows/2;
}

void Pexeso::mixing()
{
#ifdef DEBUG_H
    std::cout<< "mixing" << std::endl;
#endif
    unsigned int *select = new unsigned int[rows * cols];
    for(unsigned int i = 0; i < n; i++)
    {
        select[i] = rand()%(all/2);
        for(unsigned int j = 0; j < i; j++)
        {
            if(select[i] == select[j])
            {
                i--;
                break;
            }
        }
        select[i + n] = select[i] + all/2;
    }
    mix = new unsigned int[rows*cols];
    for(unsigned int i = 0; i < rows*cols; i++)
    {
        mix[i] = select[rand()%(rows*cols)];
        for(unsigned int j = 0; j < i; j++)
        {
            if(mix[i] == mix[j])
            {
                i--;
                break;
            }
        }
    }
    delete[] select;
#ifdef DEBUG_H
    std::cout << "mixed" << std::endl;
#endif
}

void Pexeso::saveSettings()
{
    QSettings settings("Jachym Lis", "PexesoQt");
    settings.setValue("cols", cols);
    settings.setValue("rows", rows);
}

void Pexeso::setupMenu()
{
    mnuGame = new QMenu(tr("&Game"));

    mnuStart = new QMenu(tr("S&tart"));
    mnuStart->setToolTip(tr("Gives options to start or join a game server"));
    mnuGame->addMenu(mnuStart);

    actStart = new QAction(tr("Start New Game &Server"));
    actStart->setToolTip(tr("Starts new game server"));
    mnuStart->addAction(actStart);
    connect(actStart, SIGNAL(triggered()), this, SLOT(stopGame()));
    connect(actStart, SIGNAL(triggered()), this, SLOT(startGameServer()));

    actConnect = new QAction(tr("&Connect to Game Server"));
    actConnect->setToolTip(tr("Connects to game server"));
    mnuStart->addAction(actConnect);
    connect(actConnect, SIGNAL(triggered()), this, SLOT(stopGame()));
    connect(actConnect, SIGNAL(triggered()), this, SLOT(joinGameServer()));

    actSet = new QAction(tr("&Settings"));
    actSet->setToolTip(tr("Allows user to set dimensions of the grid"));
    mnuGame->addAction(actSet);
    connect(actSet, SIGNAL(triggered()), this, SLOT(configure()));

    actEnd = new QAction(tr("&End"));
    actEnd->setToolTip(tr("Exits the application"));
    mnuGame->addAction(actEnd);
    connect(actEnd, SIGNAL(triggered()), this, SLOT(close()));

    menuBar()->addMenu(mnuGame);

    myToolBar = new QToolBar;

    Player_1 = new QLabel(tr("Player 1:"));
    score[0] = new QLCDNumber(2, nullptr);
    Player_2 = new QLabel(tr("Player 2:"));
    score[1] = new QLCDNumber(2, nullptr);
    player = new QLabel(tr("Active Player:"));
    playing = new QLCDNumber(1, nullptr);
    myToolBar->addWidget(Player_1);
    myToolBar->addWidget(score[0]);
    myToolBar->addWidget(Player_2);
    myToolBar->addWidget(score[1]);
    myToolBar->addWidget(player);
    myToolBar->addWidget(playing);

    addToolBar(myToolBar);
}

void Pexeso::stackedWidget_clicked(unsigned int index)
{
#ifdef DEBUG_H
    std::cout << "slot stackedWidget_clicked(" << index << ")" << std::endl;
#endif
    if(card[index]->currentIndex())
    {
        return;
    }
    else if(card_flipped)
    {
        if(index == opposite_index)
        {
            card[index]->setCurrentIndex(1);
            score[playing->intValue() - 1]->display(score[playing->intValue() - 1]->intValue() + 1);
            if((unsigned int)score[0]->intValue() + (unsigned int)score[1]->intValue() == n)
            {
                if(score[0]->intValue() == score[1]->intValue())
                {
                    QMessageBox::information(this, tr("It's a tie!"), tr("Both players have the same score. Starting new game."));
                }
                else
                {
                    QMessageBox::information(this, tr("Congratulations!"), tr("Player %1 wins! \nFinal score: Player 1: %2 cards, Player 2: %3 cards. \nStarting new game.").arg(score[0]->intValue() > score[1]->intValue() ? 1 : 2).arg(score[0]->intValue()).arg(score[1]->intValue()));
                }
                stopGame();
                startGameServer();
                return;
            }
            else
            {
                QMessageBox::information(this, tr("Succes!"), tr("Player %1 found a pair, he has now %2 pairs and continues.").arg(playing->intValue()).arg(score[playing->intValue() - 1]->intValue()));
            }
        }
        else
        {
#ifdef DEBUG_H
            std::cout << "bad match" << std::endl;
#endif
            card[index]->setCurrentIndex(1);
            playing->display(playing->intValue() == 1 ? 2 : 1);
            QMessageBox::information(this, tr("Fail."), tr("Wrong pair, now plays player %1.").arg(playing->intValue()));
            sleep(2);
            card[opposite_index < all/2 ? opposite_index + all/2 : opposite_index - all/2]->setCurrentIndex(0);
            card[index]->setCurrentIndex(0);
        }
    }
    else
    {
        card[index]->setCurrentIndex(1);
        opposite_index = index < all/2 ? index + all/2 : index - all/2; //ulozim si index karty, kterou potrebuji do paru
#ifdef DEBUG_H
        std::cout << "flipped card " << index << ", looking for card " << opposite_index << std::endl;
#endif
    }
    card_flipped = !card_flipped;
#ifdef DEBUG_H
    std::cout << "slot stackedWidget_clicked ended" << std::endl;
#endif
}

void Pexeso::startGameServer()
{
#ifdef DEBUG_H
    std::cout << "starting a new game" << std::endl;
#endif
    Server Pexeserver;
    try
    {
        Pexeserver.waitForClient();
    }  catch (bool& success)
    {
        QMessageBox::information(this, tr("Fail."), tr("Client not connected, game can't be started."));
        return;
    }
    mixing();
    Pexeserver.sendArray(mix, rows, cols);
#ifdef DEBUG_H
    std::cout << "placing cards" << std::endl;
#endif
    field = new QGridLayout(centralWidget);
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
#ifdef DEBUG_H
            std::cout << "flipping card " << mix[cols * i + j] << std::endl;
#endif
            card[mix[cols * i + j]]->setCurrentIndex(0);
            card[mix[cols * i + j]]->setVisible(true);
#ifdef DEBUG_H
            std::cout << "card " << mix[cols * i + j] << " flipped" << std::endl;
#endif
            field->addWidget(card[mix[cols * i + j]], i + 1, j + 1);
            if(!i)
            {
                field->setColumnMinimumWidth(j+1, 150);
                field->setColumnStretch(j, 1.0/float(cols));
            }
        }
        field->setRowMinimumHeight(i+1, 75);
        field->setRowStretch(i, 1.0/float(rows));
    }
    playing->display(1);
    card_flipped = false;
    score[0]->display(0);
    score[1]->display(0);
    statusBar()->showMessage(tr("Ready"), 3000);
#ifdef DEBUG_H
    std::cout << "game started" << std::endl;
#endif
}

void Pexeso::stopGame()
{
#ifdef DEBUG_H
    std::cout << "Stopping game" << std::endl;
#endif
    if(!field)
    {
#ifdef DEBUG_H
        std::cout << "Game not even started yet" << std::endl;
#endif
        return;
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            card[mix[cols * i + j]]->setVisible(false);
        }
    }
    delete field;
    delete [] mix;
#ifdef DEBUG_H
    std::cout << "Game stopped" << std::endl;
#endif
}

Pexeso::~Pexeso()
{
}
