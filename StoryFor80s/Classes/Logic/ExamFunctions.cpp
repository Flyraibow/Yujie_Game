//
//  ExamFunctions.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/10/19.
//

#include "ExamFunctions.hpp"
#include "ExamListData.hpp"

float getRatioFromAttributionRequirement(const map<string, int> &requirements)
{
  float ratio = 1.0;
  for (auto requirePair : requirements) {
    auto attribute = AttributeData::getAttributeDataById(requirePair.first);
    auto require = requirePair.second;
    if (attribute->getValue() < require) {
      ratio = ratio * attribute->getValue() / require;
    }
  }
  return ratio;
}

float getRatioFromProficiencyRequirement(const map<string, int> &requirements)
{
  float ratio = 1.0;
  for (auto requirePair : requirements) {
    auto proficiency = ProficiencyData::getProficiencyDataById(requirePair.first);
    auto require = requirePair.second;
    if (proficiency->getValue() < require) {
      ratio = ratio * proficiency->getValue() / require;
    }
  }
  return ratio;
}

int getScoreOfExam(ExamData* exam)
{
  int baseScore = exam->getBaseValue() * getRatioFromProficiencyRequirement(exam->getBaseProficiencyRequirementsMap());
  int midScore = exam->getMidValue() * getRatioFromProficiencyRequirement(exam->getMidProficiencyRequirementsMap());
  int highScore = exam->getHighValue() *
  getRatioFromProficiencyRequirement(exam->getHighProficiencyRequirementsMap())
  * getRatioFromAttributionRequirement(exam->getHighAttributeRequirementsMap());
  // 身体健康方面的折扣
  float ratio = 1.0;
  auto pressure = AttributeData::getAttributeDataById("pressure")->getValue();
  auto health = AttributeData::getAttributeDataById("health")->getValue();
  if (pressure >= 0.8 * health) {
    ratio = 0.7;
  } else if (pressure >= 0.5 * health) {
    ratio = 0.9;
  }
  
  CCLOG("%s = %d + %d + %d", exam->getName().c_str(), baseScore, midScore, highScore);
  CCLOG("%s = %d + %d + %d", exam->getName().c_str(), exam->getBaseValue(), exam->getMidScore(), exam->getHighValue());
  return ratio * (baseScore + midScore + highScore);
}

int getRankOfExam(int score, int population, int lowestScore, int midScore, int highestScore)
{
  if (score >= highestScore) {
    return 1;
  } else if (score < lowestScore) {
    return population;
  } else if (score >= midScore) {
    return population / 2 - 1.0 * (score - midScore) / (highestScore - midScore) * population / 2;
  } else {
    return 1.0 * (midScore- score) / (midScore - lowestScore) * population / 2 + population / 2;
  }
}
int getRankOfExam(ExamData* exam, int score, int population)
{
  return getRankOfExam(score, population, exam->getLowestScore(), exam->getMidScore(), exam->getHighestScore());
}

int getRankOfExamList(ExamListData* examList, int totalScore)
{
  int lowestScore = 0, midScore = 0, highestScore = 0;
  
  for (auto exam : examList->getClassesDataVector()) {
    lowestScore += exam->getLowestScore();
    midScore += exam->getMidScore();
    highestScore += exam->getHighestScore();
  }
  return getRankOfExam(totalScore, examList->getPopulation(), lowestScore, midScore, highestScore);
}

string game::startExam(ExamListData* examList)
{
  // TODO: will restructure the languages.
  string text = "你进行了" + examList->getName() + "。结果如下: \n";
  auto exams = examList->getClassesDataVector();
  int totalScore = 0;
  for (auto exam : exams) {
    auto score = getScoreOfExam(exam);
    totalScore += score;
    auto rank = getRankOfExam(exam, score, examList->getPopulation());
    text += exam->getName() + " 得分:" + to_string(score) + " 排名: " + to_string(rank) + "\n";
  }
  text += "总分:" + to_string(totalScore) + " 排名: " + to_string(getRankOfExamList(examList, totalScore)) + "\n";
  
  return text;
}
