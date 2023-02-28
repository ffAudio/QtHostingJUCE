

#include "audioplayer.h"
#include "audiopluginholder.h"

#include "juce-stubs/juce_config.h"
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_basics/juce_audio_basics.h>


class AudioPlayer::AudioPlayer_Pimpl : public juce::AudioIODeviceCallback
{
public:
    AudioPlayer_Pimpl()
    {
        deviceManager.initialise (0, 2, nullptr, true);
        testTone.setFrequency (440.0);
        testTone.setAmplitude (juce::Decibels::decibelsToGain (-6.0));

        deviceManager.addAudioCallback (this);
    }

    ~AudioPlayer_Pimpl()
    {
        deviceManager.closeAudioDevice();
    }

    void setPlugin (std::unique_ptr<AudioPluginHolder> pluginToUse)
    {
        if (auto* audioDevice = deviceManager.getCurrentAudioDevice())
        {
            pluginToUse->prepareToPlay (audioDevice->getCurrentSampleRate(), audioDevice->getCurrentBufferSizeSamples());

            juce::ScopedLock lock (pluginsLock); // not realtime safe!
            plugin = std::move (pluginToUse);
        }
    }

    void showEditor()
    {
        if (plugin)
            plugin->showEditor();
    }

    void audioDeviceIOCallbackWithContext (const float *const *inputChannelData, int numInputChannels,
                                           float       *const *outputChannelData, int numOutputChannels,
                                           int numSamples, const juce::AudioIODeviceCallbackContext &context) override
    {
        juce::ignoreUnused (inputChannelData, numInputChannels, context);

        juce::AudioBuffer<float> buffer { outputChannelData, numOutputChannels, 0, numSamples };
        juce::MidiBuffer         midi;

        juce::AudioSourceChannelInfo info (buffer);
        testTone.getNextAudioBlock (info);

        if (plugin)
            plugin->processBlock (buffer, midi);
    }

    void audioDeviceAboutToStart (juce::AudioIODevice *device) override { juce::ignoreUnused (device); }
    void audioDeviceStopped() override {}

private:
    juce::ScopedJuceInitialiser_GUI juceGui;     // bring up juce's event system
    juce::CriticalSection           pluginsLock; // not realtime safe! test only

    std::unique_ptr<AudioPluginHolder> plugin;

    juce::ToneGeneratorAudioSource  testTone;
    juce::AudioDeviceManager        deviceManager;

};

// ================================================================================

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent},
      pimpl {std::make_unique<AudioPlayer::AudioPlayer_Pimpl>()}
{

}

AudioPlayer::~AudioPlayer(){}

void AudioPlayer::setPlugin (std::unique_ptr<AudioPluginHolder> plugin)
{
    pimpl->setPlugin (std::move (plugin));
}

void AudioPlayer::showEditor()
{
    pimpl->showEditor();
}

