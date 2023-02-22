#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "audioplayer.h"
#include "pluginmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    AudioPlayer     audioPlayer;
    PluginManager   pluginManager;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
