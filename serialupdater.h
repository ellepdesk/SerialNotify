#ifndef SERIALUPDATER_H
#define SERIALUPDATER_H
#include "updater.h"
#include <QtSerialPort/QSerialPortInfo>



class SerialUpdater : public Updater
{
public:

    SerialUpdater();
    ~SerialUpdater();

    virtual bool update();
    virtual void updateMenu(QMenu*);
    QString popNotificationMessage();

private:
    Q_DISABLE_COPY(SerialUpdater);
    QList<QSerialPortInfo> portInfo;
};

#endif // SERIALUPDATER_H
