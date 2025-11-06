#ifndef __SCORE_H__
#define __SCORE_H__

#include <vector>
#include <string>

class Score
{
public:
    std::string name;
    int score;

    Score(const std::string& name = "", int score = 0) : name(name), score(score) {}

    // Hàm lưu danh sách điểm số cao vào tệp .txt
    static void saveHighScoresToFile(const std::vector<Score>& highScores);

    // Hàm thêm điểm số mới và cập nhật danh sách điểm cao
    static void addHighScoreToFile(int score, const std::string& name);

    // Hàm tải danh sách điểm số cao từ tệp
    static std::vector<Score> loadHighScoresFromFile();
};
#endif // __SCORE_H__
