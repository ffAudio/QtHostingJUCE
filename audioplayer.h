#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer() override;

signals:

private:
    class AudioPlayer_Pimpl;
    std::unique_ptr<AudioPlayer_Pimpl> pimpl;

};

#endif // AUDIOPLAYER_H
