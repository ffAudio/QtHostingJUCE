#include "pluginmanager.h"


#include "juce-stubs/juce_config.h"
#include <juce_audio_processors/juce_audio_processors.h>


class PluginManager::PluginManager_Pimpl
{
public:
    PluginManager_Pimpl()
    {
        manager.addDefaultFormats();

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
