#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class AudioPluginHolder;
class QComboBox;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    enum Option
    {
        Effect     = 0x1,
        Instrument = 0x2,
        MidiEffect = 0x4
    };
    Q_DECLARE_FLAGS (Options, Option)

    struct PluginType
    {
        QString pluginID;
        QString name;
        QString manufacturer;
        Option  kind;
    };

    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager() override;

    QList<PluginType> getPluginTypes() const;

    void populateComboBox (QComboBox* combo, Options which, std::function<void(const QString& pluginID)> selectionFunc) const;

    std::unique_ptr<AudioPluginHolder> createPluginInstance (const QString& pluginID) const;


signals:

private:

    class PluginManager_Pimpl;
    std::unique_ptr<PluginManager_Pimpl> pimpl;
};

Q_DECLARE_OPERATORS_FOR_FLAGS (PluginManager::Options)

#endif // PLUGINMANAGER_H
