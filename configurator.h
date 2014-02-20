#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <cstdlib>
#include <vector>
#include <QString>
#include <QSettings>
#include "exceptions.h"

using namespace std;

class Configurator
{
protected:
    vector<QString> paths;
    QString serviceUrl;
    QSettings* settings = 0;

public:
    Configurator(QString path);
    ~Configurator();

public:
    void addPath(QString path);
    void setUrl(QString url);
    vector<QString>& getPaths();
    QString getUrl();

    void update();
};

#endif // CONFIGURATOR_H
