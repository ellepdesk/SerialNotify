#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialupdater.h"
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

    updaters << new SerialUpdater();

    updateAll();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAll()));
    timer->start(1000);
    portNameList->setStringList(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAll()
{
    QString message = "";
    list.clear();
    foreach(Updater* u, updaters)
    {
        u->update();
        message += u->popNotificationMessage();
        list += u->getItemList();
    }
    if (message != "")
    {
        trayIcon->showMessage("HW Changed", message);
    }
    updateMenu();
    portNameList->stringList().clear();
    portNameList->setStringList(list);
}

void MainWindow::updateMenu()
{
    trayIconMenu->clear();

    foreach(Updater* u, updaters)
    {
       u->updateMenu(trayIconMenu);
       trayIconMenu->addSeparator();
    }

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
        break;
    default:
        updateAll();
    }
}

void MainWindow::toggleUi()
{
    if (isVisible())
    {
        hide();
    }
    else
    {
        show();\
        raise();
    }
}
