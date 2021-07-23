#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QMessageBox>
#include <vector>
#include "simulCycle.h"
#include "qcustomplot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Проект станции технического обслуживания");
    ui->comboBox->addItem("Эрланга 2-го порядка");
    ui->comboBox->addItem("Нормальный закон");
    ui->comboBox->addItem("Равномерный закон");
    myDialog = new Dialog();
    connect(ui->pushButton, SIGNAL(clicked()), myDialog, SLOT(show()));
    connect(myDialog, SIGNAL(sendData(std::vector<int>, std::vector<int>)), this, SLOT(onSignal(std::vector<int>, std::vector<int>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::onSignal(std::vector<int> vecT, std::vector<int> vecC)
{
    vecDefiTime = vecT;
    vecDefiCost = vecC;
}

void MainWindow::on_pushButton_2_clicked()
{
    int time = (ui->lineEdit->text()).toInt()*60;
    if (time <= 0) { QMessageBox::warning(this, "Ошибка", "Вы указали не все параметры"); return;}
    int raspr = ui->comboBox->currentIndex();
    int param1 = (ui->lineEdit_5->text()).toInt();
    if (param1 <= 0) { QMessageBox::warning(this, "Ошибка", "Вы указали не все параметры"); return;}
    int param2;
    if (raspr != 0) {
        param2 = (ui->lineEdit_9->text()).toInt();
        if (param1 <= 0) { QMessageBox::warning(this, "Ошибка", "Вы указали не все параметры"); return;}
    } else param2 = 0;

    double pr_to = (ui->lineEdit_2->text()).toInt();
    double pr_torem = (ui->lineEdit_4->text()).toInt();
    double pr_r1 = (ui->lineEdit_3->text()).toInt();

    if (pr_to*pr_r1 == 0) { QMessageBox::warning(this, "Ошибка", "Вы указали не все параметры");return;}
    if (pr_to + pr_r1 != 100) { QMessageBox::warning(this, "Ошибка", "Сумма процентов на ТО и ремонт должна составлять 100%");return;}
    pr_to = pr_to/100;
    pr_torem = pr_torem/100;
    pr_r1 = pr_r1/100;

    int numTO = (ui->lineEdit_6->text()).toInt();
    int numRem = (ui->lineEdit_7->text()).toInt();
    int numUni = (ui->lineEdit_8->text()).toInt();

    if (numRem + numTO + numUni <= 0) { QMessageBox::warning(this, "Ошибка", "Вы указали не все параметры");return;}

    std::vector<int> res = simulCycl(time, raspr, param1, param2, pr_to, pr_torem, pr_r1, vecDefiTime, vecDefiCost, numTO, numRem, numUni);
    QString new_label;
    new_label = QString::number(res[0], 'g', 15);
    ui->label_kol ->setText(new_label);
    new_label = QString::number(res[1], 'g', 15);
    ui->label_j ->setText(new_label);
    new_label = QString::number(res[2], 'g', 15);
    ui->label_r1 ->setText(new_label);
    new_label = QString::number(res[3], 'g', 15);
    ui->label_r2 ->setText(new_label);
    new_label = QString::number(res[4], 'g', 15);
    ui->label_r3 ->setText(new_label);

    new_label = QString::number(res[5], 'g', 15);
    ui->label_allTime ->setText(new_label);
    new_label = QString::number(res[6], 'g', 15);
    ui->label_t_to ->setText(new_label);
    new_label = QString::number(res[7], 'g', 15);
    ui->label_t_pr ->setText(new_label);
    new_label = QString::number(res[8], 'g', 15);
    ui->label_t_sr ->setText(new_label);
    new_label = QString::number(res[9], 'g', 15);
    ui->label_t_sl ->setText(new_label);

    new_label = QString::number(res[10], 'g', 15);
    ui->label_max_q ->setText(new_label);
    new_label = QString::number(res[11], 'g', 15);
    ui->label_sr_q ->setText(new_label);
    new_label = QString::number(res[12], 'g', 15);
    ui->label_max_t ->setText(new_label);
    new_label = QString::number(res[13], 'g', 15);
    ui->label_sr_t ->setText(new_label);

    new_label = QString::number(res[14], 'g', 15);
    ui->label_max_td ->setText(new_label);
    new_label = QString::number(res[15], 'g', 15);
    ui->label_sr_td ->setText(new_label);
    new_label = QString::number(res[16], 'g', 15);
    ui->label_non_r ->setText(new_label);
    new_label = QString::number(res[17], 'g', 15);
    ui->label_sum ->setText(new_label);

    //------------Гистограмма количества поступивших машин--------------------------
        QCustomPlot *customPlot1 = ui->customPlot;

        QCPBars *fossil1 = new QCPBars(customPlot1->xAxis, customPlot1->yAxis);

        customPlot1->addPlottable(fossil1);
        // Установки цвета:
        QPen pen1;
        pen1.setWidthF(1.5);//Толщина контура столбца
        fossil1->setName(QString::fromUtf8("Гистограмма")); // Легенда
        pen1.setColor(QColor(50, 50, 100));// Цвет контура столбца
        fossil1->setPen(pen1);
        // Цвет самого столбца, четвертый параметр - прозрачность
        fossil1->setBrush(QColor(50, 50, 250, 150));

        // Установки значений оси X:
        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2 << 3 << 4;
        labels << "ТО" << "Простой" << "Средний" << "Сложный";
        customPlot1->xAxis->setAutoTicks(false);
        customPlot1->xAxis->setAutoTickLabels(false);
        customPlot1->xAxis->setTickVector(ticks);
        customPlot1->xAxis->setTickVectorLabels(labels);
        customPlot1->xAxis->setSubTickCount(0);
        customPlot1->xAxis->setTickLength(0, 4);
        customPlot1->xAxis->grid()->setVisible(true);
        customPlot1->xAxis->setRange(0.5, 4.5);

        int max_r = std::max(res[1],res[2]);
        max_r = std::max(max_r,res[3]);
        max_r = std::max(max_r,res[4]);
        max_r +=3;


        // Установки значений оси Y:
        customPlot1->yAxis->setRange(0, max_r);
        customPlot1->yAxis->setPadding(5);
        //customPlot->yAxis->setLabel(QString::fromUtf8("Значения элементов"));
        customPlot1->yAxis->grid()->setSubGridVisible(true);
        QPen gridPen;
        gridPen.setStyle(Qt::SolidLine);
        gridPen.setColor(QColor(0, 0, 0, 25));
        customPlot1->yAxis->grid()->setPen(gridPen);
        gridPen.setStyle(Qt::DotLine);
        customPlot1->yAxis->grid()->setSubGridPen(gridPen);


        // Данные:
        QVector<double> fossilData1;
        fossilData1  << res[1]
                    << res[2]
                    << res[3]
                    << res[4];

        fossil1->setData(ticks, fossilData1);

        customPlot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        customPlot1->replot();

        // Сброс всех установок графика:
        customPlot1->removePlottable(fossil1);

    //------------Гистограмма среднего времени обслуживания машин--------------------------
        QCustomPlot *customPlot2 = ui->customPlot_2;

        QCPBars *fossil2 = new QCPBars(customPlot2->xAxis, customPlot2->yAxis);

        customPlot2->addPlottable(fossil2);
        // Установки цвета:
        QPen pen2;
        pen2.setWidthF(1.5);//Толщина контура столбца
        fossil2->setName(QString::fromUtf8("Гистограмма")); // Легенда
        pen2.setColor(QColor(50, 50, 100));// Цвет контура столбца
        fossil2->setPen(pen2);
        // Цвет самого столбца, четвертый параметр - прозрачность
        fossil2->setBrush(QColor(50, 50, 250, 150));

        // Установки значений оси X:
        customPlot2->xAxis->setAutoTicks(false);
        customPlot2->xAxis->setAutoTickLabels(false);
        customPlot2->xAxis->setTickVector(ticks);
        customPlot2->xAxis->setTickVectorLabels(labels);
        customPlot2->xAxis->setSubTickCount(0);
        customPlot2->xAxis->setTickLength(0, 4);
        customPlot2->xAxis->grid()->setVisible(true);
        customPlot2->xAxis->setRange(0.5, 4.5);

        int max_t = std::max(res[6],res[7]);
        max_t = std::max(max_t,res[8]);
        max_t = std::max(max_t,res[9]);
        max_t +=5;


        // Установки значений оси Y:
        customPlot2->yAxis->setRange(0, max_t);
        customPlot2->yAxis->setPadding(5);
        customPlot2->yAxis->grid()->setSubGridVisible(true);
        gridPen.setStyle(Qt::SolidLine);
        gridPen.setColor(QColor(0, 0, 0, 25));
        customPlot2->yAxis->grid()->setPen(gridPen);
        gridPen.setStyle(Qt::DotLine);
        customPlot2->yAxis->grid()->setSubGridPen(gridPen);


        // Данные:
        QVector<double> fossilData2;
        fossilData2  << res[6]
                    << res[7]
                    << res[8]
                    << res[9];

        fossil2->setData(ticks, fossilData2);

        customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        customPlot2->replot();

        // Сброс всех установок графика:
        customPlot2->removePlottable(fossil2);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString new_label;
    if (index == 0) {
        ui->label_39->hide();
        ui->label_38->hide();
        ui->lineEdit_9->hide();
        new_label = QString::fromUtf8 (u8"Среднее значение");
        ui->label_11->setText(new_label);
        new_label = QString::number(14, 'g', 15);
        ui->lineEdit_5->setText(new_label);
    }
    if (index == 1) {
        ui->label_39->show();
        ui->label_38->show();
        ui->lineEdit_9->show();
        new_label = QString::fromUtf8 (u8"Среднее значение");
        ui->label_11->setText(new_label);
        new_label = QString::fromUtf8 (u8"Отклонение");
        ui->label_39->setText(new_label);
        new_label = QString::number(30, 'g', 15);
        ui->lineEdit_5->setText(new_label);
        new_label = QString::number(10, 'g', 15);
        ui->lineEdit_9->setText(new_label);
    }
    if (index == 2) {
        ui->label_39->show();
        ui->label_38->show();
        ui->lineEdit_9->show();
        new_label = QString::fromUtf8 (u8"От ");
        ui->label_11->setText(new_label);
        new_label = QString::fromUtf8 (u8"До ");
        ui->label_39->setText(new_label);
        new_label = QString::number(10, 'g', 15);
        ui->lineEdit_5->setText(new_label);
        new_label = QString::number(60, 'g', 15);
        ui->lineEdit_9->setText(new_label);
    }
}
