#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <vector>
#include "configurator.h"
#include "runtime.h"
#include "exceptions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    Configurator* config;
    Runtime* runtime;

public:
    void setConfigurator(Configurator* configurator);
    void setRuntime(Runtime* runtime);
    void fillFromConfiguration();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_folderAdd_pressed();

    void on_serviceUrl_textChanged(const QString &arg1);

    void on_startButton_pressed();

    void on_stopButton_pressed();

    void on_pathsList_itemPressed(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
