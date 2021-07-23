#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Дополнительные параметры");
      }

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    std::vector<int> vecT(8);
    std::vector<int> vecC(8);

    vecT[0] = (ui->lineEdit->text()).toInt();
    vecT[1] = (ui->lineEdit_2->text()).toInt();
    vecT[2] = (ui->lineEdit_3->text()).toInt();
    vecT[3] = (ui->lineEdit_4->text()).toInt();
    vecT[4] = (ui->lineEdit_5->text()).toInt();
    vecT[5] = (ui->lineEdit_6->text()).toInt();
    vecT[6] = (ui->lineEdit_7->text()).toInt();
    vecT[7] = (ui->lineEdit_8->text()).toInt();

    vecC[0] = (ui->lineEdit_13->text()).toInt();
    vecC[1] = (ui->lineEdit_14->text()).toInt();
    vecC[2] = (ui->lineEdit_9->text()).toInt();
    vecC[3] = (ui->lineEdit_16->text()).toInt();
    vecC[4] = (ui->lineEdit_11->text()).toInt();
    vecC[5] = (ui->lineEdit_10->text()).toInt();
    vecC[6] = (ui->lineEdit_15->text()).toInt();
    vecC[7] = (ui->lineEdit_12->text()).toInt();

    emit sendData(vecT, vecC);

    close();
}
