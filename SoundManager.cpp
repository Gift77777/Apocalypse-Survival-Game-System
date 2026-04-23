#include "SoundManager.h"
#include "SoundManager.h"
#include <iostream>

using namespace std;

SoundManager::SoundManager() : soundEnabled(true), volume(50.f), heartbeatPlaying(false) {
    // Implementation as in your original code
    if (!clickBuffer.loadFromFile("./resources/click.wav")) {
        cerr << "Could not load click sound!" << endl;
    }
    if (!correctBuffer.loadFromFile("./resources/correct.wav")) {
        cerr << "Could not load correct sound!" << endl;
    }
    if (!wrongBuffer.loadFromFile("./resources/wrong.wav")) {
        cerr << "Could not load wrong sound!" << endl;
    }
    if (!winBuffer.loadFromFile("./resources/win.wav")) {
        cerr << "Could not load win sound!" << endl;
    }
    if (!loseBuffer.loadFromFile("./resources/lose.wav")) {
        cerr << "Could not load lose sound!" << endl;
    }
    // LOADING sound
    if (!loadingMusic.openFromFile("./resources/loading_music.wav")) {
        cerr << "Error: Could not load loading_music\n";
    }
    loadingMusic.setLoop(true);

    if (!heartbeatBuffer.loadFromFile("./resources/heartbeat.wav")) {
        cerr << "Could not load heartbeat sound!" << endl;
    }

    heartbeatSound.setBuffer(heartbeatBuffer);
    heartbeatSound.setLoop(true);


    clickSound.setBuffer(clickBuffer);
    correctSound.setBuffer(correctBuffer);
    wrongSound.setBuffer(wrongBuffer);
    winSound.setBuffer(winBuffer);
    loseSound.setBuffer(loseBuffer);

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(volume);
    backgroundMusic.play();
}

// Implement all SoundManager methods as in your original code


void SoundManager::playClick() { if (soundEnabled) clickSound.play(); }
void SoundManager::playCorrect() { if (soundEnabled) correctSound.play(); }
void SoundManager::playWrong() { if (soundEnabled) wrongSound.play(); }
void SoundManager::playWin() { if (soundEnabled) winSound.play(); }
void SoundManager::playLose() { if (soundEnabled) loseSound.play(); }

void SoundManager::playHeartbeat() {
    if (soundEnabled && !heartbeatPlaying) {
        heartbeatSound.play();
        heartbeatPlaying = true;
    }
}

void SoundManager::playLoadingMusic() {
    if (soundEnabled) {
        loadingMusic.play();
    }
}

void SoundManager::stopLoadingMusic() {
    loadingMusic.stop();
}


void SoundManager::toggleSound(bool shouldPlayMusic) {
    soundEnabled = !soundEnabled;
    if (soundEnabled) {
        backgroundMusic.play();
    }
    else {
        backgroundMusic.pause();
    }
}
void SoundManager::startGameMusic() {
}

void SoundManager::stopHeartbeat() {
    heartbeatSound.stop();
    heartbeatPlaying = false;
}

void SoundManager::setVolume(float vol) {
    volume = vol;
    backgroundMusic.setVolume(volume);
}

bool SoundManager::isSoundEnabled() const { return soundEnabled; }
float SoundManager::getVolume() const { return volume; }
