#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GTD_map.h"
#include "datagen.h"
#include "node.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QTime>
#include <string>
#include <fstream>
#include <iostream>
#include<vector>
#define BOARDER_WIDTH 1600
#define BOARDER_HEIGHT 1200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_Load_and_print_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string map_name = ui->le_print_map_name->text().toStdString();
    if (map_name == "")
        map_name = "map.txt";
    GTD_map *m = new GTD_map();
    int ret = m->mapLoader(map_name, scene);
    if (ret == 0)
    {
        QGraphicsView * view = new QGraphicsView(scene);

        view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //this->setCentralWidget(view);
        view->show();
    }
    else if (ret == 1)
    {
        ui->label->setText("Map File Not Found!");
        ui->label->repaint();
    }
    delete m;
}

void MainWindow::on_bt_generate_clicked()
{
    std::string map_name = ui->le_print_map_name->text().toStdString();
    std::string outputPath = ui->le_output->text().toStdString();
    DataGen *gen = new DataGen();
    gen->mapReader(map_name);
    gen->generator(outputPath);
}

void MainWindow::on_bt_print_path_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,BOARDER_WIDTH,BOARDER_HEIGHT);

    std::string map_name = ui->le_print_map_name->text().toStdString();
    std::string path_name = ui->le_output->text().toStdString();
    if (map_name == "")
        map_name = "map.txt";
    GTD_map *m = new GTD_map();
    int ret = m->mapAndPathLoader(map_name, path_name, scene);
    if (ret == 0)
    {
        QGraphicsView * view = new QGraphicsView(scene);

        view->setFixedSize(BOARDER_WIDTH,BOARDER_HEIGHT);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //this->setCentralWidget(view);
        view->show();
    }
    else if (ret == 1)
    {
        ui->label->setText("Map File Not Found!");
        ui->label->repaint();
    }
    delete m;
}
