#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

class Question {
public:
    struct StoryText {
        std::string storyText;
        operator std::string() const { return storyText; }
    };

    struct QuestionData {
        std::string questionText;
        std::vector<std::string> options;
        int correctAnswerIndex;
        bool isTrueFalse;
        int difficultyLevel;
    };

    // Declaring the phase structs 
    struct Phase_1 {
        std::vector<QuestionData> path_1;
        std::vector<StoryText> path1_Encounters;
        Phase_1(); 
    };

    struct Phase_2 {
        std::vector<QuestionData> path_1;
        std::vector<QuestionData> path_2;
        std::vector<StoryText> path1_Encounters;
        std::vector<StoryText> path2_Encounters;
        Phase_2();  
    };

    struct Phase_3 {
        std::vector<QuestionData> path_1;
        std::vector<QuestionData> path_2;
        std::vector<QuestionData> path_3;
        std::vector<QuestionData> path_4;
        std::vector<StoryText> path1_Encounters;
        std::vector<StoryText> path2_Encounters;
        std::vector<StoryText> path3_Encounters;
        std::vector<StoryText> path4_Encounters;
        Phase_3();  
    };
};

#endif // QUESTION_H