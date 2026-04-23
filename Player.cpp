#include "Player.h"
#include <array>

Player::Player(const std::string& playerName, int diff) :
    name(playerName), score(0), difficulty(diff), survivalPath(1) {
}

void Player::increaseScore(int points) {
    score += points;
}

void Player::resetScore() {
    score = 0;
}

int Player::getScore() const {
    return score;
}

bool Player::operator<(const Player& other) const {
    return score > other.score; // For descending order
}

// Leaderboard implementation
void Player::saveLeaderboard(const std::set<Player>& players) {
    std::ofstream outFile("leaderboard.txt");
    if (outFile.is_open()) {
        for (const auto& player : players) {
            outFile << player.name << "," << player.score << "\n";
        }
        outFile.close();
    }
}

std::set<Player> Player::loadLeaderboard() {
    std::set<Player> players;
    std::ifstream inFile("leaderboard.txt");

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string name = line.substr(0, commaPos);
                int score = std::stoi(line.substr(commaPos + 1));
                Player p(name, 2);
                p.score = score;
                players.insert(p);
            }
        }
        inFile.close();
    }
    else {
        // Default leaderboard
        std::array<std::string, 10> names = {
            "ALICE", "BOB", "CAROL", "DAVE", "EVE",
            "FRANK", "GRACE", "HANK", "IVY", "JACK"
        };
        std::array<int, 10> scores = {
            2500, 2200, 1950, 1800, 1650,
            1500, 1350, 1200, 1050, 900
        };

        for (size_t i = 0; i < names.size(); ++i) {
            Player p(names[i], 2);
            p.score = scores[i];
            players.insert(p);
        }

        saveLeaderboard(players);
    }

    return players;
}