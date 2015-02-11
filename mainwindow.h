#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QStringListModel>
#include <QtSerialPort/QSerialPortInfo>
#include <QSet>
#include <QTimer>

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
    void updatePorts();

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
    QList<QSerialPortInfo> portInfo;
};

#endif // MAINWINDOW_H
