#include "pluginmanager.h"


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

    juce::AudioPluginFormatManager manager;
    juce::KnownPluginList          plugins;
};


PluginManager::PluginManager(QObject *parent)
    : QObject{parent},
      pimpl{std::make_unique<PluginManager_Pimpl>()}
{

}

PluginManager::~PluginManager() {}
