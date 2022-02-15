#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rowcount = 3;
    int columncount = 37;
    QStandardItemModel *model = new QStandardItemModel(rowcount,columncount);


    for(int j = 0; j<rowcount;j++)
    for(int i =0; i<columncount;i++)
    {
        QStandardItem *item = new QStandardItem(QString("Value %1 %2").arg(i).arg(j));
        model->setItem(j,i,item);
    }

    ui->tableView->setModel(model);
    report->dataManager()->addModel("tablewidget", ui->tableView->model(),false);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete report;
}


void MainWindow::on_pushButton_clicked()
{

    report->previewReport();
}


void MainWindow::on_pushButton_2_clicked()
{


   QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
        "", tr("PDF (*.pdf);; All Files (*)"));
   if (filename.isEmpty())
          return;
      else
   {
          QFile file(filename);

          if (!file.open(QIODevice::WriteOnly))
          {
              QMessageBox::information(this, tr("Unable to open file"),
                  file.errorString());
              return;
          }
          QDataStream out(&file);
           out<< report->printToPDF("/Test1.lrxml");

     }

}

