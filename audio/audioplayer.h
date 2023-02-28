#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class AudioPluginHolder;

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer() override;

    void setPlugin (std::unique_ptr<AudioPluginHolder> plugin);

public slots:
    void showEditor();

signals:

private:
    class AudioPlayer_Pimpl;
    std::unique_ptr<AudioPlayer_Pimpl> pimpl;

};

#endif // AUDIOPLAYER_H
