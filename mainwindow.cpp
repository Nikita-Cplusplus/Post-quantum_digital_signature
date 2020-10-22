#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setIrr_2_clicked()
{
    QString strIrr = ui->Lineirr->text();
    reverse(strIrr.begin(), strIrr.end());
    vector<bool> irr;
    for (int i = 0 ; i < strIrr.size() ; ++i)
    {
        if(strIrr[i] == '1')
            irr.push_back(1);
        else
            irr.push_back(0);
    }
    GF::setIrreduciblePoly(irr);
}

void MainWindow::on_GenButton_2_clicked()
{
    sign.genKeys();
    sign.genES();
    QVector<QString> Data = sign.getData();
    ui->N1->setText(Data[0]);
    ui->N2->setText(Data[1]);
    ui->N3->setText(Data[2]);
    ui->N4->setText(Data[3]);
    ui->G1->setText(Data[4]);
    ui->G2->setText(Data[5]);
    ui->G3->setText(Data[6]);
    ui->G4->setText(Data[7]);
    ui->T1->setText(Data[8]);
    ui->T2->setText(Data[9]);
    ui->T3->setText(Data[10]);
    ui->T4->setText(Data[11]);
    ui->x1->setText(Data[12]);
    ui->Y1->setText(Data[13]);
    ui->Y2->setText(Data[14]);
    ui->Y3->setText(Data[15]);
    ui->Y4->setText(Data[16]);
    ui->Q1->setText(Data[17]);
    ui->Q2->setText(Data[18]);
    ui->Q3->setText(Data[19]);
    ui->Q4->setText(Data[20]);
    ui->e1->setText(Data[21]);
    ui->s1->setText(Data[22]);
    ui->W1->setText(Data[23]);
    ui->W2->setText(Data[24]);
    ui->W3->setText(Data[25]);
    ui->W4->setText(Data[26]);
}

void MainWindow::on_CheckButton_2_clicked()
{
    checkES check(sign.getY(),sign.getQ());
    bool flagCheck = check.check();
    QVector<QString> Data = check.getData();
    ui->Wx1->setText(Data[0]);
    ui->Wx2->setText(Data[1]);
    ui->Wx3->setText(Data[2]);
    ui->Wx4->setText(Data[3]);
    ui->ex1->setText(Data[4]);
    if (flagCheck == true)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::green);
        ui->ex1->setPalette(palette);
    }
    else
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        ui->ex1->setPalette(palette);
    }
    qDebug() << flagCheck;
}

void MainWindow::on_genIrrButton_clicked()
{
    int pow = ui->linePow->text().toInt();
    genIrrPoly(pow);
    vector<bool> irr = GF::getIrreduciblePoly();
    QString irrStr;
    for (int i = 0 ; i < int(irr.size()) ; ++i)
    {
        if(irr[i] == 1)
            irrStr.push_back('1');
        else
            irrStr.push_back('0');
    }
    reverse(irrStr.begin(),irrStr.end());
    ui->Lineirr->setText(irrStr);
}
