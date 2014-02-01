#ifndef RUNTIME_H
#define RUNTIME_H

#include <cstdlib>
#include <vector>
#include <map>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QDate>

using namespace std;

typedef struct RT_INSTANCE {
    QString folder;
    QString url;
    QProcess* process;
    QString binary;
} RT_INSTANCE;

class Runtime
{
protected:
    vector<RT_INSTANCE> instances;
    QString binaryPath;
    QString logsDir;

public:
    Runtime(QString binary, QString logsDir);
    ~Runtime();

public:
    vector<RT_INSTANCE> getInstances();
    void restart(RT_INSTANCE instance);
    void stop(RT_INSTANCE instance);
    void start(RT_INSTANCE instance);
    RT_INSTANCE createAddInstance(QString url, QString folder);
    void restartAll();
    void startAll();
    void stopAll();

protected:
    QStringList getArgsFromUrlAndPath(QString url, QString path);
    QProcess* createProcess();
};

#endif // RUNTIME_H
