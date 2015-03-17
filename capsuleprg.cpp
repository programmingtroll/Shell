#include "capsuleprg.h"


QString capsulePrg::getName() const
{
    return name;
}

void capsulePrg::setName(const QString &value)
{
    name = value;
}

void capsulePrg::insertParam(int pos, QString param)
{
    params.insert(pos,param);
}

capsulePrg::capsulePrg(QString name)
{
    this->name = name;
    this->programPath = "";
}

capsulePrg::capsulePrg(QString name, QStringList params)
{
    this->name = name;
    this->params = params;
    this->programPath = "";
}

capsulePrg::capsulePrg(QString name, QString params)
{
    this->name = name;
    this->params = params.split(" ",QString::SkipEmptyParts);
    this->programPath = "";
}

capsulePrg::~capsulePrg()
{

}

QString capsulePrg::getProgramPath() const
{
    return programPath;
}

void capsulePrg::setProgramPath(const QString &value)
{
    programPath = value;
}

QStringList capsulePrg::getParams() const
{
    return params;
}

void capsulePrg::setParams(const QStringList &value)
{
    params = value;
}


