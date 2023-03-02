#include "pluginmanager.h"
#include "audiopluginholder.h"

#include "juce-stubs/juce_config.h"
#include <juce_audio_processors/juce_audio_processors.h>

#include <QComboBox>


class PluginManager::PluginManager_Pimpl
{
public:
    PluginManager_Pimpl()
    {
        manager.addDefaultFormats();

        // read JUCE AudioPluginHost plugin list
        auto pluginFile = juce::File::getSpecialLocation (juce::File::userHomeDirectory)
                .getChildFile ("Library")
                .getChildFile ("Preferences")
                .getChildFile ("Juce Audio Plugin Host.settings");

        auto pluginXml = juce::XmlDocument::parse (pluginFile);
        if (pluginXml)
        {
            if (auto* pluginList = pluginXml->getChildByAttribute("name", "pluginList"))
            {
                if (auto* knownPlugins = pluginList->getChildByName("KNOWNPLUGINS"))
                {
                    plugins.recreateFromXml (*knownPlugins);
                }
            }
        }

        DBG ("Found " + juce::String (plugins.getNumTypes()) + " plugins");
    }

    QList<PluginType> getPluginTypes() const
    {
        QList<PluginType> types;

        for (const auto& pluginType : plugins.getTypes())
            types.append({
                             pluginType.createIdentifierString().toRawUTF8(),
                             pluginType.name.toRawUTF8(),
                             pluginType.manufacturerName.toRawUTF8(),
                             pluginType.isInstrument ? Option::Instrument : Option::Effect
                        });

        return types;
    }

    std::unique_ptr<AudioPluginHolder> createPluginInstance (const QString& pluginID) const
    {
        auto holder = std::make_unique<AudioPluginHolder>();
        if (auto description = plugins.getTypeForIdentifierString (pluginID.toUtf8().constData()))
        {
            juce::String errorMessage;
            auto instance = manager.createPluginInstance (*description, 48000.0, 1024, errorMessage);

            if (errorMessage.isEmpty())
            {
                holder->setAudioProcessor (std::move (instance));
            }
            else
            {
                DBG ("Error creating instance: " + errorMessage);
            }

        }
        return holder;
    }

    juce::AudioPluginFormatManager manager;
    juce::KnownPluginList          plugins;
};


PluginManager::PluginManager(QObject *parent)
    : QObject{parent},
      pimpl{std::make_unique<PluginManager_Pimpl>()}
{

}

PluginManager::~PluginManager() {}

QList<PluginManager::PluginType> PluginManager::getPluginTypes() const
{
    return pimpl->getPluginTypes();
}

void PluginManager::populateComboBox (QComboBox* combo, Options which, std::function<void(const QString& pluginID)> selectionFunc) const
{
    for (const auto& pluginType : pimpl->getPluginTypes())
        if (which.testFlag (pluginType.kind))
            combo->addItem (pluginType.name, pluginType.pluginID);

    QObject::connect (combo, QOverload<int>::of (&QComboBox::currentIndexChanged),
                      this, [combo, selectionFunc](int index)
    {
        selectionFunc (combo->itemData (index).toString());
    });
}


std::unique_ptr<AudioPluginHolder> PluginManager::createPluginInstance (const QString& pluginID) const
{
    return pimpl->createPluginInstance (pluginID);
}


