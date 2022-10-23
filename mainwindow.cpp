#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <iostream>
#include <QToolBar>
#include <QSaveFile>
#include <QMessageBox>
#include <QCloseEvent>
#include "tp2.h"


using namespace std;

#define textEditor


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    QMenuBar * menuBar = this->menuBar();
    QMenu * menu = menuBar->addMenu(tr("&File") ); // adds a pulldown menu
    QToolBar *fileToolBar = this->addToolBar(tr("File"));

    QAction * actionOpen = new QAction(QIcon(":/images/new-document.png"), tr("&Open..."), this );
    QAction * actionSave = new QAction( QIcon(":/images/diskette.png"), tr("&Save..."), this );
    QAction * actionQuit = new QAction( QIcon(":/images/sign-out.png"), tr("&Quit..."), this );
    fileToolBar->addAction(actionOpen);
    fileToolBar->addAction(actionSave);
    fileToolBar->addAction(actionQuit);
    TP2 * centerBox = new TP2();
#ifdef textEditor
    MainWindow::text = new QTextEdit(this);
    this->setCentralWidget(text);
#else
    this->setCentralWidget(centerBox);
#endif

    menu->addAction(actionOpen);
    menu->addAction(actionSave);
    menu->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quitApp()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    //ui->setupUi(this);

}

void MainWindow::quitApp(){

    QMessageBox * quitBox = new QMessageBox();
    quitBox->setText("Are you sure you want to close this program?");
    quitBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    quitBox->setDefaultButton(QMessageBox::Yes);
    int ret = quitBox->exec();
    switch (ret){
        case QMessageBox::Yes:

            this->~MainWindow();
        break;
        case QMessageBox::No:
            quitBox->~QMessageBox();
        break;
    }

    //this->~MainWindow();
}

void MainWindow::openFile(){
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream out(&file);
        QString fullText = out.readAll();
        MainWindow::text->setHtml(fullText);
    }
}

void MainWindow::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << MainWindow::text->toPlainText();
    }
}

void MainWindow::closeEvent(QCloseEvent * e){
    e->ignore();
    this->quitApp();

}


MainWindow::~MainWindow()
{
    delete ui;
}


