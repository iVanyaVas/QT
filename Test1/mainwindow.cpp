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

    report->dataManager()->addModel("tablewidget",model,false);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete report;
}


void MainWindow::on_pushButton_clicked()
{
    //report->printToPDF("Test");

}


void MainWindow::on_pushButton_2_clicked()
{
//
}


void MainWindow::on_pushButton_3_clicked()
{
    report->createPreviewWidget(ui->tableWidget);

    //Load File Dialog
    QString filename = QFileDialog::getOpenFileName((QWidget* )0, "Load Sample", QString(), "*.lrxml");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

   // while (!file.atEnd()) {
     //   QByteArray line = file.readLine();
      //  list->append(line);
    //}

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filename);
    //report->printToPDF(filename);
    //report->printReport(&printer);

    report->previewReport(&printer);



    //Save PDF file Dialog
   // QString filename_1 = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
   // if (QFileInfo(filename_1).suffix().isEmpty())
   // {
   //     filename_1.append(".pdf");
   // }




    //QList<QString> *list = new QList<QString>();
   /* QPainter painter(&printer);
    int counter = 0;
    for(auto i: *list)
    {
           painter.drawText(0,counter,i);
           counter+=20;
    }

    painter.end();*/

    //QString filename("D:/Programs/QtProjects/build-Test1-Desktop_Qt_5_12_12_MinGW_64_bit-Release/Test.pdf");
     report->printReport(&printer);
    // delete list;
}

