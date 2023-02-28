#ifndef AUDIOPLUGINHOLDER_H
#define AUDIOPLUGINHOLDER_H

#include <QObject>
#include <QWidget>


namespace juce
{
class AudioProcessor;
class AudioProcessorEditor;
template<typename FloatType>class AudioBuffer;
class MidiBuffer;
}

class AudioPluginWindow : public QWidget
{
public:
    AudioPluginWindow();
    ~AudioPluginWindow();

    void setAudioProcessorEditor (juce::AudioProcessorEditor* editor);

private:
    std::unique_ptr<juce::AudioProcessorEditor> editor;
};


class AudioPluginHolder : public QObject
{
    Q_OBJECT
public:
    AudioPluginHolder (QObject *parent = nullptr);
    ~AudioPluginHolder() override;

    void setAudioProcessor (std::unique_ptr<juce::AudioProcessor> processor);

    void prepareToPlay (double sampleRate, int blockSize);
    void releaseResources();

    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi);

public slots:
    void showEditor();

private:

    class AudioPluginHolder_Pimpl;
    std::unique_ptr<AudioPluginHolder_Pimpl> pimpl;
};




#endif // AUDIOPLUGINHOLDER_H
