#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "tp2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTextEdit * text;
    TP2 * centerBox;
    void closeEvent(QCloseEvent * e) override;

public slots:
    void quitApp();
    void openFile();
    void saveFile();
    void changeColor();
    void changeLineWidth();
    void changeLineStyle(int styleOption);
    void setShape(int shapeOption);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
