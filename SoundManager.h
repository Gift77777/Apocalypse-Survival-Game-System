#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer correctBuffer;
    sf::SoundBuffer wrongBuffer;
    sf::SoundBuffer winBuffer;
    sf::SoundBuffer loseBuffer;
    sf::SoundBuffer loadingBuffer;
    sf::SoundBuffer heartbeatBuffer;
    sf::SoundBuffer backgroundMusicBuffer;

    sf::Sound clickSound;
    sf::Sound correctSound;
    sf::Sound wrongSound;
    sf::Sound winSound;
    sf::Sound loseSound;
    sf::Sound loadingSound;
    sf::Sound backgroundMusic;
    sf::Sound heartbeatSound;

    bool soundEnabled;
    float volume;
    bool heartbeatPlaying;
    sf::Music loadingMusic;

public:
    SoundManager();
    void playClick();
    void playCorrect();
    void playWrong();
    void playWin();
    void playLose();
    void playHeartbeat();
    void playLoadingMusic();
    void stopLoadingMusic();
    void toggleSound(bool shouldPlayMusic);
    void startGameMusic();
    void stopHeartbeat();
    void setVolume(float vol);
    bool isSoundEnabled() const;
    float getVolume() const;
};

#endif // SOUNDMANAGER_H