#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QStandardItemModel>
#include "lrreportengine.h"
#include "lrcallbackdatasourceintf.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QProgressDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    LimeReport::ReportEngine *report;
    void renderStarted();
    void renderPageFinished(int renderedPageCount);
    void renderFinished();
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QProgressDialog* m_progressDialog;
    int m_currentPage;
};
#endif // MAINWINDOW_H
