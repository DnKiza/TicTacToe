#ifndef TICTAC_H
#define TICTAC_H

#include <QtWidgets>
#include <QLayout>

class Case:public QPushButton
{
    Q_OBJECT
public:
    Case();
    static int state;
    static int toUse;
    int getState();
    void setState(int);
public slots:
    void redraw();
protected:
    void paintEvent(QPaintEvent*);
    int m_currentState;
    //int m_sign;
};

class TicTacToe:public QWidget
{
    Q_OBJECT
public:
    TicTacToe();
    void setGrp1(QString);
    void setGrp2(QString);
    void checkSuccess();
public slots:
    void redraw(int);
private:
    QVector<Case*> emptyCase;
    QHBoxLayout* mainLay;
    QLabel* Grp1;
    QLabel* Grp2;
};

class TicTac:public QMainWindow
{
    Q_OBJECT
public:
    TicTac();
public slots:
    void launchX();
    void launchO();
private:
  //  QHBoxLayout* mainLay;
    TicTacToe* ticTacToe;
    //QLabel* Grp1;
    //QLabel* Grp2;
};




#endif // TICTAC_H
