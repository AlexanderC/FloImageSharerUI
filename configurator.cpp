#include "configurator.h"

Configurator::Configurator(QString path)
{
    this->settings = new QSettings(path, QSettings::IniFormat);

    if(!this->settings->isWritable()) {
        throw new SettingsFileLockedException();
    }

    this->setUrl(this->settings->value("url").toString());

    int max = this->settings->beginReadArray("paths");
    for(int i = 0; i < max; ++i) {
        this->settings->setArrayIndex(i);
        this->addPath(this->settings->value("path").toString());
    }
    this->settings->endArray();
}

Configurator::~Configurator()
{
    this->update();
}

void Configurator::addPath(QString path)
{
    this->paths.push_back(path);
}

void Configurator::setUrl(QString url)
{
    this->serviceUrl = url;
}

QString Configurator::getUrl()
{
    return this->serviceUrl;
}

vector<QString>& Configurator::getPaths()
{
    return this->paths;
}

void Configurator::update()
{
    this->settings->clear();

    this->settings->setValue("url", this->getUrl());

    this->settings->beginWriteArray("paths");
    int i = 0;
    for(auto & path: this->getPaths()) {
        this->settings->setArrayIndex(i);
        this->settings->setValue("path", path);
        i++;
    }
    this->settings->endArray();

    this->settings->sync();
}

