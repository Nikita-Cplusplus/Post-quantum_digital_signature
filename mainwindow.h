#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "es.h"
#include "checkes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_setIrr_2_clicked();

    void on_GenButton_2_clicked();

    void on_CheckButton_2_clicked();

    void on_genIrrButton_clicked();

private:
    Ui::MainWindow *ui;
    ES sign;

};
#endif // MAINWINDOW_H
