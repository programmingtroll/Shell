#ifndef CAPSULEPRG_H
#define CAPSULEPRG_H
#include <QString>
#include <QStringList>

class capsulePrg
{
   QString name;
   QString programPath;
   QStringList params;
public:
    capsulePrg(QString, QStringList);
    capsulePrg(QString, QString);
    ~capsulePrg();
    QString getProgramPath() const;
    void setProgramPath(const QString &value);
    QStringList getParams() const;
    void setParams(const QStringList &value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // CAPSULEPRG_H
