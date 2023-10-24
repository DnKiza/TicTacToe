#include "tictac.h"

int Case::state=0;
int Case::toUse=0;
TicTac::TicTac()
{
    // mainLay=new QHBoxLayout;
    ticTacToe=new TicTacToe;

    QWidget* choiceSign=new QWidget;
    
    QLabel* welcome=new QLabel("Welcome\nClick to choose which sign you want to "
                               "use for this part\nThis will be for the Group 1\n\n");
    welcome->setFont(QFont("Comic Sans MS",10));
    
    Case* choice0=new Case;
    Case* choice1=new Case;
    
    choice0->setState(1);
    choice1->setState(2);
    choice0->setFixedSize(80,80);
    choice1->setFixedSize(80,80);
    choice0->setStyleSheet("border: 2px solid blue");
    choice1->setStyleSheet("border: 2px solid blue");
    
    QHBoxLayout* layout1=new QHBoxLayout;
    layout1->addWidget(choice0);
    layout1->addWidget(choice1);
    
    QVBoxLayout* layout2=new QVBoxLayout;
    layout2->addWidget(welcome);
    layout2->addLayout(layout1);
    layout2->setAlignment(Qt::AlignCenter);
    
    
    choiceSign->setLayout(layout2);
    setFixedSize(600,600);
    
    
    setCentralWidget(choiceSign);
    connect(choice0,SIGNAL(clicked(bool)),this,SLOT(launchX()));
    connect(choice1,SIGNAL(clicked(bool)),this,SLOT(launchO()));
    
}
void TicTac::launchX()
{
    Case::toUse=1;
    //Grp1->setText("Group 1: O");
    ticTacToe->setGrp1("O");
    //Grp2->setText("Group 2: X");
    ticTacToe->setGrp2("X");
    setCentralWidget(ticTacToe);
}
void TicTac::launchO()
{
    Case::toUse=2;
    //Grp1->setText("Group 1: X");
    ticTacToe->setGrp1("X");
    //Grp2->setText("Group 2: O");
    ticTacToe->setGrp2("O");
    setCentralWidget(ticTacToe);
}

TicTacToe::TicTacToe()
{
    mainLay=new QHBoxLayout;
    QSignalMapper* signalMapper=new QSignalMapper;
    
    QGridLayout* layout=new QGridLayout;
    
    Grp1=new QLabel("Group 1: ");
    Grp2=new QLabel("Group 2: ");
    
    
    
    
    int it=0;
    for(it;it<9;it++)
    {
        emptyCase.append(new Case);
        emptyCase.at(it)->setStyleSheet("border: 2px solid blue");
        emptyCase.at(it)->setMinimumSize(80,80);
        emptyCase.at(it)->setState(0);
        signalMapper->setMapping(emptyCase.at(it),emptyCase.indexOf(emptyCase.at(it)));
        //connect(emptyCase.at(it),SIGNAL(clicked(bool)),emptyCase.at(it),SLOT(redraw()));
        connect(emptyCase.at(it), SIGNAL(clicked(bool)),signalMapper, SLOT(map()));
    }
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(redraw(int)));
    qDebug()<<it<<emptyCase.length();
    
    it=0;
    for(int row=0;row<3;row++)
    {
        for(int column=0;column<3;column++)
        {
            layout->addWidget(emptyCase.at(it),row,column);
            it++;
        }
    }
    layout->setSpacing(0);
    
    mainLay->addWidget(Grp1);
    mainLay->addLayout(layout);
    mainLay->addWidget(Grp2);
    mainLay->setAlignment(Qt::AlignCenter);
    
    setLayout(mainLay);
    
    
}
void TicTacToe::setGrp1(QString value)
{
    Grp1->setText(QString("Group 1: %1").arg(value));
}
void TicTacToe::setGrp2(QString value)
{
    Grp2->setText(QString("Group 2: %1").arg(value));
}
void TicTacToe::redraw(int value)
{
    if(emptyCase.at(value)->getState()==0)
    {
        if(Case::toUse==1&&Case::state==0||Case::toUse==1&&Case::state%2==0||Case::toUse==2&&Case::state%2!=0)
            emptyCase.at(value)->setState(1);
        else if(Case::toUse==2&&Case::state==0||Case::toUse==2&&Case::state%2==0||Case::toUse==1&&Case::state%2!=0)
            emptyCase.at(value)->setState(2);
        // else if(Case::toUse==1&&Case::state%2!=0);
         Case::state++;
    }
    /*else if(Case::state%2==0)
    {
        if(Case::toUse==1)
            emptyCase.at(value)->setState(1);
        else if(Case::toUse==2)
            emptyCase.at(value)->setState(2);
    }
    else if(Case::state%2!=0)
    {
        if(Case::toUse==1)
            emptyCase.at(value)->setState(2);
        else if(Case::toUse==2)
            emptyCase.at(value)->setState(1);
    }*/
    emptyCase.at(value)->repaint();
    checkSuccess();


    if(Case::state==9)
    {
        QMessageBox::information(this,"Warning","Game over for everyone");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
        repaint();
    }
    qDebug()<<Case::state;

    //qApp->aboutQt();
}

void TicTacToe::checkSuccess()
{
    if(emptyCase.at(0)->getState()!=0&&emptyCase.at(1)->getState()!=0&&emptyCase.at(2)->getState()!=0&&emptyCase.at(0)->getState()==emptyCase.at(1)->getState()&&emptyCase.at(0)->getState()==emptyCase.at(2)->getState()&&emptyCase.at(1)->getState()==emptyCase.at(2)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(3)->getState()!=0&&emptyCase.at(4)->getState()!=0&&emptyCase.at(5)->getState()!=0&&emptyCase.at(3)->getState()==emptyCase.at(4)->getState()&&emptyCase.at(3)->getState()==emptyCase.at(5)->getState()&&emptyCase.at(4)->getState()==emptyCase.at(5)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(6)->getState()!=0&&emptyCase.at(7)->getState()!=0&&emptyCase.at(8)->getState()!=0&&emptyCase.at(6)->getState()==emptyCase.at(7)->getState()&&emptyCase.at(6)->getState()==emptyCase.at(8)->getState()&&emptyCase.at(7)->getState()==emptyCase.at(8)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(0)->getState()!=0&&emptyCase.at(3)->getState()!=0&&emptyCase.at(6)->getState()!=0&&emptyCase.at(0)->getState()==emptyCase.at(3)->getState()&&emptyCase.at(0)->getState()==emptyCase.at(6)->getState()&&emptyCase.at(3)->getState()==emptyCase.at(6)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(1)->getState()!=0&&emptyCase.at(4)->getState()!=0&&emptyCase.at(7)->getState()!=0&&emptyCase.at(1)->getState()==emptyCase.at(4)->getState()&&emptyCase.at(1)->getState()==emptyCase.at(7)->getState()&&emptyCase.at(4)->getState()==emptyCase.at(7)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(2)->getState()!=0&&emptyCase.at(5)->getState()!=0&&emptyCase.at(8)->getState()!=0&&emptyCase.at(2)->getState()==emptyCase.at(5)->getState()&&emptyCase.at(2)->getState()==emptyCase.at(8)->getState()&&emptyCase.at(5)->getState()==emptyCase.at(8)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(2)->getState()!=0&&emptyCase.at(4)->getState()!=0&&emptyCase.at(6)->getState()!=0&&emptyCase.at(2)->getState()==emptyCase.at(4)->getState()&&emptyCase.at(2)->getState()==emptyCase.at(6)->getState()&&emptyCase.at(4)->getState()==emptyCase.at(6)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
    else if(emptyCase.at(0)->getState()!=0&&emptyCase.at(4)->getState()!=0&&emptyCase.at(8)->getState()!=0&&emptyCase.at(0)->getState()==emptyCase.at(4)->getState()&&emptyCase.at(0)->getState()==emptyCase.at(8)->getState()&&emptyCase.at(4)->getState()==emptyCase.at(8)->getState())
    {
        QMessageBox::information(this,"Winnn","You won my guy");
        for(int c=0;c<9;c++)
            emptyCase.at(c)->setState(0);
        Case::state=0;
    }
}

Case::Case()
{}
int Case::getState()
{
    return m_currentState;
}

void Case::setState(int currentState)
{
    m_currentState=currentState;
}
void Case::redraw()
{
    repaint();
    qDebug()<<"gdfcqcx";
    qApp->aboutQt();
}

void Case::paintEvent(QPaintEvent* event)
{
    QVector<QLineF> lines;
    lines.append(QLineF(0,0,80,80));
    lines.append(QLineF(80,0,0,80));
    QPainter painter(this);
    //painter.setPen(QPen(QColor(220,145,204),2));
    
    if(getState()==1)
        painter.drawEllipse(0,0,80,80);
    else if(getState()==2)
        painter.drawLines(lines);

    QPushButton::paintEvent(event);
    
    /*painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath paint;
    paint.addEllipse(QRect(0,0,30,30));
    painter.drawPath(paint);*/
}
