#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_progressDialog(0)
{
    ui->setupUi(this);
    report = new LimeReport::ReportEngine(this);

    connect(report, SIGNAL(renderStarted()), this, SLOT(renderStarted()));
    connect(report, SIGNAL(renderPageFinished(int)),
            this, SLOT(renderPageFinished(int)));
    connect(report, SIGNAL(renderFinished()), this, SLOT(renderFinished()));

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


void MainWindow::on_pushButton_3_clicked()
{
    QString testname = "Test";
    QVariant testvalue = "TestValue";
    //report->createPreviewWidget();

    //Load File Dialog
    QString filename = QFileDialog::getOpenFileName(this,"Select report file",QApplication::applicationDirPath(),"*.lrxml");
    QFile file(filename);
    if(!filename.isEmpty())
    {
        report->loadFromFile(filename);
        report->dataManager()->setReportVariable(testname,testvalue);
        report->setShowProgressDialog(true);
        report->previewReport();

    }
}

void MainWindow::renderStarted()
{
    if (report->isShowProgressDialog()){
        m_currentPage = 0;
        m_progressDialog = new QProgressDialog(tr("Start render"),tr("Cancel"),0,0,this);
        //m_progressDialog->setWindowModality(Qt::WindowModal);
        connect(m_progressDialog, SIGNAL(canceled()), report, SLOT(cancelRender()));
        QApplication::processEvents();
        m_progressDialog->show();
    }
}

void MainWindow::renderPageFinished(int renderedPageCount)
{
    if (m_progressDialog){
        m_progressDialog->setLabelText(QString::number(renderedPageCount)+tr(" page rendered"));
        m_progressDialog->setValue(renderedPageCount);
    }
}

void MainWindow::renderFinished()
{
    if (m_progressDialog){
        m_progressDialog->close();
        delete m_progressDialog;
    }
    m_progressDialog = 0;
}
