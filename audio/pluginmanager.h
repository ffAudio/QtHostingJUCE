#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class AudioPluginHolder;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    struct PluginType
    {
        QString pluginID;
        QString name;
        QString manufacturer;
    };


    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager() override;

    QList<PluginType> getPluginTypes() const;

    std::unique_ptr<AudioPluginHolder> createPluginInstance (const QString& pluginID) const;


signals:

private:

    class PluginManager_Pimpl;
    std::unique_ptr<PluginManager_Pimpl> pimpl;
};

#endif // PLUGINMANAGER_H
