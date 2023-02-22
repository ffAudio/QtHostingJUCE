

#include "audioplayer.h"
#include "audiopluginholder.h"

#include "juce-stubs/juce_config.h"
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>


class AudioPlayer::AudioPlayer_Pimpl
{
public:
    AudioPlayer_Pimpl()
    {
        deviceManager.initialise (0, 2, nullptr, true);
        testTone.setFrequency (440.0);
        testTone.setAmplitude (juce::Decibels::decibelsToGain (-6.0));
        sourcePlayer.setSource (&testTone);

        deviceManager.addAudioCallback (&sourcePlayer);
    }

    ~AudioPlayer_Pimpl()
    {
        deviceManager.closeAudioDevice();
    }

private:
    juce::ScopedJuceInitialiser_GUI juceGui; // bring up juce's event system

    std::vector<std::unique_ptr<AudioPluginHolder>> plugins;

    juce::ToneGeneratorAudioSource  testTone;
    juce::AudioSourcePlayer         sourcePlayer;
    juce::AudioDeviceManager        deviceManager;

};

// ================================================================================

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent},
      pimpl {std::make_unique<AudioPlayer::AudioPlayer_Pimpl>()}
{

}

AudioPlayer::~AudioPlayer(){}


