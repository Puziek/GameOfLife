#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new gameW(this))
{
    ui->setupUi(this);
    ui->gameLayout->addWidget(game);

    connect(ui->btnStart, SIGNAL(clicked()), game, SLOT(startGame()));
    connect(ui->btnClear, SIGNAL(clicked()), game, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeBtnText(const char* btnText)
{
    ui->btnStart->setText(btnText);
}
