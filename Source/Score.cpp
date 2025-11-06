#include "Score.h"
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <algorithm>

using namespace rapidjson;

void Score::saveHighScoresToFile(const std::vector<Score>& highScores)
{
    // Tạo đối tượng JSON
    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator();

    // Mảng để chứa các điểm số
    rapidjson::Value scoreArray(kArrayType);

    for (const auto& score : highScores)
    {
        // Tạo đối tượng JSON cho mỗi điểm số
        rapidjson::Value scoreObject(kObjectType);
        scoreObject.AddMember("name", rapidjson::Value(score.name.c_str(), allocator), allocator);
        scoreObject.AddMember("score", score.score, allocator);
        scoreArray.PushBack(scoreObject, allocator);
    }

    // Thêm mảng điểm số vào tài liệu
    doc.AddMember("highScores", scoreArray, allocator);

    // Ghi dữ liệu vào tệp
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    // Lưu vào tệp .json
    std::ofstream file("highscores.json");
    if (file.is_open())
    {
        file << buffer.GetString();
        file.close();
    }
}

void Score::addHighScoreToFile(int score, const std::string& name)
{
    // Tải danh sách điểm số hiện tại
    std::vector<Score> highScores = loadHighScoresFromFile();

    // Thêm điểm số mới
    highScores.push_back(Score(name, score));

    // Sắp xếp danh sách điểm số theo thứ tự giảm dần
    std::sort(highScores.begin(), highScores.end(), [](const Score& a, const Score& b) {
        return a.score > b.score;  // So sánh theo điểm số
    });

    // Giới hạn số lượng điểm số chỉ còn 10
    if (highScores.size() > 10)
    {
        highScores.resize(10);
    }

    // Lưu lại danh sách điểm số
    saveHighScoresToFile(highScores);
}

std::vector<Score> Score::loadHighScoresFromFile()
{
    std::vector<Score> highScores;

    // Đọc tệp JSON
    std::ifstream file("highscores.json");
    if (file.is_open())
    {
        std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // Phân tích cú pháp JSON
        Document doc;
        doc.Parse(fileContent.c_str());

        if (doc.HasMember("highScores"))
        {
            const rapidjson::Value& scoreArray = doc["highScores"];
            for (SizeType i = 0; i < scoreArray.Size(); ++i)
            {
                const rapidjson::Value& scoreObject = scoreArray[i];
                std::string name         = scoreObject["name"].GetString();
                int score                = scoreObject["score"].GetInt();
                highScores.push_back(Score(name, score));
            }
        }
    }
    return highScores;
}
