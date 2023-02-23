#include "pluginmanager.h"
#include "audiopluginholder.h"


#include "juce-stubs/juce_config.h"
#include <juce_audio_processors/juce_audio_processors.h>


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
                             pluginType.fileOrIdentifier.toRawUTF8(),
                             pluginType.name.toRawUTF8(),
                             pluginType.manufacturerName.toRawUTF8()
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

std::unique_ptr<AudioPluginHolder> PluginManager::createPluginInstance (const QString& pluginID) const
{
    return pimpl->createPluginInstance (pluginID);
}


