#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<int> vecDefiTime = {10, 55, 12, 45, 45, 5, 80, 150};
    std::vector<int>  vecDefiCost = {100, 400, 50, 450, 100, 1400, 350, 2550};


    std::vector<int> getVecDefiTime() const;

public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void onSignal(std::vector<int> vecT, std::vector<int> vecC);

private:
    Ui::MainWindow *ui;
    Dialog *myDialog;
};
#endif // MAINWINDOW_H
