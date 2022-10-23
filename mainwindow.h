#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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
    void closeEvent(QCloseEvent * e) override;

public slots:
    void quitApp();
    void openFile();
    void saveFile();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
