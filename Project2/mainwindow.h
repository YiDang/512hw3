#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gtd_map.h"
#include "node.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bt_Load_and_print_clicked();
    void on_bt_generate_clicked();

    void on_bt_print_path_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
