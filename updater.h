#ifndef UPDATER_H
#define UPDATER_H
#include <QMenu>
#include <QString>
#include <QStringList>


class Updater
{
public:
    Updater() {};
    virtual ~Updater() {};
    virtual bool update() = 0;
    virtual void updateMenu(QMenu*) = 0;
    QString popNotificationMessage();
    QStringList getItemList();

protected:
    QString message;
    QStringList itemList;
};

#endif // UPDATER_H
