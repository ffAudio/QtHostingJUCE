
#include "audiopluginholder.h"

#include "juce-stubs/juce_config.h"
#include <juce_audio_processors/juce_audio_processors.h>


AudioPluginWindow::AudioPluginWindow()
{
    setWindowFlags (Qt::Tool);
    raise();
}

AudioPluginWindow::~AudioPluginWindow()
{

}

void AudioPluginWindow::setAudioProcessorEditor (juce::AudioProcessorEditor* editorToUse)
{
    editor.reset (editorToUse);
    editor->addToDesktop (winId());
    editor->setVisible (true);

    resize (editor->getWidth(), editor->getHeight());
}


// ================================================================================

class AudioPluginHolder::AudioPluginHolder_Pimpl
{
public:
    AudioPluginHolder_Pimpl()
    {

    }

    void showEditor()
    {
        if (!processor)
            return;

        if (window)
        {
            window->raise();
            return;
        }

        window = std::make_unique<AudioPluginWindow>();
        window->setAudioProcessorEditor (processor->createEditor());

    }

    std::unique_ptr<juce::AudioProcessor> processor;
    std::unique_ptr<AudioPluginWindow>    window;

};

// ================================================================================

AudioPluginHolder::AudioPluginHolder (QObject *parent)
    : QObject {parent},
      pimpl {std::make_unique<AudioPluginHolder_Pimpl>()}
{}

AudioPluginHolder::~AudioPluginHolder() {}

void AudioPluginHolder::setAudioProcessor (std::unique_ptr<juce::AudioProcessor> processor)
{
    pimpl->processor = std::move (processor);
}

void AudioPluginHolder::showEditor()
{

}
