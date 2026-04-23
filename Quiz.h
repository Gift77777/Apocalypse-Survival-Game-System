#pragma once
#ifndef QUIZ_H
#define QUIZ_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <set>
#include "Player.h"
#include "Question.h"
#include "SoundManager.h"
#include "RectangleButton.h"

using namespace sf;
using namespace std;

class Quiz {
private:
    enum GameState {
        LOADING,
        MAIN_MENU,
        PLAYER_NAME_INPUT,
        TUTORIAL,
        SETTINGS,
        IN_GAME,
        PHASE_COMPLETE,
        GAME_COMPLETE,
        LEADERBOARD
    };

    bool questionSpriteLoaded = false;

    //BACKGROUND PICTURE FOR EACH PHASE
    Texture questionTextures[3][8]; // 3 phases, 8 questions each
    Sprite questionSprites[3][8];
    bool questionTexturesLoaded = false;

    // for shaking 
    bool isShaking = false;
    float shakeIntensity = 0.0f;
    Vector2f originalViewCenter;
    Clock shakeClock;
    float minShakeDuration = 8.0f; // Minimum shake duration in seconds
    Clock shakeDurationClock; // Clock to track how long we've been shaking

    // blood splatter
    Texture bloodTexture;
    Sprite bloodSprite;
    bool showBloodSplatter = false;
    float bloodAlpha = 170.0f; // Semi-transparent (0-255)

    //for jumpscare
    Texture jumpScareTexture;
    Sprite jumpScareSprite;
    SoundBuffer jumpScareSoundBuffer;
    Sound jumpScareSound;
    bool showJumpScare = false;
    Clock jumpScareClock;
    const float JUMP_SCARE_DURATION = 1.5f; // Duration in seconds

    //Setting up the leaderboard
    //std::set<Player> leaderboardPlayers;

    Texture menuBackgroundTexture;
    //Sprite menuBackgroundSprite;

    RenderWindow& mainWindow;
    Font font;
    SoundManager soundManager;  // create soundManager
    GameState currentState;

    // Main menu elements
    Text titleText;
    RectangleButton playButton;
    RectangleButton settingsButton;
    RectangleButton exitButton;

    // Player name input elements
    Text namePromptText;
    Text nameInputText;
    string playerNameInput;
    RectangleButton nameSubmitButton;

    // Tutorial elements
    Text tutorialText;
    RectangleButton tutorialContinueButton;

    //**
    RectangleShape progressBarBackground;
    RectangleShape progressBarFill;
    Text progressBarStatus;

    // Settings elements
    Text settingsTitle;
    RectangleButton soundToggleButton;
    Text soundStatusText;
    // RectangleButton difficultyButton;
    Text difficultyText;
    RectangleButton settingsBackButton;

    // Game elements
    Sprite nextButtonSprite;
    Texture nextButtonTexture;
    RectangleButton continueButton;
    Text levelText;
    Text phaseText;
    Text questionTextDisplay;
    Text encounterTextDisplay;
    Text scoreText;
    Text phaseCompleteText;
    Text timerText;
    vector<RectangleShape> optionBoxes;
    vector<Text> optionTexts;
    int totalScore = 0;
    Text totalScoreText;

    RectangleShape questionTextBox;

    //leaderboard
    RectangleButton leaderboardButton;

    //***
    float encounterScrollOffset = 0.0f; // Current scroll offset (vertical)
    const float encounterScrollSpeed = 20.0f; // Scroll speed for mouse wheel or keyboard
    const float encounterViewportHeight = 400.0f; // Height of the viewport for encounter text


    int selectedAnswer = -1;
    bool answered = false;
    bool questionLoadingComplete = false;
    bool encounterLoadingComplete = false;
    int currentPhase = 1;
    bool showPhaseCompleteScreen = false;
    bool showGameCompleteScreen = false;

    Clock typingClock;
    float typingSpeed = 0.03f; // typing speed edit
    size_t charIndex = 0;

    // Timer variables
    Clock questionTimer;
    float timeRemaining = 0;
    float maxTime = 15.0f;
    float trueFalseTime = 8.0f;

    Player player;
    vector<Question::QuestionData> currentQuestions;
    vector<string> currentEncounters;
    int currentQuestionIndex = 0;
    string fullQuestionText;
    string displayedQuestionText;
    int currentEncounterIndex = 0;
    string currentEncounterText;
    string displayedEncounterText;

    Texture phase1BackgroundTexture;
    Texture phase2BackgroundTexture;
    Texture phase3BackgroundTexture;
    Texture phase4BackgroundTexture;
    Sprite currentBackgroundSprite;

    int phase1Score = 0;
    int phase2Score = 0;
    int phase3Score = 0;

    //**
     // Loading screen elements
    RectangleShape loadingBarBackground;
    RectangleShape loadingBar;
    Clock loadingClock;
    bool loadingComplete = false;
    Text loadingText;
    Texture loadingBackgroundTexture;
    Sprite loadingBackgroundSprite;

    // Leaderboard elements //added
    set<Player> leaderboardPlayers;
    RectangleButton leaderboardContinueButton;

    vector<string> phase1Intro = {
    "Intelligence reports confirm alien scouts have been spotted on Earth. The government has initiated ",
    "emergency training protocols. Your knowledge of proper medical procedures and protective ",
    "measures will determine your readiness for the coming invasion."
    };

    vector<string> phase2IntroPath1 = {
        "Thanks to your preparation, you have crucial resources and knowledge. The full-scale invasion has ",
        "begun, but you're ready to face the challenges ahead."
    };

    vector<string> phase2IntroPath2 = {
        "Your lack of preparation has left you vulnerable. The alien invasion overwhelms your defenses, and ",
        "you're fighting for survival with limited resources."
    };

    vector<string> phase3IntroPath1 = {
        "Your preparation and successful resistance have positioned you well. As humans mutate into ",
        "zombies, you lead a formidable defense against this new threat."
    };

    vector<string> phase3IntroPath2 = {
        "Despite good preparation, the alien-zombie threat has forced you to adapt. You lead a mobile ",
        "community that survives through constant tactical adaptation."
    };

    vector<string> phase3IntroPath3 = {
        "Despite early struggles, you've rallied your resources for a final stand. Against overwhelming odds, ",
        "you fight to carve out a defensible position against the alien-zombie onslaught."
    };

    vector<string> phase3IntroPath4 = {
        "Your position is critical. Resources are depleted, morale is low, and the alien-zombie horde ",
        "surrounds you. This is truly humanity's darkest hour."
    };

    bool showingPhaseIntro = false;
    vector<string> currentPhaseIntro;
    size_t currentIntroLine = 0;
    bool introLineComplete = false;
    Clock introTypingClock;
    size_t introCharIndex = 0;
    float introTypingSpeed = 0.05f;


    // Private methods
    void setupLoadingScreen();
    void scaleBackground(sf::Sprite& sprite);
    void setupMainMenu();
    void setupPlayerNameInput();
    void setupTutorial();
    void setupSettings();
    void setupLeaderboard();
    void scaleBackground();
    void showPhaseIntro(const std::vector<std::string>& introText);
    void loadPhase(const std::vector<Question::QuestionData>& questions, const std::vector<std::string>& encounters);
    void resetQuestionState();
    void setupCurrentQuestion();
    void setupOptionsGraphics();
    void resetOptionColors();
    void highlightSelectedAnswer();
    void processAnswer();
    void loadNextQuestion();

    // Input handlers
    void handleMainMenuInput(const sf::Event& event);
    void handlePlayerNameInput(const sf::Event& event);
    void handleTutorialInput(const sf::Event& event);
    void handleSettingsInput(const sf::Event& event);
    void handleGameInput(const sf::Event& event);
    void handleGameCompleteInput(const sf::Event& event);
    void handleLeaderboardInput(const sf::Event& event);
    void handleInput(const sf::Event& event);

    // Update methods
    //template <typename T>
    //T clamp(T value, T minVal, T maxVal);
    //void clampEncounterScroll();
    void update();

    // Render methods
    void renderLoadingScreen();
    void renderMainMenu();
    void renderPlayerNameInput();
    void renderTutorial();
    void renderSettings();
    void setupProgressBar();
    void updateProgressBar();
    void renderGame();
    String wrapText(const sf::String& text, sf::Font& font, unsigned int characterSize, float maxWidth);
    String wrapIntroText(const sf::String& text, sf::Font& font, unsigned int characterSize, float maxWidth);
    String getCurrentIntroText();
    string getEndingMessage(int path);
    void renderGameComplete();
    void renderLeaderboard();
    void render();

public:
    Quiz(sf::RenderWindow& window);
    void run();
};

#endif // QUIZ_H