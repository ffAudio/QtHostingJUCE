#ifndef AUDIOPLUGINHOLDER_H
#define AUDIOPLUGINHOLDER_H

#include <QObject>
#include <QWidget>


namespace juce
{
class AudioProcessor;
class AudioProcessorEditor;
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

public slots:
    void showEditor();

private:

    class AudioPluginHolder_Pimpl;
    std::unique_ptr<AudioPluginHolder_Pimpl> pimpl;
};




#endif // AUDIOPLUGINHOLDER_H
