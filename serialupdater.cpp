#include "serialupdater.h"

SerialUpdater::SerialUpdater()
{
}

SerialUpdater::~SerialUpdater()
{
}

bool SerialUpdater::update()
{
    QList<QSerialPortInfo> freshPortInfo = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo> newPortInfo;
    QList<QSerialPortInfo> removedPortInfo;

    itemList.clear();

    //find new ports
    for (int i = 0; i < freshPortInfo.length(); i++)
    {
        bool match = false;
        for (int j = 0; j < portInfo.length(); j++)
        {
            //match name against all previous ports
            if (freshPortInfo.at(i).portName() == portInfo.at(j).portName())
            {
                match = true;
                break;
            }
        }
        if (!match)
        {
            newPortInfo.push_back(QSerialPortInfo(freshPortInfo.at(i)));
        }
    }

    //find removed ports
    for (int i = 0; i < portInfo.length(); i++)
    {
        bool match = false;
        for (int j = 0; j < freshPortInfo.length(); j++)
        {
            //match name against all new ports
            if (portInfo.at(i).portName() == freshPortInfo.at(j).portName())
            {
                match = true;
                break;
            }
        }
        if (!match)
        {
            removedPortInfo.push_back(QSerialPortInfo(portInfo.at(i)));
        }
    }

    bool newPorts = false;
    for (int i = 0; i < newPortInfo.length(); i++)
    {
        message += newPortInfo.at(i).portName() + "\n";
        newPorts = true;
    }

    for (int i = 0; i < freshPortInfo.length(); i++)
    {
        QSerialPortInfo p = freshPortInfo.at(i);
        itemList << p.portName() + "\t" +  p.manufacturer() + " " + p.description() ;
    }
    portInfo = freshPortInfo;
    return newPorts;
}

void SerialUpdater::updateMenu(QMenu* menu)
{
    for (int i = 0; i < portInfo.length(); i++)
    {
        menu->addAction(portInfo.at(i).portName());
    }
}
