#include "Quiz.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
void Quiz::setupLoadingScreen() {
    // Set background to black (we'll handle this in render)

    loadingBarBackground.setSize(Vector2f(700, 30));
    loadingBarBackground.setFillColor(Color(50, 50, 50));
    loadingBarBackground.setPosition((mainWindow.getSize().x - 700) / 2, mainWindow.getSize().y - 100); // Centered at bottom

    loadingBar.setSize(Vector2f(0, 30));
    loadingBar.setFillColor(Color::Green);
    loadingBar.setPosition(loadingBarBackground.getPosition());

    loadingText.setFont(font);
    loadingText.setString("APOCALYPSE SURVIVAL");
    loadingText.setCharacterSize(60);
    loadingText.setFillColor(Color::Red);
    loadingText.setStyle(Text::Bold);

    // Center the text horizontally
    FloatRect textBounds = loadingText.getLocalBounds();
    loadingText.setOrigin(textBounds.width / 2, 0);

    // Position game name below logo
    loadingText.setPosition(mainWindow.getSize().x / 2, mainWindow.getSize().y / 2 + 150);
    soundManager.playLoadingMusic();
}

void Quiz::scaleBackground(Sprite& sprite) {
    sprite.setScale(
        float(mainWindow.getSize().x) / sprite.getTexture()->getSize().x,
        float(mainWindow.getSize().y) / sprite.getTexture()->getSize().y
    );
}

Clock delayTimer;
bool isInDelay = false;
const float QUESTION_DELAY = 2.0f; // 5 second delay between encounter and quest

void Quiz::setupMainMenu() {
    //**
   /* if (!menuBackgroundTexture.loadFromFile("./resources/menu_background.png")) {
        cerr << "Error: Could not load menu_background.png!\n";
        // Create a simple background if file not found
        menuBackgroundTexture.create(mainWindow.getSize().x, mainWindow.getSize().y);
    }

    // Set up the background sprite
   // menuBackgroundSprite.setTexture(menuBackgroundTexture);
    menuBackgroundSprite.setScale(
        float(mainWindow.getSize().x) / menuBackgroundTexture.getSize().x,
        float(mainWindow.getSize().y) / menuBackgroundTexture.getSize().y
    );*/

    // Load logo texture for main menu
    Texture logoTexture;
    if (!logoTexture.loadFromFile("./resources/logo.png")) {
        cerr << "Error: Could not load logo.png!\n";
    }
    Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    FloatRect logoBounds = logoSprite.getLocalBounds();
    logoSprite.setOrigin(logoBounds.width / 2, 0);
    logoSprite.setPosition(mainWindow.getSize().x / 2, 50);

    titleText.setFont(font);
    titleText.setString("APOCALYPSE SURVIVAL");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::Red);
    titleText.setPosition(200, 100);

    playButton.button.setSize(Vector2f(300, 60));
    playButton.button.setPosition(300, 250);
    playButton.button.setFillColor(Color(150, 0, 0, 200));
    playButton.label.setFont(font);
    playButton.label.setString("BEGIN");
    playButton.label.setCharacterSize(30);
    playButton.label.setFillColor(Color::White);
    playButton.label.setPosition(370, 260);

    leaderboardButton.button.setSize(Vector2f(300, 60));
    leaderboardButton.button.setPosition(300, 350);
    leaderboardButton.button.setFillColor(Color(150, 0, 0, 200));
    leaderboardButton.label.setFont(font);
    leaderboardButton.label.setString("LEADERBOARD");
    leaderboardButton.label.setCharacterSize(30);
    leaderboardButton.label.setFillColor(Color::White);
    leaderboardButton.label.setPosition(370, 360);

    settingsButton.button.setSize(Vector2f(300, 60));
    settingsButton.button.setPosition(300, 450);
    settingsButton.button.setFillColor(Color(150, 0, 0, 200));
    settingsButton.label.setFont(font);
    settingsButton.label.setString("SETTINGS");
    settingsButton.label.setCharacterSize(30);
    settingsButton.label.setFillColor(Color::White);
    settingsButton.label.setPosition(370, 460);

    exitButton.button.setSize(Vector2f(300, 60));
    exitButton.button.setPosition(300, 550);
    exitButton.button.setFillColor(Color(150, 0, 0, 200));
    exitButton.label.setFont(font);
    exitButton.label.setString("EXIT");
    exitButton.label.setCharacterSize(30);
    exitButton.label.setFillColor(Color::White);
    exitButton.label.setPosition(400, 560);
}

void Quiz::setupPlayerNameInput() {
    namePromptText.setFont(font);
    namePromptText.setString("Enter your name:");
    namePromptText.setCharacterSize(40);
    namePromptText.setFillColor(Color::White);
    namePromptText.setPosition(300, 200);

    nameInputText.setFont(font);
    nameInputText.setString("");
    nameInputText.setCharacterSize(40);
    nameInputText.setFillColor(Color::White);
    nameInputText.setPosition(300, 300);

    nameSubmitButton.button.setSize(Vector2f(200, 50));
    nameSubmitButton.button.setPosition(350, 400);
    nameSubmitButton.button.setFillColor(Color(0, 150, 0, 200));
    nameSubmitButton.label.setFont(font);
    nameSubmitButton.label.setString("CONTINUE");
    nameSubmitButton.label.setCharacterSize(30);
    nameSubmitButton.label.setFillColor(Color::White);
    nameSubmitButton.label.setPosition(370, 410);
}

void Quiz::setupTutorial() {
    tutorialText.setFont(font);
    tutorialText.setString(
        "SURVIVAL GUIDE:\n\n"
        "1. Answer correctly to survive each phase\n"
        "2. Your choices affect the story outcome\n"
        "3. The Game gets harder going from phase 1 to 3\n"
        "4. Phase 2 adds shaking from wrong answers\n"
        "4. Phase 3 adds bloodsplatter when remaining time is low\n"
        "5. True/False questions have shorter timers\n"
        "6. Your performance determines your path\n\n"
        "Survive all 3 phases to reach an ending\n"
        "Score 500+ in each phase for the best ending!\n\n"
        "Good luck survivor!"
    );
    tutorialText.setCharacterSize(24);
    tutorialText.setFillColor(Color::White);
    tutorialText.setPosition(100, 150);

    tutorialContinueButton.button.setSize(Vector2f(200, 50));
    tutorialContinueButton.button.setPosition(480, 580);
    tutorialContinueButton.button.setFillColor(Color(0, 150, 0, 200));
    tutorialContinueButton.label.setFont(font);
    tutorialContinueButton.label.setString("I'M READY");
    tutorialContinueButton.label.setCharacterSize(30);
    tutorialContinueButton.label.setFillColor(Color::White);
    tutorialContinueButton.label.setPosition(490, 590);
}

void Quiz::setupSettings() {
    settingsTitle.setFont(font);
    settingsTitle.setString("SETTINGS");
    settingsTitle.setCharacterSize(50);
    settingsTitle.setFillColor(Color::Red);
    settingsTitle.setPosition(350, 100);

    soundToggleButton.button.setSize(Vector2f(300, 60));
    soundToggleButton.button.setPosition(300, 200);
    soundToggleButton.button.setFillColor(Color(150, 0, 0, 200));
    soundToggleButton.label.setFont(font);
    soundToggleButton.label.setString("SOUND: ");
    soundToggleButton.label.setCharacterSize(30);
    soundToggleButton.label.setFillColor(Color::White);
    soundToggleButton.label.setPosition(310, 210);

    soundStatusText.setFont(font);
    soundStatusText.setCharacterSize(30);
    soundStatusText.setFillColor(Color::White);
    soundStatusText.setPosition(450, 210);
    soundStatusText.setString(soundManager.isSoundEnabled() ? "ON" : "OFF");

    /*difficultyButton.button.setSize(Vector2f(300, 60));
    difficultyButton.button.setPosition(300, 300);
    difficultyButton.button.setFillColor(Color(150, 0, 0, 200));
    difficultyButton.label.setFont(font);
    difficultyButton.label.setString("DIFFICULTY: ");
    difficultyButton.label.setCharacterSize(30);
    difficultyButton.label.setFillColor(Color::White);
    difficultyButton.label.setPosition(310, 310);

    difficultyText.setFont(font);
    difficultyText.setCharacterSize(30);
    difficultyText.setFillColor(Color::White);
    difficultyText.setPosition(500, 310);
    switch (player.difficulty) {
    case 1: difficultyText.setString("EASY"); break;
    case 2: difficultyText.setString("MEDIUM"); break;
    case 3: difficultyText.setString("HARD"); break;
    }
*/

    settingsBackButton.button.setSize(Vector2f(200, 50));
    settingsBackButton.button.setPosition(350, 400);
    settingsBackButton.button.setFillColor(Color(0, 150, 0, 200));
    settingsBackButton.label.setFont(font);
    settingsBackButton.label.setString("BACK");
    settingsBackButton.label.setCharacterSize(30);
    settingsBackButton.label.setFillColor(Color::White);
    settingsBackButton.label.setPosition(400, 410);
}

void Quiz::setupLeaderboard() {
    // Load existing leaderboard
    leaderboardPlayers = Player::loadLeaderboard();

    // Add current player's score
    Player currentPlayer = player;
    currentPlayer.score = totalScore;
    leaderboardPlayers.insert(currentPlayer); // duplicates are ignored if same name+score

    // Keep only top 10 players
    if (leaderboardPlayers.size() > 10) {
        auto it = leaderboardPlayers.begin();
        std::advance(it, 10); // move to the 11th player
        leaderboardPlayers.erase(it, leaderboardPlayers.end());
    }

    // Save the updated leaderboard
    Player::saveLeaderboard(leaderboardPlayers);

    // Setup continue button
    leaderboardContinueButton.button.setSize(Vector2f(200, 50));
    leaderboardContinueButton.button.setPosition(350, 700);
    leaderboardContinueButton.button.setFillColor(Color(0, 150, 0, 200));
    leaderboardContinueButton.label.setFont(font);
    leaderboardContinueButton.label.setString("MAIN MENU");
    leaderboardContinueButton.label.setCharacterSize(30);
    leaderboardContinueButton.label.setFillColor(Color::White);
    leaderboardContinueButton.label.setPosition(370, 710);
}


void Quiz::scaleBackground() {
    currentBackgroundSprite.setScale(
        float(mainWindow.getSize().x) / currentBackgroundSprite.getTexture()->getSize().x,
        float(mainWindow.getSize().y) / currentBackgroundSprite.getTexture()->getSize().y
    );
}


void Quiz::showPhaseIntro(const vector<string>& introText) {
    showingPhaseIntro = true;
    currentPhaseIntro = introText;
    currentIntroLine = 0;
    introCharIndex = 0;
    introLineComplete = false;
    introTypingClock.restart();

    // Combine all lines with spaces for proper wrapping
    string combinedText;
    for (const auto& line : introText) {
        combinedText += line + " ";
    }
    currentPhaseIntro = { combinedText }; // Store as single line for typing
}

void Quiz::loadPhase(const vector<Question::QuestionData>& questions, const vector<string>& encounters) {

    currentQuestions = questions;
    currentEncounters = encounters;
    currentQuestionIndex = 0;
    resetQuestionState();




    if (currentPhase == 1) {
        currentBackgroundSprite.setTexture(phase1BackgroundTexture);
        //player.survivalPath = 1;
        scaleBackground();
        showPhaseIntro(phase1Intro);
    }

    else if (currentPhase == 2) {
        if (phase1Score >= 5) {
            currentBackgroundSprite.setTexture(phase2BackgroundTexture);
            showPhaseIntro(phase2IntroPath1);
        }
        else {
            currentBackgroundSprite.setTexture(phase3BackgroundTexture);
            showPhaseIntro(phase2IntroPath2);
        }
    }
    else if (currentPhase == 3) {
        // Determine which ending path based on cumulative performance
        //int totalScore = phase1Score + phase2Score;
        if (phase1Score >= 500 && phase2Score >= 500) { // Did well in both phases
            currentBackgroundSprite.setTexture(phase1BackgroundTexture); // Best ending
            showPhaseIntro(phase3IntroPath1);
            player.survivalPath = 1;

        }
        else if (phase1Score >= 500 && phase2Score < 500) { // Did okay
            currentBackgroundSprite.setTexture(phase2BackgroundTexture); // Good ending
            showPhaseIntro(phase3IntroPath2);
            player.survivalPath = 2;
        }
        else if (phase1Score < 500 && phase2Score >= 500) { // Struggled
            currentBackgroundSprite.setTexture(phase3BackgroundTexture); // Bad ending
            showPhaseIntro(phase3IntroPath3);
            player.survivalPath = 3;
        }
        else if (phase1Score < 500 && phase2Score < 500) { // Failed badly
            currentBackgroundSprite.setTexture(phase4BackgroundTexture); // Worst ending
            showPhaseIntro(phase3IntroPath4);
            player.survivalPath = 4;
        }
    }
    scaleBackground();

    if (!currentQuestions.empty() && !currentEncounters.empty()) {
        setupCurrentQuestion();
    }
}

void Quiz::resetQuestionState() {
    selectedAnswer = -1;
    answered = false;
    questionLoadingComplete = false;
    encounterLoadingComplete = currentEncounters.empty();
    showPhaseCompleteScreen = false;
}

void Quiz::setupCurrentQuestion() {
    if (!currentEncounters.empty()) {
        currentEncounterText = currentEncounters[currentQuestionIndex];
        displayedEncounterText = wrapText(currentEncounterText, font, encounterTextDisplay.getCharacterSize(), 700);
    }

    fullQuestionText = currentQuestions[currentQuestionIndex].questionText;
    displayedQuestionText = wrapText(fullQuestionText, font, questionTextDisplay.getCharacterSize(), 700);
    charIndex = 0;
    typingClock.restart();

    // Load the question sprite immediately
    questionSpriteLoaded = true; // We've already loaded all sprites in constructor

    // Set timer based on question type
    if (currentQuestions[currentQuestionIndex].isTrueFalse) {
        if (currentPhase == 1) {
            timeRemaining = 10.0f;
        }
        else if (currentPhase == 2) {
            timeRemaining = 8.0f;
        }
        else if (currentPhase == 3) {
            timeRemaining = 6.0f;
        }
    }
    else {
        if (currentPhase == 1) {
            timeRemaining = 15.0f;
        }
        else if (currentPhase == 2) {
            timeRemaining = 12.0f;
        }
        else if (currentPhase == 3) {
            timeRemaining = 9.0f;
        }
    }

    // Apply difficulty modifier
    float difficultyModifier = 1.2f - (player.difficulty * 0.1f);
    timeRemaining *= difficultyModifier;

    setupOptionsGraphics();
}

void Quiz::setupOptionsGraphics() {
    optionBoxes.clear();
    optionTexts.clear();
    const auto& options = currentQuestions[currentQuestionIndex].options;
    float startX = (mainWindow.getSize().x - 700.0f) / 2.0f;
    float startY = 350.0f;
    float spacing = 60.0f;
    float boxWidth = 700.0f;

    for (size_t i = 0; i < options.size(); ++i) {
        RectangleShape box(Vector2f(boxWidth, 50));
        box.setPosition(startX, startY + i * spacing);
        box.setFillColor(Color(30, 30, 30));
        box.setOutlineThickness(2);
        box.setOutlineColor(Color::Red);
        optionBoxes.push_back(box);

        Text text(options[i], font, 20);
        text.setFillColor(Color::White);

        FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        text.setPosition(box.getPosition().x + box.getSize().x / 2.f, box.getPosition().y + box.getSize().y / 2.f);
        optionTexts.push_back(text);
    }


    questionTimer.restart();
}

void Quiz::resetOptionColors() {
    for (auto& box : optionBoxes) {
        box.setFillColor(Color(30, 30, 30));
        box.setOutlineColor(Color::Red);
    }
}

void Quiz::highlightSelectedAnswer() {
    resetOptionColors();
    if (selectedAnswer != -1 && static_cast<size_t>(selectedAnswer) < optionBoxes.size()) {
        optionBoxes[selectedAnswer].setFillColor(Color(0, 150, 0, 200));
    }
}

/* void processAnswer() {
     if (answered && selectedAnswer != -1) {
         float timeTaken = questionTimer.getElapsedTime().asSeconds();
         float timeRatio = timeTaken / timeRemaining;

         // Calculate points based on speed and difficulty
         int basePoints = currentQuestions[currentQuestionIndex].difficultyLevel;
         int speedBonus = static_cast<int>((1.0f - timeRatio) * 3); // Up to 3 bonus points

         if (selectedAnswer == currentQuestions[currentQuestionIndex].correctAnswerIndex) {
             player.increaseScore(basePoints + speedBonus);
             soundManager.playCorrect();
         }
         else {
             soundManager.playWrong();
         }
         answered = false;
         selectedAnswer = -1;
     }
 }*/
void Quiz::processAnswer() {
    if (answered && selectedAnswer != -1) {
        if (selectedAnswer == currentQuestions[currentQuestionIndex].correctAnswerIndex) {
            // Correct answer - stop shaking
            isShaking = false;
            player.increaseScore(125);
            totalScore += 125;
            soundManager.playCorrect();
        }
        else {
            // Only shake in Phase 2 and Phase 3
            if (currentPhase == 2 || currentPhase == 3) {
                isShaking = true;
                shakeDurationClock.restart(); // Start tracking shake duration

                // Set different intensity based on phase
                if (currentPhase == 2) {
                    shakeIntensity = 7.0f; // Stronger shake for Phase 2
                }
                else if (currentPhase == 3) {
                    shakeIntensity = 10.0f; // Strongest shake for Phase 3
                }
            }
            shakeClock.restart();
            soundManager.playWrong();
        }

        highlightSelectedAnswer();
    }
}

void Quiz::loadNextQuestion() {
    currentQuestionIndex++;
    selectedAnswer = -1;
    answered = false;
    questionLoadingComplete = false;
    encounterLoadingComplete = currentEncounters.empty(); // Immediately complete if no encounters
    resetOptionColors();

    if (currentQuestionIndex < currentQuestions.size()) {
        // sleep(seconds(6));
        setupCurrentQuestion();
        // Force immediate display if no encounter text
        if (currentEncounters.empty()) {
            encounterLoadingComplete = true;
        }
    }
    else {
        showPhaseCompleteScreen = true;
        // Save phase score
        if (currentPhase == 1) {
            phase1Score = player.getScore();
        }
        else if (currentPhase == 2) {
            phase2Score = player.getScore();
        }
        else if (currentPhase == 3) {
            phase3Score = player.getScore();
            currentState = GAME_COMPLETE;
            // Play appropriate ending sound
            if (player.survivalPath == 1) {
                soundManager.playWin();
            }
            else if (player.survivalPath == 4) {
                soundManager.playLose();
            }
        }
        player.resetScore();
    }
}
void Quiz::handleMainMenuInput(const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (playButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            currentState = PLAYER_NAME_INPUT;
        }
        else if (settingsButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            currentState = SETTINGS;
        }
        else if (leaderboardButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            setupLeaderboard(); // Load the leaderboard data
            currentState = LEADERBOARD;
        }
        else if (exitButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            mainWindow.close();
        }
    }
}

void Quiz::handlePlayerNameInput(const Event& event) {
    if (event.type == Event::TextEntered) {
        if (event.text.unicode == '\b' && !playerNameInput.empty()) {
            playerNameInput.pop_back();
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n') {
            playerNameInput += static_cast<char>(event.text.unicode);
        }
        nameInputText.setString(playerNameInput);
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (nameSubmitButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            if (!playerNameInput.empty()) {
                player.name = playerNameInput;
                currentState = TUTORIAL;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        // A key was pressed! Let's check which one.
        if (event.key.code == sf::Keyboard::Enter) {
            soundManager.playClick();
            if (!playerNameInput.empty()) {
                player.name = playerNameInput;
                currentState = TUTORIAL;
            }
        }
    }
}

void Quiz::handleTutorialInput(const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (tutorialContinueButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            currentState = IN_GAME;
            Question::Phase_1 phase1;
            vector<string> encounters;
            for (const auto& story : phase1.path1_Encounters) {
                encounters.push_back(story.storyText);
            }
            loadPhase(phase1.path_1, encounters);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        // A key was pressed! Let's check which one.
        if (event.key.code == sf::Keyboard::Enter) {
            soundManager.playClick();
            currentState = IN_GAME;
            Question::Phase_1 phase1;
            vector<string> encounters;
            for (const auto& story : phase1.path1_Encounters) {
                encounters.push_back(story.storyText);
            }
            loadPhase(phase1.path_1, encounters);
        }
    }
}

void Quiz::handleSettingsInput(const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (soundToggleButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            soundManager.toggleSound(soundManager.isSoundEnabled());
            soundStatusText.setString(soundManager.isSoundEnabled() ? "ON" : "OFF");
        }
        /*else if (difficultyButton.button.getGlobalBounds().contains(mousePos)) {
             soundManager.playClick();
             player.difficulty = player.difficulty % 3 + 1;
             switch (player.difficulty) {
             case 1: difficultyText.setString("EASY"); break;
             case 2: difficultyText.setString("MEDIUM"); break;
             case 3: difficultyText.setString("HARD"); break;
             }
         }*/
        else if (settingsBackButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            currentState = MAIN_MENU;
        }
    }
}

void Quiz::handleGameInput(const Event& event) {
    //****

    //****
    if (showingPhaseIntro) {
        if (event.type == Event::MouseButtonPressed ||
            event.type == Event::KeyPressed) {
            if (!introLineComplete) {
                // Skip to end of current typing
                introCharIndex = currentPhaseIntro[0].size();
                introLineComplete = true;
            }
            else {
                // Move to game
                showingPhaseIntro = false;
            }
            soundManager.playClick();
        }
        return;
    }
    else if (event.type == Event::MouseWheelScrolled) {
        // Handle scrolling with mouse wheel
        if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel) {
            encounterScrollOffset -= event.mouseWheelScroll.delta * encounterScrollSpeed;
            //clampEncounterScroll(); // Ensure scroll offset stays within bounds
        }
    }
    else if (event.type == Event::KeyPressed) {
        // Handle scrolling with keyboard
        if (event.key.code == Keyboard::Up) {
            encounterScrollOffset -= encounterScrollSpeed;
            //clampEncounterScroll();
        }
        else if (event.key.code == Keyboard::Down) {
            encounterScrollOffset += encounterScrollSpeed;
            //clampEncounterScroll();
        }
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left || event.type == sf::Event::KeyPressed) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (showPhaseCompleteScreen && continueButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            showPhaseCompleteScreen = false;
            if (currentPhase < 3) {
                currentPhase++;
                if (currentPhase == 2) {
                    Question::Phase_2 phase2;
                    if (phase1Score >= 5) {
                        vector<string> encounters;
                        for (const auto& story : phase2.path1_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase2.path_1, encounters);
                    }
                    else {
                        vector<string> encounters;
                        for (const auto& story : phase2.path2_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase2.path_2, encounters);
                    }
                }

                else if (currentPhase == 3) {
                    Question::Phase_3 phase3;
                    vector<string> encounters;

                    // Determine which ending path based on cumulative performance
                    //int totalScore = phase1Score + phase2Score;
                    // phase1Score >= 500 checks if the player did well in phase 1 (implying they in phase 2 path 1)
                    // phase2Score >= 500 checks if the player did well in phase 2 (implying they going to phase 3 path 1)
                    if (phase2Score >= 500 && phase1Score >= 500) { // Best ending
                        for (const auto& story : phase3.path1_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase3.path_1, encounters);
                    }
                    // phase1Score >= 500 checks if the player did well in phase 1 (implying they in phase 2 path 1)
                    // phase2Score < 500 checks if the player did not do well in phase 2 (implying they going to phase 3 path 2)
                    else if (phase2Score < 500 && phase1Score >= 500) { // Good ending
                        for (const auto& story : phase3.path2_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase3.path_2, encounters);
                    }
                    // phase1Score < 500 checks if the player did not do well in phase 1 (implying they in phase 2 path 2)
                    // phase2Score >= 500 checks if the player did well in phase 2 (implying they going to phase 3 path 3)
                    else if (phase2Score >= 500 && phase1Score < 500) { // Bad ending
                        for (const auto& story : phase3.path3_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase3.path_3, encounters);
                    }
                    // phase1Score < 500 checks if the player did not do well in phase 1 (implying they in phase 2 path 2)
                    // phase2Score < 500 checks if the player did not do well in phase 2 (implying they going to phase 3 path 4)
                    else if (phase2Score < 500 && phase1Score < 500) { // Worst ending
                        for (const auto& story : phase3.path4_Encounters) {
                            encounters.push_back(story.storyText);
                        }
                        loadPhase(phase3.path_4, encounters);
                    }
                }
            }
        }


        if (!showPhaseCompleteScreen && !showGameCompleteScreen) {
            if (encounterLoadingComplete && questionLoadingComplete) {
                for (size_t i = 0; i < optionBoxes.size(); ++i) {
                    if (optionBoxes[i].getGlobalBounds().contains(mousePos)) {
                        selectedAnswer = static_cast<int>(i);
                        answered = true;
                        highlightSelectedAnswer();
                        soundManager.playClick();
                        break;
                    }
                }

                if (nextButtonSprite.getGlobalBounds().contains(mousePos) || event.key.code == sf::Keyboard::Enter) {
                    //soundManager.playClick();
                    if (!answered) {
                        selectedAnswer = -1; // Mark as no answer selected
                        answered = true;
                    }
                    processAnswer();
                    loadNextQuestion();
                }


            }
            else if (!isInDelay) { // Only allow skipping if not in delay period
                if (!encounterLoadingComplete) {
                    soundManager.playClick();
                    encounterLoadingComplete = true;
                    charIndex = currentEncounterText.size();
                    isInDelay = true; // Start delay period
                    delayTimer.restart();
                }
                else if (!questionLoadingComplete) {
                    soundManager.playClick();
                    questionLoadingComplete = true;
                    charIndex = displayedQuestionText.size();
                    setupOptionsGraphics();
                }

            }
        }
    }
}
/*template <typename T>
T clamp(T value, T minVal, T maxVal) {
    return (value < minVal) ? minVal : (value > maxVal) ? maxVal : value;
}
void Quiz::clampEncounterScroll() {
    // Clamp the scroll offset to ensure it doesn't go out of bounds
    float maxScrollOffset = max(0.0f, encounterTextDisplay.getLocalBounds().height - encounterViewportHeight);
    encounterScrollOffset = clamp(encounterScrollOffset, 0.0f, maxScrollOffset);
}*/


void Quiz::handleGameCompleteInput(const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (continueButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            player.score = phase1Score + phase2Score + phase3Score;
            setupLeaderboard(); //added
            currentState = LEADERBOARD; // added
        }
    }
}

void Quiz::handleLeaderboardInput(const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (leaderboardContinueButton.button.getGlobalBounds().contains(mousePos)) {
            soundManager.playClick();
            currentState = MAIN_MENU;
            player.resetScore();
            currentPhase = 1;
            phase1Score = 0;
            phase2Score = 0;
            phase3Score = 0;
            player.survivalPath = 1;
            currentQuestionIndex = 0;
            selectedAnswer = -1;
            answered = false;
            showPhaseCompleteScreen = false;
            showGameCompleteScreen = false;
            showingPhaseIntro = false;
        }
    }
}

void Quiz::handleInput(const Event& event) {
    switch (currentState) {
    case MAIN_MENU: handleMainMenuInput(event); break;
    case PLAYER_NAME_INPUT: handlePlayerNameInput(event); break;
    case TUTORIAL: handleTutorialInput(event); break;
    case SETTINGS: handleSettingsInput(event); break;
    case IN_GAME: handleGameInput(event); break;
    case GAME_COMPLETE: handleGameCompleteInput(event); break;
    case LEADERBOARD: handleLeaderboardInput(event); break;

    default: break;
    }

    if (event.type == Event::Closed) {
        mainWindow.close();
    }
}


void Quiz::update() {
    // jump scare
    if (currentState == LOADING) {
        float progress = min(1.0f, loadingClock.getElapsedTime().asSeconds() / 15.0f);
        if (progress >= 1.0f && !loadingComplete) {
            loadingComplete = true;
            showJumpScare = true;
            jumpScareClock.restart();
            jumpScareSound.play();
            soundManager.stopLoadingMusic(); // Stop loading music when jumpscare starts
        }
    }
    // Handle jump scare duration
    if (showJumpScare && jumpScareClock.getElapsedTime().asSeconds() >= JUMP_SCARE_DURATION) {
        showJumpScare = false;
        currentState = MAIN_MENU;
        // Reset view in case it was affected by shaking
        mainWindow.setView(mainWindow.getDefaultView());
        return; // Skip other updates this frame
    }
    bool questionDelayComplete = false;
    if (showingPhaseIntro) {
        if (introTypingClock.getElapsedTime().asSeconds() >= introTypingSpeed) {
            if (!introLineComplete) {
                introCharIndex++;
                if (introCharIndex >= currentPhaseIntro[0].size()) {
                    introLineComplete = true;
                }
                introTypingClock.restart();
            }
        }
        return;
    }
    if (isShaking) {
        soundManager.playHeartbeat();
        float shakeTime = shakeClock.getElapsedTime().asSeconds();
        float shakeDuration = shakeDurationClock.getElapsedTime().asSeconds();

        // Only reduce intensity after minimum duration has passed
        if (shakeDuration >= minShakeDuration) {
            // Gradually reduce shake intensity over time
            float reductionRate = currentPhase == 1 ? 0.5f :
                currentPhase == 2 ? 0.4f :
                0.3f;
            shakeIntensity = max(0.0f, shakeIntensity - shakeTime * reductionRate);
        }

        // If intensity reaches 0, stop shaking
        if (shakeIntensity <= 0.0f) {
            soundManager.stopHeartbeat();
            isShaking = false;
        }
    }


    if (currentState == IN_GAME && !showPhaseCompleteScreen && !showGameCompleteScreen) {

        if (currentPhase == 3) {
            // show blood when there is 50% time left
                // show blood when there is 50% time left
            if (timeRemaining < maxTime * 0.3f) {
                showBloodSplatter = true;
                bloodSprite.setColor(Color(255, 255, 255, static_cast<Uint8>(bloodAlpha)));
            }
            else {
                showBloodSplatter = false;
            }
        }
        else {
            showBloodSplatter = false;
        }
        // Handle the delay between encounter and question
        if (isInDelay && delayTimer.getElapsedTime().asSeconds() >= QUESTION_DELAY) {
            isInDelay = false;
        }

        // Update timer
        if (questionSpriteLoaded && encounterLoadingComplete && questionLoadingComplete) {
            timeRemaining = max(0.0f, timeRemaining - questionTimer.getElapsedTime().asSeconds());
            questionTimer.restart();


            // If the timer runs out
            if (timeRemaining <= 0) {
                if (!answered) {
                    if (selectedAnswer != -1) {
                        // Process the selected answer if one exists
                        answered = true;
                        processAnswer();
                    }
                    else {
                        // No answer selected, the user gets zero points
                        answered = true;
                        soundManager.playWrong(); // Play wrong answer sound as feedback
                    }
                }
                // Move to the next question regardless
                loadNextQuestion();
            }
        }

        if (!encounterLoadingComplete && questionSpriteLoaded) {
            if (charIndex < currentEncounterText.size() && typingClock.getElapsedTime().asSeconds() >= typingSpeed) {
                charIndex++;
                typingClock.restart();
                if (charIndex >= currentEncounterText.size()) {
                    encounterLoadingComplete = true;
                    charIndex = 0;
                    isInDelay = true;
                    delayTimer.restart();
                }
            }
        }



        if (!questionLoadingComplete && !isInDelay && questionSpriteLoaded && encounterLoadingComplete) { // Only proceed with question if delay is over

            if (charIndex < displayedQuestionText.size() && typingClock.getElapsedTime().asSeconds() >= typingSpeed) {
                //   sleep(seconds(3));
                charIndex++;
                typingClock.restart();
                if (charIndex >= displayedQuestionText.size()) {
                    questionLoadingComplete = true;
                    setupOptionsGraphics();
                }
            }
        }
    }
}
void Quiz::renderLoadingScreen() {
    mainWindow.clear(Color::Black); // Black background

    // Draw logo2 centered
    Texture logo2Texture;
    if (logo2Texture.loadFromFile("./resources/logo2.png")) {
        Sprite logo2Sprite(logo2Texture);

        // Center the logo
        FloatRect logo2Bounds = logo2Sprite.getLocalBounds();
        logo2Sprite.setOrigin(logo2Bounds.width / 2, logo2Bounds.height / 2);
        logo2Sprite.setPosition(mainWindow.getSize().x / 2, mainWindow.getSize().y / 2 - 50);

        // Scale if needed (optional)
        float maxSize = 300.0f;
        if (logo2Bounds.width > maxSize || logo2Bounds.height > maxSize) {
            float scale = maxSize / max(logo2Bounds.width, logo2Bounds.height);
            logo2Sprite.setScale(scale, scale);
        }

        mainWindow.draw(logo2Sprite);
    }
    else {
        // Fallback if logo2.png doesn't exist
        Text fallbackText("APOCALYPSE", font, 60);
        fallbackText.setFillColor(Color::Red);
        FloatRect fallbackBounds = fallbackText.getLocalBounds();
        fallbackText.setPosition(
            (mainWindow.getSize().x - fallbackBounds.width) / 2,
            mainWindow.getSize().y / 2 - 50
        );
        mainWindow.draw(fallbackText);
    }

    // Draw game name
    mainWindow.draw(loadingText);

    // Update loading bar
    float progress = min(1.0f, loadingClock.getElapsedTime().asSeconds() / 15.0f);
    loadingBar.setSize(Vector2f(700 * progress, 30));

    // Draw loading bar
    mainWindow.draw(loadingBarBackground);
    mainWindow.draw(loadingBar);

    // Display loading percentage text below the bar
    Text loadingProgressText("Loading... " + to_string(int(progress * 100)) + "%", font, 24);
    loadingProgressText.setFillColor(Color::White);
    FloatRect progressBounds = loadingProgressText.getLocalBounds();
    loadingProgressText.setPosition(
        (mainWindow.getSize().x - progressBounds.width) / 2,
        loadingBarBackground.getPosition().y + 40
    );
    mainWindow.draw(loadingProgressText);

    mainWindow.display();


    // Check if loading is complete
    if (progress >= 1.0f && !loadingComplete) {
        loadingComplete = true;
        showJumpScare = true;
        jumpScareClock.restart();
        jumpScareSound.play();
        soundManager.stopLoadingMusic();
        currentState = MAIN_MENU;
    }
}
void Quiz::renderMainMenu() {
    mainWindow.clear();  // Draw the background (using member variable)
    // mainWindow.draw(menuBackgroundSprite);
     // Draw logo
    Texture logoTexture;
    if (logoTexture.loadFromFile("./resources/logo.png")) {
        Sprite logoSprite(logoTexture);
        FloatRect logoBounds = logoSprite.getLocalBounds();
        logoSprite.setOrigin(logoBounds.width / 2, 0);
        logoSprite.setPosition(mainWindow.getSize().x / 2, 50);
        mainWindow.draw(logoSprite);
    }

    mainWindow.draw(titleText);
    mainWindow.draw(playButton.button);
    mainWindow.draw(playButton.label);
    mainWindow.draw(settingsButton.button);
    mainWindow.draw(settingsButton.label);
    mainWindow.draw(exitButton.button);
    mainWindow.draw(exitButton.label);
    mainWindow.draw(leaderboardButton.button);
    mainWindow.draw(leaderboardButton.label);
    mainWindow.display();
}

void Quiz::renderPlayerNameInput() {
    mainWindow.clear();
    mainWindow.draw(namePromptText);
    mainWindow.draw(nameInputText);
    mainWindow.draw(nameSubmitButton.button);
    mainWindow.draw(nameSubmitButton.label);
    mainWindow.display();
}

void Quiz::renderTutorial() {
    mainWindow.clear();
    mainWindow.draw(tutorialText);
    mainWindow.draw(tutorialContinueButton.button);
    mainWindow.draw(tutorialContinueButton.label);
    mainWindow.display();
}

void Quiz::renderSettings() {
    mainWindow.clear();
    mainWindow.draw(settingsTitle);
    mainWindow.draw(soundToggleButton.button);
    mainWindow.draw(soundToggleButton.label);
    mainWindow.draw(soundStatusText);
    // mainWindow.draw(difficultyButton.button);
    // mainWindow.draw(difficultyButton.label);
    //mainWindow.draw(difficultyText);
    mainWindow.draw(settingsBackButton.button);
    mainWindow.draw(settingsBackButton.label);
    mainWindow.display();
}



void Quiz::setupProgressBar() {
    float progressBarWidth = 700.0f;
    float progressBarHeight = 20.0f;
    float centerX = (mainWindow.getSize().x - progressBarWidth) / 2.0f;
    float centerY = 650.0f; // Position below the options

    // Background of the progress bar
    progressBarBackground.setSize(Vector2f(progressBarWidth, progressBarHeight));
    progressBarBackground.setFillColor(Color(50, 50, 50)); // Dark gray
    progressBarBackground.setPosition(centerX, centerY);

    // Fill of the progress bar
    progressBarFill.setSize(Vector2f(0, progressBarHeight)); // Start with 0 progress
    progressBarFill.setFillColor(Color(0, 150, 0)); // Green
    progressBarFill.setPosition(centerX, centerY);

    progressBarStatus.setFillColor(Color(0, 150, 0)); // Green
    progressBarStatus.setPosition(centerX, centerY + 40);
}

void Quiz::updateProgressBar() {
    //string progressStatus = "Question " + currentQuestionIndex + " of 8";
    string currentQuestionIndexString = to_string(currentQuestionIndex + 1);
    if (!currentQuestions.empty() && currentQuestionIndex < 8) {
        float progress = static_cast<float>(currentQuestionIndex + 1) / currentQuestions.size();
        float progressBarWidth = progressBarBackground.getSize().x;
        progressBarFill.setSize(Vector2f(progressBarWidth * progress, progressBarBackground.getSize().y));
        progressBarStatus.setFont(font);
        progressBarStatus.setString("Question " + currentQuestionIndexString + " of 8");
        progressBarStatus.setCharacterSize(30);
        progressBarStatus.setFillColor(Color::Green);
        progressBarStatus.setStyle(Text::Bold);
    }
}


void Quiz::renderGame() {
    // for shaking 
    View currentView = mainWindow.getView();

    if (isShaking) {
        // Apply random offset based on intensity
        float offsetX = (rand() % 100 - 50) * 0.01f * shakeIntensity;
        float offsetY = (rand() % 100 - 50) * 0.01f * shakeIntensity;
        currentView.setCenter(originalViewCenter + Vector2f(offsetX, offsetY));
    }
    else {
        // Reset to normal view when not shaking
        currentView.setCenter(originalViewCenter);
    }

    mainWindow.setView(currentView);


    mainWindow.clear();
    mainWindow.draw(currentBackgroundSprite);
    if (showingPhaseIntro) {
        // Draw dark overlay
        RectangleShape overlay(Vector2f(mainWindow.getSize().x, mainWindow.getSize().y));
        overlay.setFillColor(Color(0, 0, 0, 200));
        mainWindow.draw(overlay);

        // Draw intro box
        RectangleShape introBox(Vector2f(700, 500));
        introBox.setFillColor(Color(30, 30, 30, 220));
        introBox.setOutlineColor(Color::White);
        introBox.setOutlineThickness(2);
        introBox.setPosition(100, 100);
        mainWindow.draw(introBox);

        // Draw intro title
        Text introTitle("PHASE " + to_string(currentPhase) + " BEGINS", font, 40);
        introTitle.setFillColor(Color::Red);
        introTitle.setStyle(Text::Bold);
        FloatRect titleBounds = introTitle.getLocalBounds();
        introTitle.setPosition(introBox.getPosition().x + (introBox.getSize().x - titleBounds.width) / 2,
            introBox.getPosition().y + 20);
        mainWindow.draw(introTitle);

        // Draw wrapped intro text
        String currentText = getCurrentIntroText();
        Text introText(wrapIntroText(currentText, font, 28, introBox.getSize().x - 40), font, 28);
        introText.setFillColor(Color::White);
        introText.setPosition(introBox.getPosition().x + 20, introBox.getPosition().y + 80);
        mainWindow.draw(introText);

        // Draw continue prompt
        if (introLineComplete) {
            Text continueText("Press any key to begin...", font, 24);
            continueText.setFillColor(Color(200, 200, 200));
            continueText.setStyle(Text::Italic);
            FloatRect contBounds = continueText.getLocalBounds();
            continueText.setPosition(introBox.getPosition().x + (introBox.getSize().x - contBounds.width) / 2,
                introBox.getPosition().y + introBox.getSize().y - 50);
            mainWindow.draw(continueText);
        }
        if (currentPhase == 3 && showBloodSplatter) { // only show blood splatter in phase 3
            mainWindow.draw(bloodSprite);
        }
        mainWindow.display();
        return;
    }


    if (showPhaseCompleteScreen) {
        int currentScore = currentPhase == 1 ? phase1Score :
            (currentPhase == 2 ? phase2Score : phase3Score);

        // Calculate percentage (capped at 100%)
        int percentage = min(100, (currentScore * 100) / 1000);

        string performance;
        Color performanceColor;
        if (percentage >= 90) {
            performance = "EPIC SURVIVOR!";
            performanceColor = Color::Cyan;
        }
        else if (percentage >= 75) {
            performance = "SKILLED SURVIVOR";
            performanceColor = Color::Green;
        }
        else if (percentage >= 50) {
            performance = "AVERAGE SURVIVOR";
            performanceColor = Color::Yellow;
        }
        else {
            performance = "NOVICE SURVIVOR";
            performanceColor = Color(255, 165, 0);
        }

        string scoreStr = "Rating: " + performance + "\n" +
            "Score: " + to_string(currentScore) + "/1000\n" +
            "Completion: " + to_string(percentage) + "%\n\n";

        string phaseFeedback;
        if (currentPhase == 1) {
            phaseFeedback = percentage >= 75 ?
                "You secured excellent supplies and fortified your base!" :
                percentage >= 50 ?
                "You gathered enough to survive, but supplies are limited." :
                "You barely made it... better prepare for the next phase.";
        }
        else if (currentPhase == 2) {
            phaseFeedback = percentage >= 75 ?
                "You've mastered combat against the infected hordes!" :
                percentage >= 50 ?
                "You're holding your own, but the zombies are evolving." :
                "The infected are overwhelming you... need better tactics.";
        }
        else {
            phaseFeedback = percentage >= 75 ?
                "You've become an apex survivor of the apocalypse!" :
                percentage >= 50 ?
                "You survived against all odds, but just barely." :
                "The outbreak proved too much to handle...";
        }

        Text ratingText(performance, font, 36);
        ratingText.setFillColor(performanceColor);
        ratingText.setPosition(450 - ratingText.getLocalBounds().width / 2, 180);

        Text scoreDisplayText(scoreStr + phaseFeedback, font, 24);
        scoreDisplayText.setFillColor(Color::White);
        scoreDisplayText.setPosition(150, 250);

        phaseCompleteText.setString("PHASE " + to_string(currentPhase) + " COMPLETE");
        phaseCompleteText.setPosition(450 - phaseCompleteText.getLocalBounds().width / 2, 100);

        continueButton.button.setPosition(350, 500);
        continueButton.label.setString("CONTINUE");
        continueButton.label.setPosition(370, 510);

        mainWindow.draw(phaseCompleteText);
        mainWindow.draw(ratingText);
        mainWindow.draw(scoreDisplayText);
        mainWindow.draw(continueButton.button);
        mainWindow.draw(continueButton.label);
    }
    if (!currentQuestions.empty()) {
        // Always draw the question sprite first if it's loaded
        if (questionSpriteLoaded && currentQuestionIndex < 8) {
            mainWindow.draw(questionSprites[currentPhase - 1][currentQuestionIndex]);
        }

        if (!currentEncounters.empty()) {
            String currentEncounterDisplay = displayedEncounterText.substr(0,
                encounterLoadingComplete ? displayedEncounterText.size() : charIndex);
            encounterTextDisplay.setString(currentEncounterDisplay);
            mainWindow.draw(encounterTextDisplay);
        }


        if (encounterLoadingComplete) {

            // Draw the question text box
            mainWindow.draw(questionTextBox);


            String currentQuestionDisplay = displayedQuestionText.substr(0,
                questionLoadingComplete ? displayedQuestionText.size() : charIndex);
            questionTextDisplay.setString(currentQuestionDisplay);
            mainWindow.draw(questionTextDisplay);

            // Enhanced timer display
            timerText.setFont(font);
            timerText.setCharacterSize(36); // Larger size
            timerText.setFillColor(timeRemaining < (maxTime * 0.4f) ? Color::Red : Color::Yellow); // change to red when there is 40% time left
            timerText.setString("TIME: " + to_string(static_cast<int>(timeRemaining)) + "s");
            timerText.setPosition(700, 30); // Top-right position
            timerText.setStyle(Text::Bold);
            mainWindow.draw(timerText);

            // Current score display
            totalScoreText.setFont(font);
            totalScoreText.setCharacterSize(36);
            totalScoreText.setFillColor(Color::Red);
            totalScoreText.setString("SCORE: " + to_string(static_cast<int>(totalScore)));
            totalScoreText.setPosition(50, 30);
            totalScoreText.setStyle(Text::Bold);
            mainWindow.draw(totalScoreText);
            if (questionLoadingComplete) {
                for (size_t i = 0; i < optionBoxes.size(); ++i) {
                    mainWindow.draw(optionBoxes[i]);
                    mainWindow.draw(optionTexts[i]);
                }

                if (answered) {
                    nextButtonSprite.setPosition(700, 720);
                    mainWindow.draw(nextButtonSprite);
                }
            }
        }
        mainWindow.draw(progressBarBackground);
        mainWindow.draw(progressBarFill);
        mainWindow.draw(progressBarStatus);
    }
    if (currentPhase == 3 && showBloodSplatter) {
        mainWindow.draw(bloodSprite);
    }
    mainWindow.display();
    mainWindow.setView(mainWindow.getDefaultView());
}


String wrapText(const String& text, Font& font, unsigned int characterSize, float maxWidth) {
    istringstream words(text.toAnsiString());
    string word, wrappedText;
    Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(characterSize);

    string line;
    while (words >> word) {
        String tempLine = line + (line.empty() ? "" : " ") + word;
        tempText.setString(tempLine);
        if (tempText.getLocalBounds().width > maxWidth) {
            wrappedText += line + "\n";
            line = word;
        }
        else {
            line += (line.empty() ? "" : " ") + word;
        }
    }
    wrappedText += line;
    return wrappedText;
}
String wrapIntroText(const String& text, Font& font, unsigned int characterSize, float maxWidth) {
    istringstream words(text.toAnsiString());
    string word, wrappedText;
    Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(characterSize);

    string line;
    while (words >> word) {
        String tempLine = line + (line.empty() ? "" : " ") + word;
        tempText.setString(tempLine);
        if (tempText.getLocalBounds().width > maxWidth) {
            wrappedText += line + "\n";
            line = word;
        }
        else {
            line += (line.empty() ? "" : " ") + word;
        }
    }
    wrappedText += line;
    return wrappedText;
}
String Quiz::getCurrentIntroText() {
    String fullText;
    for (size_t i = 0; i < currentIntroLine; i++) {
        fullText += currentPhaseIntro[i] + "\n";
    }
    if (currentIntroLine < currentPhaseIntro.size()) {
        fullText += currentPhaseIntro[currentIntroLine].substr(0, introCharIndex);
    }
    return fullText;
}
string getEndingMessage(int path) {
    switch (path) {
    case 1: // Best ending
        return "EPIC VICTORY!\n\n"
            "You successfully destroyed the hive mind!\n"
            "The infected collapse without their control.\n"
            "Humanity will rebuild thanks to your courage.\n\n"
            "True hero status achieved!";

    case 2: // Good ending
        return "HARD-WON SURVIVAL\n\n"
            "You secured the cure and made it to safety.\n"
            "Though many were lost, your efforts give hope.\n"
            "The fight continues, but humanity endures.\n\n"
            "You're a true survivor.";

    case 3: // Bad ending
        return "BITTER ESCAPE\n\n"
            "You barely made it out alive, alone and wounded.\n"
            "The infection continues to spread unchecked.\n"
            "But as long as you breathe, hope remains...\n\n"
            "Survival comes at a cost.";

    case 4: // Worst ending
        return "FINAL NIGHTMARE\n\n"
            "The infected overwhelm your last defenses.\n"
            "As darkness takes you, you hear their whispers...\n"
            "You've become part of the horde now.\n\n"
            "Game Over.";

    default:
        return "Your journey ends here...";
    }
}

void Quiz::renderGameComplete() {
    mainWindow.clear(Color(20, 20, 20));

    string finalScoreStr = getEndingMessage(player.survivalPath) + "\n\n" +
        player.name + "'s Survival Report:\n\n" +
        "Phase 1: " + to_string(phase1Score) + "/1000\n" +
        "Phase 2: " + to_string(phase2Score) + "/1000\n" +
        "Phase 3: " + to_string(phase3Score) + "/1000\n\n" +
        "Total Score: " + to_string(phase1Score + phase2Score + phase3Score) + "\n";

    scoreText.setString(finalScoreStr);
    scoreText.setPosition(100, 150);
    scoreText.setCharacterSize(24);

    phaseCompleteText.setString("YOUR STORY ENDS");
    phaseCompleteText.setPosition(300, 50);
    phaseCompleteText.setCharacterSize(40);

    continueButton.button.setPosition(350, 500);
    continueButton.label.setString("LEADERBOARD");
    continueButton.label.setPosition(370, 510);

    mainWindow.draw(phaseCompleteText);
    mainWindow.draw(scoreText);
    mainWindow.draw(continueButton.button);
    mainWindow.draw(continueButton.label);
    mainWindow.display();
}

void Quiz::renderLeaderboard() {
    mainWindow.clear(Color(20, 20, 20));

    Text leaderboardTitle("TOP SURVIVORS", font, 50);
    leaderboardTitle.setFillColor(Color::Red);
    leaderboardTitle.setPosition(300, 50);
    mainWindow.draw(leaderboardTitle);

    Text subtitle("Can you make it to the top?", font, 24);
    subtitle.setFillColor(Color::White);
    subtitle.setPosition(300, 120);
    mainWindow.draw(subtitle);

    int playerTotalScore = phase1Score + phase2Score + phase3Score;
    bool playerInTop10 = false;

    int i = 0;
    for (const auto& p : leaderboardPlayers) {
        if (i >= 10) break;

        string entry = std::to_string(i + 1) + ". " + p.name + " - " + std::to_string(p.score);
        Text scoreText(entry, font, 28);
        scoreText.setPosition(300, 180 + i * 40);

        if (p.name == player.name && p.score == playerTotalScore) {
            scoreText.setFillColor(Color::Green);
            playerInTop10 = true;
        }
        else {
            scoreText.setFillColor(Color::White);
        }

        mainWindow.draw(scoreText);
        ++i;
    }

    if (!playerInTop10) {
        string playerEntry = player.name + " - " + std::to_string(playerTotalScore);
        Text playerText("Your score: " + playerEntry, font, 28);
        playerText.setFillColor(Color::Yellow);
        playerText.setPosition(300, 620);
        mainWindow.draw(playerText);
    }

    mainWindow.draw(leaderboardContinueButton.button);
    mainWindow.draw(leaderboardContinueButton.label);
    mainWindow.display();
}


void Quiz::render() {
    if (showJumpScare) {
        // Reset to default view
        mainWindow.setView(mainWindow.getDefaultView());

        // Show jump scare for the duration
        mainWindow.clear();
        mainWindow.draw(jumpScareSprite);
        mainWindow.display();
        return;
    }

    switch (currentState) {
    case MAIN_MENU: renderMainMenu(); break;
    case PLAYER_NAME_INPUT: renderPlayerNameInput(); break;
    case TUTORIAL: renderTutorial(); break;
    case SETTINGS: renderSettings(); break;
    case IN_GAME: renderGame(); break;
    case GAME_COMPLETE: renderGameComplete(); break;
    case LEADERBOARD: renderLeaderboard(); break;
    default: break;
    }
}

Quiz::Quiz(RenderWindow& window) :mainWindow(window), currentState(LOADING), showJumpScare(false), loadingComplete(false) {

        if (!font.loadFromFile("./resources/arial.ttf")) {
            cerr << "Could not load arial.ttf font in Quiz class" << endl;
        }
        setupLoadingScreen();


        /**if (!phase1BackgroundTexture.loadFromFile("./resources/Background1.jpg")) {
             cerr << "Error: Could not load phase1_zombies.png!\n";
         }
         if (!phase2BackgroundTexture.loadFromFile("./resources/alienBackground1.jpg")) {
             cerr << "Error: Could not load phase2_zombies.png!\n";
         }
         if (!phase3BackgroundTexture.loadFromFile("./resources/phase3_zombies.png")) {
             cerr << "Error: Could not load phase3_zombies.png!\n";
         }
         if (!phase4BackgroundTexture.loadFromFile("./resources/phase4_zombies.png")) {
             cerr << "Error: Could not load phase4_zombies.png!\n";
         }*/
        if (!nextButtonTexture.loadFromFile("./resources/forward_button.png")) {
            cerr << "Error: Could not load forward_button\n";
        }
        if (!jumpScareTexture.loadFromFile("./resources/jumpscare.png")) {
            cerr << "Error: Could not load jumpscare.png!\n";
        }
        else {
            cout << "Jumpscare texture loaded successfully\n";
        }
        jumpScareSprite.setTexture(jumpScareTexture);
        // Scale to full screen
        jumpScareSprite.setScale(
            float(mainWindow.getSize().x) / jumpScareTexture.getSize().x,
            float(mainWindow.getSize().y) / jumpScareTexture.getSize().y
        );

        if (!jumpScareSoundBuffer.loadFromFile("./resources/jumpscare_sound.wav")) {
            cerr << "Error: Could not load jumpscare_sound.wav!\n";
        }
        jumpScareSound.setBuffer(jumpScareSoundBuffer);
        jumpScareSound.setVolume(100.0f);


        originalViewCenter = mainWindow.getView().getCenter(); // for shaking

        currentBackgroundSprite.setTexture(phase1BackgroundTexture);
        scaleBackground();

        if (!bloodTexture.loadFromFile("./resources/blood_splatter.png")) {
            cerr << "Error: Could not load blood_splatter.png!\n";
            // Create a simple red overlay if file not found
            bloodTexture.create(mainWindow.getSize().x, mainWindow.getSize().y);
            Image tempImage;
            tempImage.create(mainWindow.getSize().x, mainWindow.getSize().y, Color::Transparent);
            // Create some random red splatters
            for (int i = 0; i < 1000; i++) {
                int x = rand() % mainWindow.getSize().x;
                int y = rand() % mainWindow.getSize().y;
                tempImage.setPixel(x, y, Color(200, 0, 0, 150));
            }
            bloodTexture.loadFromImage(tempImage);
        }
        bloodSprite.setTexture(bloodTexture);
        bloodSprite.setColor(Color(255, 255, 255, static_cast<Uint8>(bloodAlpha)));
        bloodSprite.setScale(
            float(mainWindow.getSize().x) / bloodTexture.getSize().x,
            float(mainWindow.getSize().y) / bloodTexture.getSize().y
        );
        // Load question images for all phases
        for (int phase = 0; phase < 3; phase++) {
            for (int question = 0; question < 8; question++) {
                string filename = "./resources/phase" + to_string(phase + 1) + "Q" + to_string(question + 1) + ".jpg";
                if (!questionTextures[phase][question].loadFromFile(filename)) {
                    cerr << "Error: Could not load question image " << filename << "!\n";
                    // Create a placeholder texture if image not found
                    Image placeholder;
                    placeholder.create(200, 200, Color(100, 100, 100, 150));
                    questionTextures[phase][question].loadFromImage(placeholder);
                }
                questionSprites[phase][question].setTexture(questionTextures[phase][question]);

                // Scale and position the question sprites
                questionSprites[phase][question].setScale(0.5f, 0.5f);
                questionSprites[phase][question].setPosition(50, 200);
            }
        }
        questionTexturesLoaded = true;

        for (int phase = 0; phase < 3; phase++) {
            for (int question = 0; question < 8; question++) {
                // [Texture loading code...]

                // Calculate scale to exactly fill window (may distort aspect ratio)
                Vector2u windowSize = mainWindow.getSize();
                Vector2u textureSize = questionTextures[phase][question].getSize();

                float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
                float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

                questionSprites[phase][question].setScale(scaleX, scaleY);
                questionSprites[phase][question].setPosition(0, 0); // Start at top-left corner
            }
        }
        // In the Quiz constructor, after setting up other elements
        questionTextBox.setSize(Vector2f(800, 130));
        questionTextBox.setFillColor(Color(30, 30, 30, 220)); // Dark grey with slight transparency
        questionTextBox.setOutlineColor(Color::Black);
        questionTextBox.setOutlineThickness(2);
        questionTextBox.setPosition(50, 180); // Position below the encounter text

        questionTextDisplay.setFont(font);
        questionTextDisplay.setCharacterSize(24);
        questionTextDisplay.setFillColor(Color::White);
        questionTextDisplay.setPosition(70, 200);

        encounterTextDisplay.setFont(font);
        encounterTextDisplay.setCharacterSize(24);
        encounterTextDisplay.setFillColor(Color::White);
        encounterTextDisplay.setPosition(50, 75);

        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(350, 300);

        phaseCompleteText.setFont(font);
        phaseCompleteText.setCharacterSize(40);
        phaseCompleteText.setFillColor(Color::White);
        phaseCompleteText.setString("Phase Complete!");
        phaseCompleteText.setPosition(300, 200);

        nextButtonSprite.setTexture(nextButtonTexture);
        nextButtonSprite.setScale(1.0f, 1.0f);
        nextButtonSprite.setPosition(700, 620);

        continueButton.button.setSize(Vector2f(200, 50));
        continueButton.button.setPosition(350, 400);
        continueButton.button.setFillColor(Color::Green);
        continueButton.label.setFont(font);
        continueButton.label.setCharacterSize(24);
        continueButton.label.setFillColor(Color::White);
        continueButton.label.setString("Continue");
        continueButton.label.setPosition(375, 410);

        setupMainMenu();
        setupPlayerNameInput();
        setupTutorial();
        setupSettings();
        //**
        setupProgressBar();
    }

    void Quiz::run() {
        Clock loadingClock;
        bool loadingComplete = false;

        while (mainWindow.isOpen()) {
            Event event;
            while (mainWindow.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    mainWindow.close();
                }
                // Only handle input if we're past the loading screen
                if (currentState != LOADING) {
                    handleInput(event);
                }
            }
            // Handle loading state
            if (currentState == LOADING) {
                float progress = min(1.0f, loadingClock.getElapsedTime().asSeconds() / 15.0f); // 3 second loading
                renderLoadingScreen();
                continue; // Skip other updates while loading
            }

            update();
            //**
            updateProgressBar();
            render();
        }
    }

    String Quiz::wrapIntroText(const sf::String& text, sf::Font& font,
        unsigned int characterSize, float maxWidth) {
        std::istringstream words(text.toAnsiString());
        std::string word, wrappedText;
        sf::Text tempText;
        tempText.setFont(font);
        tempText.setCharacterSize(characterSize);

        std::string line;
        while (words >> word) {
            sf::String tempLine = line + (line.empty() ? "" : " ") + word;
            tempText.setString(tempLine);
            if (tempText.getLocalBounds().width > maxWidth) {
                wrappedText += line + "\n";
                line = word;
            }
            else {
                line += (line.empty() ? "" : " ") + word;
            }
        }
        wrappedText += line;
        return wrappedText;
    }

    String Quiz::wrapText(const sf::String& text, sf::Font& font,
        unsigned int characterSize, float maxWidth) {
        std::istringstream words(text.toAnsiString());
        std::string word, wrappedText;
        sf::Text tempText;
        tempText.setFont(font);
        tempText.setCharacterSize(characterSize);

        std::string line;
        while (words >> word) {
            sf::String tempLine = line + (line.empty() ? "" : " ") + word;
            tempText.setString(tempLine);
            if (tempText.getLocalBounds().width > maxWidth) {
                wrappedText += line + "\n";
                line = word;
            }
            else {
                line += (line.empty() ? "" : " ") + word;
            }
        }
        wrappedText += line;
        return wrappedText;
    }

    std::string Quiz::getEndingMessage(int path) {
        switch (path) {
        case 1: // Best ending
            return "EPIC VICTORY!\n\n"
                "You successfully destroyed the hive mind!\n"
                "The infected collapse without their control.\n"
                "Humanity will rebuild thanks to your courage.\n\n"
                "True hero status achieved!";

        case 2: // Good ending
            return "HARD-WON SURVIVAL\n\n"
                "You secured the cure and made it to safety.\n"
                "Though many were lost, your efforts give hope.\n"
                "The fight continues, but humanity endures.\n\n"
                "You're a true survivor.";

        case 3: // Bad ending
            return "BITTER ESCAPE\n\n"
                "You barely made it out alive, alone and wounded.\n"
                "The infection continues to spread unchecked.\n"
                "But as long as you breathe, hope remains...\n\n"
                "Survival comes at a cost.";

        case 4: // Worst ending
            return "FINAL NIGHTMARE\n\n"
                "The infected overwhelm your last defenses.\n"
                "As darkness takes you, you hear their whispers...\n"
                "You've become part of the horde now.\n\n"
                "Game Over.";

        default:
            return "Your journey ends here...";
        }
    }



