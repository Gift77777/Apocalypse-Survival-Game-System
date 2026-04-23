#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>
#include <fstream>

class Player {
public:
    std::string name;
    int score;
    int difficulty; // 1=easy, 2=medium, 3=hard
    int survivalPath; // Tracks which story path player is on

    Player(const std::string& playerName = "Survivor", int diff = 2);
    void increaseScore(int points);
    void resetScore();
    int getScore() const;
    bool operator<(const Player& other) const;

    // Leaderboard methods
    static void saveLeaderboard(const std::set<Player>& players);
    static std::set<Player> loadLeaderboard();
};

#endif // PLAYER_H