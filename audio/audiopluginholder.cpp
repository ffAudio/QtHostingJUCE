
#include "audiopluginholder.h"

#include "juce-stubs/juce_config.h"
#include <juce_audio_processors/juce_audio_processors.h>

#include <QPointer>


AudioPluginWindow::AudioPluginWindow (QWidget* parent)
    : QWidget (parent, Qt::Tool | Qt::WindowStaysOnTopHint)
{
    setVisible (true);
    raise();
}

AudioPluginWindow::~AudioPluginWindow()
{

}

void AudioPluginWindow::setAudioProcessorEditor (juce::AudioProcessorEditor* editorToUse)
{
    editor.reset (editorToUse);
    editor->addToDesktop (0, (void*)winId());
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

        window = new AudioPluginWindow(nullptr);
        window->setAudioProcessorEditor (processor->createEditor());
    }

    std::unique_ptr<juce::AudioProcessor> processor;
    QPointer<AudioPluginWindow>           window;

};

// ================================================================================

AudioPluginHolder::AudioPluginHolder (QObject *parent)
    : QObject {parent},
      pimpl {std::make_unique<AudioPluginHolder_Pimpl>()}
{}

AudioPluginHolder::~AudioPluginHolder()
{
    if (pimpl->window)
    {
        pimpl->window->close();
        delete pimpl->window;
    }
}

void AudioPluginHolder::setAudioProcessor (std::unique_ptr<juce::AudioProcessor> processorToUse)
{
    pimpl->processor = std::move (processorToUse);
}

void AudioPluginHolder::prepareToPlay (double sampleRate, int blockSize)
{
    if (pimpl->processor)
        pimpl->processor->prepareToPlay (sampleRate, blockSize);
}

void AudioPluginHolder::releaseResources()
{
    if (pimpl->processor)
        pimpl->processor->releaseResources();
}

void AudioPluginHolder::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    if (pimpl->processor)
        pimpl->processor->processBlock (buffer, midi);
}


void AudioPluginHolder::showEditor()
{
    pimpl->showEditor();
}
