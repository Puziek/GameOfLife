#ifndef GAMEW_H
#define GAMEW_H

#include <QColor>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

class gameW : public QWidget
{
    Q_OBJECT

private:
    bool * currentGeneration;
    bool * nextGeneration;
    int mapSize;
    QTimer * timer;
    bool isAlive(int i, int j);

public:
    explicit gameW(QWidget * parent = 0);
    ~gameW();

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void paintGrid(QPainter &painter);
    void paintGeneration(QPainter &painter);
    void updateGeneration();

public slots:
    void startGame();
    void clear();

signals:
    void changeBtn(const char* btnText);


//signals:
    //void environmentChanged(bool ok);
};


#endif // GAMEW_H
