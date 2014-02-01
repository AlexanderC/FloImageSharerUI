#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stopButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConfigurator(Configurator* configurator)
{
    this->config = configurator;
}

void MainWindow::setRuntime(Runtime* runtime)
{
    this->runtime = runtime;
}

void MainWindow::fillFromConfiguration()
{
    ui->serviceUrl->setText(this->config->getUrl());

    ui->pathsList->clear();
    for(auto & path: this->config->getPaths()) {
        ui->pathsList->addItem(path);
    }
}

void MainWindow::on_folderAdd_pressed()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setDirectory(QDir::homePath());

    QStringList dirs;
    if (dialog.exec()) {
        dirs = dialog.selectedFiles();

        foreach(const QString &path, dirs) {
            this->config->addPath(path);
            ui->pathsList->addItem(path);

            RT_INSTANCE instance = this->runtime->createAddInstance(this->config->getUrl(), path);

            // start this instance if all running
            if(!ui->startButton->isEnabled()) {
                this->runtime->start(instance);
            }
        }
    }
}

void MainWindow::on_serviceUrl_textChanged(const QString &arg1)
{
    this->config->setUrl((QString) arg1);
}

void MainWindow::on_startButton_pressed()
{
    ui->startButton->setDisabled(true);
    ui->stopButton->setEnabled(true);

    this->runtime->startAll();
}

void MainWindow::on_stopButton_pressed()
{
    ui->startButton->setDisabled(false);
    ui->stopButton->setEnabled(false);

    this->runtime->stopAll();
}

void MainWindow::on_pathsList_itemPressed(QListWidgetItem *item)
{
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Please Confirm", "Do you realy want to stop sharing this folder? (needs restart)",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
            QString path = item->text();

            int i = 0;
            std::vector<QString>::iterator rmPos;
            for(auto & curPath: this->config->getPaths()) {
                if(path == curPath) {
                    rmPos = this->config->getPaths().begin() + i;
                }
                i++;
            }

            this->config->getPaths().erase(rmPos);

            item->listWidget()->takeItem(item->listWidget()->row(item));
      }
}
