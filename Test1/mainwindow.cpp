#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rowcount = 1;
    int columncount = 37;
    ui->tableWidget->setRowCount(rowcount);
    ui->tableWidget->setColumnCount(columncount);
    for(int i=0;i<columncount;i++)
    {
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(QString("Value %1").arg(i)));
    }

    report->dataManager()->addModel("tablewidget",ui->tableWidget->model(),false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    report ->designReport();
}

