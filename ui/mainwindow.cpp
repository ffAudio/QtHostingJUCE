#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "audio/pluginmanager.h"
#include "audio/audiopluginholder.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pluginManager.populateComboBox (ui->pluginSelect, PluginManager::Effect, [this](const QString& pluginID)
    {
        auto instance = pluginManager.createPluginInstance (pluginID);
        audioPlayer.setPlugin (std::move (instance));
    });

    QObject::connect (ui->pluginEditor, SIGNAL (clicked()),
                      &audioPlayer,     SLOT (showEditor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

