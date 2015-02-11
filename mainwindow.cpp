#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    CreateTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    portNameList = new QStringListModel();
    ui->portList->setModel(portNameList);
    ui->menuSerialNotifier->addAction(quitAction);
    updatePorts();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePorts()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePorts()
{
    QList<QSerialPortInfo> freshPortInfo = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo> newPortInfo;
    QList<QSerialPortInfo> removedPortInfo;

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

    QString message = "";
    bool newPorts = false;
    for (int i = 0; i < newPortInfo.length(); i++)
    {
        message += newPortInfo.at(i).portName() + "\n";
        newPorts = true;
    }
    if(newPorts)
    {
        trayIcon->showMessage("Serial Port(s) Found", message);
    }

    QStringList list;
    for (int i = 0; i < freshPortInfo.length(); i++)
    {
        QSerialPortInfo p = freshPortInfo.at(i);
        list << p.portName() + "\t" +  p.manufacturer() + " " + p.description() ;
    }
    portInfo = freshPortInfo;
    portNameList->setStringList(list);
}

void MainWindow::updateMenu()
{
    trayIconMenu->clear();
    for (int i = 0; i < portInfo.length(); i++)
    {
        trayIconMenu->addAction(portInfo.at(i).portName());
    }
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

}

void MainWindow::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::CreateTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QIcon(":/images/serial.png");
    trayIcon->setIcon(icon);

    trayIcon->show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        toggleUi();
        break;
    case QSystemTrayIcon::Context:
        updateMenu();
        break;
    default:
        updatePorts();
    }
}

void MainWindow::toggleUi()
{
    if (isVisible())
        hide();
    else
        show();
}

