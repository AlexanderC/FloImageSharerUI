#include "runtime.h"

Runtime::Runtime(QString binary, QString logsDir)
{
    this->binaryPath = binary;
    this->logsDir = logsDir;
}

Runtime::~Runtime()
{
    // do not allow processes running
    this->stopAll();
}

vector<RT_INSTANCE> Runtime::getInstances()
{
    return this->instances;
}

void Runtime::restart(RT_INSTANCE instance)
{
    this->stop(instance);
    this->start(instance);
}


void Runtime::stop(RT_INSTANCE instance)
{
    qDebug() << "Stopping Share Daemon (" << instance.process->pid() << ")";

    instance.process->terminate();
}

void Runtime::start(RT_INSTANCE instance)
{
    instance.process->start(
                instance.binary,
                this->getArgsFromUrlAndPath(instance.url, instance.folder)
                );

    qDebug() << "Starting Share Daemon (" << instance.process->pid() << ")";
}

RT_INSTANCE Runtime::createAddInstance(QString url, QString folder)
{
    RT_INSTANCE instance;

    instance.folder = folder;
    instance.url = url;
    instance.binary = this->binaryPath;
    instance.process = this->createProcess();

    this->instances.push_back(instance);

    return instance;
}

void Runtime::restartAll()
{
    for (auto & instance : this->instances) {
        this->restart(instance);
    }
}

void Runtime::startAll()
{
    for (auto & instance : this->instances) {
        this->start(instance);
    }
}

void Runtime::stopAll()
{
    for (auto & instance : this->instances) {
        this->stop(instance);
    }
}

QStringList Runtime::getArgsFromUrlAndPath(QString url, QString path)
{
    QStringList arguments;
    arguments << path << url;

    return arguments;
}

QProcess* Runtime::createProcess()
{
    QProcess* process = new QProcess();

    QString logFile = this->logsDir + QString("/") + QDate::currentDate().toString() + QString("_log.txt");

    process->setStandardErrorFile(logFile, QIODevice::Append);
    process->setStandardOutputFile(logFile, QIODevice::Append);

    return process;
}
