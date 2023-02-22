#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager() override;

signals:

private:

    class PluginManager_Pimpl;
    std::unique_ptr<PluginManager_Pimpl> pimpl;
};

#endif // PLUGINMANAGER_H
