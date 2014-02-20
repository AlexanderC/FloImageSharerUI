#include <QApplication>
#include <QDebug>

#include "exceptions.h"
#include "mainwindow.h"
#include "configurator.h"
#include "runtime.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir d;
    QString settingsFile = d.absolutePath() + QString("/settings.ini");
#ifdef _WIN32
    QString binaryFile = d.absolutePath() + QString("/bin/FloImageSharerDaemon.exe");
#else
    QString binaryFile = d.absolutePath() + QString("/bin/FloImageSharerDaemon");
#endif

    qDebug() << "Working Path: " << d.absolutePath();

    Configurator* configurator = new Configurator(settingsFile);
    Runtime* runtime = new Runtime(binaryFile, d.absolutePath() + QString("/logs"));

    for(auto & path: configurator->getPaths()) {
        runtime->createAddInstance(configurator->getUrl(), path);
    }

    MainWindow w;
    w.setConfigurator(configurator);
    w.setRuntime(runtime);
    w.fillFromConfiguration();
    w.show();

    int result = a.exec();

    delete runtime;
    delete configurator;

    return result;
}
