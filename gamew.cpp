#include "gamew.h"
#include <QDebug>

gameW::gameW(QWidget *parent) :
    QWidget(parent),
    mapSize(60),
    timer(new QTimer(this))
{
    timer->setInterval(100);

    currentGeneration = new bool[mapSize * mapSize];
    nextGeneration = new bool[mapSize * mapSize];

    for(int i = 0; i < mapSize * mapSize; i++)
    {
        currentGeneration[i] = false;
        nextGeneration[i] = false;
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(updateGeneration()));
    connect(this, SIGNAL(changeBtn(const char*)), parent, SLOT(changeBtnText(const char*)));
}

gameW::~gameW()
{
    delete [] currentGeneration;
    delete [] nextGeneration;
}


void gameW::startGame()
{
    if (timer->isActive())
    {
        timer->stop();
        emit changeBtn("Start");
    }
    else
    {
        timer->start();
        emit changeBtn("Stop");
    }
}

void gameW::clear()
{
    for(int i = 0; i < mapSize * mapSize; i++)
    {
        currentGeneration[i] = false;
    }
    update();
}

bool gameW::isAlive(int i, int j)
{
    int neighNumber = 0;
    if (i != 0)
    {
        neighNumber += currentGeneration[(i - 1) * mapSize + j];
        if (j != 0)
        neighNumber += currentGeneration[(i - 1) * mapSize + j - 1];
        if (j != mapSize - 1)
        neighNumber += currentGeneration[(i - 1) * mapSize + j + 1];
    }
    if (i != mapSize - 1)
    {
        neighNumber += currentGeneration[(i + 1) * mapSize + j];
        if (j != 0)
        neighNumber += currentGeneration[(i + 1) * mapSize + j - 1];
        if (j != mapSize - 1)
        neighNumber += currentGeneration[(i + 1) * mapSize + j + 1];
    }
    if (j != mapSize - 1)
    neighNumber += currentGeneration[i * mapSize + j + 1];
    if (j != 0)
    neighNumber += currentGeneration[i * mapSize + j - 1];

    return ((currentGeneration[i * mapSize + j] == true) && (neighNumber == 2 || neighNumber == 3)) || (currentGeneration[i * mapSize + j] == false) && ( neighNumber == 3);
}

void gameW::updateGeneration()
{
    for(int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize; j++)
        {
            nextGeneration[i * mapSize + j] = isAlive(i, j);
        }
    }
    qDebug() << "NOWE NOWE";


    for(int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize; j++)
        {
            currentGeneration[i * mapSize + j] = nextGeneration[i * mapSize + j];
        }
    }

    update();
}

void gameW::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintGrid(painter);
    paintGeneration(painter);
}

void gameW::mousePressEvent(QMouseEvent *e)
{
    double cellWidth = (double)width() / mapSize;
    double cellHeight = (double)height() / mapSize;
    int i = floor(e -> y() / cellHeight);
    int j = floor(e -> x() / cellWidth);
    currentGeneration[i * mapSize + j] = !currentGeneration[i * mapSize + j];
    update();
}

void gameW::paintGrid(QPainter &painter)
{
    QRect borders(0, 0, width()-1, height()-1);
    QColor gridColor = "#000";
    gridColor.setAlpha(40);
    painter.setPen(gridColor);
    double cellWidth = (double)width() / mapSize;
    for(double k = 0; k < width(); k += cellWidth)
    {
        painter.drawLine(k, 0, k, height());
    }
    double cellHeight = (double)height()/mapSize;
    for(double k = 0; k < height(); k += cellHeight)
    {
        painter.drawLine(0, k, width(), k);
    }
    painter.drawRect(borders);
}

void gameW::paintGeneration(QPainter &painter)
{
    double cellWidth = (double)width() / mapSize;
    double cellHeight = (double)height() / mapSize;
    for(int i = 0; i < mapSize; i++)
    {
        for(int j = 0; j < mapSize ; j++)
        {
            if(currentGeneration[i * mapSize + j] == true)
            {
                double left = (double)(cellWidth * j);
                double top  = (double)(cellHeight * i);
                QRectF r(left, top, (double)cellWidth, (double)cellHeight);
                painter.fillRect(r, QBrush("#000"));
            }
        }
    }
}


