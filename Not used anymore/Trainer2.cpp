#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

void pointerMover(std::ifstream &file, int k);
bool listChecker(std::list<std::string> searchedList, std::string searchedWord);

void practiseEnglish();
void practiseFinnish(int finCase);

void getEngFin(int k, int finCase);
void getFinEng(int k);

std::string getElement(int row, int column);
std::string gradeMessage(double grade);
std::string getEng(int line);
std::string getFin(int line, int finCase);

int maxLine = 50;

// Questions
std::string EngOrFin;
double wordsTrained;
int wordType;

struct {
  bool infinite;
  bool random;
} Practise;

struct {
  std::list<std::string> no = {"No",  "no",  "Nah", "nah",
                               "Nei", "nei", "Nee", "nee"};
  std::list<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::list<std::string> language = {"Finnish", "finnish", "English",
                                     "english"};
  std::list<std::string> cases = {
      "Nominatiivi", "Genitiivi", "Akkusatiivi", "Partitiivi",
      "nominatiivi", "genitiivi", "akkusatiivi", "partitiivi"};
} List;

struct {
  std::vector<std::string> wordType = {
      "adverbsEngFin.csv",  "nounsEngFin.csv", "numbersEngFin.csv",
      "pronounsEngFin.csv", "verbsEngFin.csv", "otherEngFin.csv",
  };
} Vector;

struct {
  double correct;
  int incorrect;
} Score;

std::ifstream readEngFin(Vector.wordType.at(wordType - 1)); 

int main() {

  int finCase;

  while (true) {

    // Word Type
    while (true) {
      std::cout << "What type of word would you like to practise? " << std::endl
                << "  Adverbs (type 1), " << std::endl
                << "  Nouns (type 2), " << std::endl
                << "  Numbers (type 3), " << std::endl
                << "  Pronouns (type 4), " << std::endl
                << "  Verbs (type 5), " << std::endl
                << "  Other (type 6), " << std::endl;
      std::cin >> wordType;

      if (1 <= wordType <= 6) {
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    };

    // English or Finnish
    while (true) {
      std::cout
          << "What language would you like to practise? ";
      std::cin >> EngOrFin;

      if (listChecker(List.language, EngOrFin)) {
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    };

    // What case?
    if (EngOrFin == "Finnish" or EngOrFin == "finnish") {
      while (true) {
        std::cout << "What case would you like to practise? " << std::endl
                  << "  Nominatiivi (type 1), " << std::endl
                  << "  Genitiivi (type 2), " << std::endl
                  << "  Partitiivi (type 3), " << std::endl
                  << "  Akkusatiivi (type 4), " << std::endl;
        std::cin >> finCase;

        if (1 <= finCase <= 4) {
          break;
        } else {
          std::cout
              << std::endl
              << "Sorry, I could not understand that. Please re-enter your "
                 "answer."
              << std::endl;
        }
      }
    }

    // How many words?
    std::cout << "How many words do you want to practise (the current list "
                 "contains "
              << maxLine << " words)? ";
    std::cin >> wordsTrained;

    // Random order?
    while (true) {
      std::string answerRandom;
      std::cout << "Do you want to randomise the words? ";
      std::cin >> answerRandom;

      if (listChecker(List.yes, answerRandom)) {
        Practise.random = true;
        break;
      } else if (listChecker(List.no, answerRandom)) {
        Practise.random = false;
        break;
      } else {
        std::cout << std::endl
                  << "Sorry, I could not understand that. Please re-enter your "
                     "answer."
                  << std::endl;
      }
    }

    if (EngOrFin == "Finnish" or EngOrFin == "finnish") {
      practiseFinnish(finCase);
    } else {
      practiseEnglish();
    };
    
    std::cout << Score.correct << std::endl << wordsTrained << std::endl;
    double grade = (Score.correct / wordsTrained) * 9 + 1;
    std::cout << grade << std::endl;
    std::cout << gradeMessage(grade) << std::endl;

    Score.correct, Score.incorrect = 0;

    std::string repeat;
    std::cout << std::endl << "Do you want to try again? " << std::endl;
    std::cin >> repeat;

    readEngFin.close();

    if (listChecker(List.no, repeat)) {
      break;
    }
  }

  return 0;
}

void practiseEnglish() {

  int counter = 0;

  int i = 2;

  if (Practise.random) {
    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      getFinEng(randomSequence.at(0));

      counter = counter + 1;

      if (i > maxLine) {
        if (Practise.infinite = false) {
          break;
        } else {
          i = 1;
        }
      }
    }
  } else {
    while (true) {

      getFinEng(i);

      counter = counter + 1;

      i = i + 1;

      if (counter == wordsTrained) {
        break;
      };

      if (i > maxLine) {
        readEngFin.seekg(0, std::ifstream::beg);
        pointerMover(readEngFin, 2);
      }
    }
  }
}

void practiseFinnish(int finCase) {

  int counter = 0;

  int i = 2;

  if (Practise.random) {
    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      getEngFin(randomSequence.at(0), finCase);

      counter = counter + 1;

      if (i > maxLine) {
        if (Practise.infinite = false) {
          break;
        } else {
          i = 1;
        }
      }
    }
  } else {
    while (true) {

      getEngFin(i, finCase);

      counter = counter + 1;

      i = i + 1;

      if (counter == wordsTrained) {
        break;
      };

      if (i > maxLine) {
        readEngFin.seekg(0, std::ifstream::beg);
        pointerMover(readEngFin, 2);
      }
    }
  }
}

void pointerMover(std::ifstream &file, int k) {

  // Special thanks to Elses/Menium for writing this part!

  file.clear();
  file.seekg(0, std::ios::beg);

  std::string line;
  for (int currentLine = 1; currentLine < k; currentLine++) {
    if (!std::getline(file, line)) {
      std::cerr << "Error: Line " << k << " does not exist!" << std::endl;
      return;
    }
  }
}

bool listChecker(std::list<std::string> searchedList,
                 std::string searchedWord) {
  bool result = false;

  for (std::string comparer : searchedList) {
    if (comparer == searchedWord) {
      result = true;
    }
  };

  return result;
}

void getEngFin(int k, int finCase) {
  std::string wordEng = getEng(k);

  std::string wordFin = getFin(k, finCase);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :( The correct word was " << wordFin << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your current score: (" << Score.correct << " / " << Score.incorrect
            << ")" << std::endl;
}

void getFinEng(int k) {
  std::string wordEng = getEng(k);

  std::string wordFin = getFin(k, 2);

  std::string wordEngInput;
  std::cout << std::endl
            << "What is the " << EngOrFin << " word for " << wordFin << "? ";
  std::cin >> wordEngInput;
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
    Score.correct += 1;
  } else {
    std::cout << "No :(" << std::endl;
    Score.incorrect += 1;
  };
  std::cout << "Your current score: (" << Score.correct << " / " << Score.incorrect
            << ")" << std::endl;
}

std::string gradeMessage(double grade) {
  std::cout << std::endl << "Your grade is: " << grade << "/10" << std::endl;

  std::vector<std::string> gradeMessage = {
      "This is too hard for you. Have you considered Swedish?",
      "Were you even trying?",
      "I would consider that not very good.",
      "It's okay, could be better.",
      "Solid grade!",
      "Wow, good job!"};

  return gradeMessage.at((int)floor(grade / 2));
}

std::string getEng(int line) {

  std::string wordEng = getElement(line, 1);

  return wordEng;
}

std::string getFin(int line, int finCase) {

  std::string wordFin = getElement(line, finCase + 1);

  return wordFin;
}

std::string getElement(int row, int column) {
  pointerMover(readEngFin, row);

  std::string output;
  std::getline(readEngFin, output);

  std::string tmp; // A string to store the word on each iteration.
  std::stringstream str_strm(output);
  std::vector<std::string> wordsVector; // Create vector to hold our words
  while (str_strm >> tmp) {
    tmp.pop_back();
    wordsVector.push_back(tmp);
  }

  return wordsVector.at(column - 1);
}