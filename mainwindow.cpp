#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>
#include <iostream>
#include <QToolBar>
#include <QSaveFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>
#include "tp2.h"


using namespace std;

//#define textEditor


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenuBar * menuBar = this->menuBar();
    QMenu * menu = menuBar->addMenu(tr("&File") ); // adds a pulldown menu
    QToolBar *fileToolBar = this->addToolBar(tr("File"));

    QAction * actionOpen = new QAction(QIcon(":/images/new-document.png"), tr("&Open..."), this );
    QAction * actionSave = new QAction( QIcon(":/images/diskette.png"), tr("&Save..."), this );
    QAction * actionQuit = new QAction( QIcon(":/images/sign-out.png"), tr("&Quit..."), this );
    fileToolBar->addAction(actionOpen);
    fileToolBar->addAction(actionSave);
    fileToolBar->addAction(actionQuit);
    centerBox = new TP2();
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

    QMenu * menuDrawing = menuBar->addMenu(tr("&Pen"));


    QAction * chooseColor = new QAction(tr("&Color..."), this);
    QAction * changeThickness = new QAction(tr("&Thickness..."), this);
    menuDrawing->addAction(chooseColor);
    menuDrawing->addAction(changeThickness);
    connect(chooseColor, SIGNAL(triggered()), this, SLOT(changeColor()));
    connect(changeThickness, SIGNAL(triggered()), this, SLOT(changeLineWidth()));

    QMenu * menuPenStyle = menuDrawing->addMenu(tr("&Style..."));
    QAction * solidLine = new QAction(tr("&Solid line..."), this);
    QAction * dashedLine = new QAction(tr("&Dashed line..."), this);
    QAction * dotLine = new QAction(tr("&Dot line..."), this);
    menuPenStyle->addAction(solidLine);
    menuPenStyle->addAction(dashedLine);
    menuPenStyle->addAction(dotLine);

    connect(solidLine, &QAction::triggered, this,  [this]{changeLineStyle(0);});
    connect(dashedLine, &QAction::triggered, this, [this]{changeLineStyle(1);});
    connect(dotLine, &QAction::triggered, this, [this]{changeLineStyle(2);});

    QMenu * chooseShape = menuBar->addMenu(tr("&Shape"));
    QAction * line = new QAction(tr("&Line..."), this);
    QAction * rect = new QAction(tr("&Rectangle..."), this);
    QAction * ellipse = new QAction(tr("&Ellipse..."), this);
    chooseShape->addAction(line);
    chooseShape->addAction(rect);
    chooseShape->addAction(ellipse);
    connect(line, &QAction::triggered, this,  [this]{setShape(0);});
    connect(rect, &QAction::triggered, this, [this]{setShape(1);});
    connect(ellipse, &QAction::triggered, this, [this]{setShape(2);});
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


void MainWindow::changeColor(){
    QColor color = QColorDialog::getColor(QColor(255, 0, 0, 255));
  if (color.isValid())
      centerBox->set_color(color);
}


void MainWindow::changeLineWidth(){
  int newWidth = QInputDialog::getInt(this, tr("Pen width"), tr("Pen width:"), centerBox->get_width(), 1, 10, 1);
  centerBox->set_width(newWidth);
}

void MainWindow::changeLineStyle(int styleOption){
    centerBox->setLineStyle(styleOption);
}

void MainWindow::setShape(int shapeOption){
    centerBox->setActiveShape(shapeOption);
}

MainWindow::~MainWindow()
{
    delete ui;
}


