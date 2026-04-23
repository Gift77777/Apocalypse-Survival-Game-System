#include "Quiz.h"

int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(900, 900), "Apocalypse Survival Quiz");
    Quiz quiz(mainWindow);
    quiz.run();
    return 0;
}