#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QStringListModel>
#include <QSet>
#include <QTimer>
#include "updater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateAll();

private:
    void CreateTrayIcon();
    void createActions();
    void toggleUi();
    void updateMenu();

    Ui::MainWindow *ui;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QStringListModel *portNameList;
    QStringList list;
    QSet<Updater*> updaters;
};

#endif // MAINWINDOW_H
