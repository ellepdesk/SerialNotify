#include "updater.h"

QString Updater::popNotificationMessage()
{
    QString m = message;
    message = "";
    return m;
}

QStringList Updater::getItemList()
{
    return itemList;
}
