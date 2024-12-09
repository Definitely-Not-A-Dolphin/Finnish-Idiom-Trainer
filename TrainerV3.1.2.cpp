#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Header
void pointerMover(std::ifstream &file, int k);

bool vectorChecker(std::vector<std::string> searchedVector,
                   std::string searchedWord) {
  bool result = false;

  for (std::string comparer : searchedVector) {
    if (comparer == searchedWord) {
      result = true;
    }
  };

  return result;
}

// Get functions
void getEngPractise(std::ifstream &file, int line);
void getFinPractise(std::ifstream &file, int line, int finCase);
std::string getEng(std::ifstream &file, int line);
std::string getFin(std::ifstream &file, int line, int finCase);
std::string getElement(std::ifstream &file, int row, int column);

// Practices
void standardPractise(std::ifstream &file, bool random, std::string language,
                      int finCase);
void verbsPractise();

// Questions
void wordTypeQuestion();
void languageQuestion();
void caseQuestion();
void wordAmountQuestion();
void randomQuestion();

struct {
  std::string wordTypeString;
  int wordTypeInt;
  std::string language;
  int finCase;
  int wordAmount;
  bool random;
} Answer;

struct {
  int correct;
  int incorrect;
} Score;

struct {
  std::vector<std::string> no = {"No",  "no",  "Nah", "nah",
                                 "Nei", "nei", "Nee", "nee"};
  std::vector<std::string> yes = {"Yes", "yes", "Yeah", "yeah", "Yea",
                                  "yea", "Ye",  "ye",   "Ja",   "ja"};
  std::vector<std::string> language = {"Finnish", "finnish", "English",
                                       "english"};
  std::vector<std::string> cases = {"Nominatiivi", "Genitiivi",   "Akkusatiivi",
                                    "Partitiivi",  "nominatiivi", "genitiivi",
                                    "akkusatiivi", "partitiivi"};
  std::vector<std::string> wordType = {"adjectivesFile.csv", "nounsFile.csv",
                                       "numbersFile.csv",    "pronounsFile.csv",
                                       "verbsFile.csv",      "otherFile.csv"};
} Vector;

int main() {

  std::cout << "Yep, this runs!" << std::endl;

  // Questions
  wordTypeQuestion();
  languageQuestion();
  if ((Answer.language == "Finnish" or Answer.language == "finnish") and
      Answer.wordTypeInt != 5) {
    caseQuestion();
  }
  wordAmountQuestion();
  randomQuestion();

  std::ifstream readFile(Answer.wordTypeString, std::ios::in);

  if (Answer.wordTypeInt != 5) {
    standardPractise(readFile, Answer.random, Answer.language, Answer.finCase);
  } else if (Answer.wordTypeInt == 5) {
    verbsPractise();
  };

  readFile.close();

  return 0;
}

void standardPractise(std::ifstream &file, bool random, std::string language,
                      int finCase) {

  int counter = 0;
  int maxLine = 4;

  if (random) {

    while (true) {

      // Get random sequence n
      std::vector<int> randomSequence;

      if (language == "English" or language == "english") {
        getEngPractise(file, randomSequence.at(counter));
      } else {
        getFinPractise(file, randomSequence.at(counter), finCase);
      }

      counter += 1;

      if (counter == Answer.wordAmount) {
        break;
      }
    }
  } else {
    int line = 2;

    while (true) {
      if (language == "English" or language == "english") {
        getEngPractise(file, line);
      } else {
        getFinPractise(file, line, finCase);
      };

      counter += 1, line += 1;

      if (counter == Answer.wordAmount) {
        break;
      };

      if (line > maxLine) {
        file.seekg(0, std::ifstream::beg);
        pointerMover(file, 2);
      }
    }
  }
  file.close();
}

// Questions
void wordTypeQuestion() {
  while (true) {
    std::cout << "What type of word would you like to practise? " << std::endl
              << "  Adjectives (type 1), " << std::endl
              << "  Nouns (type 2), " << std::endl
              << "  Numbers (type 3), " << std::endl
              << "  Pronouns (type 4), " << std::endl
              << "  Verbs (type 5), " << std::endl
              << "  Other (type 6), " << std::endl;
    std::cin >> Answer.wordTypeInt;

    if (1 <= Answer.wordTypeInt <= 6) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };

  if (Answer.wordTypeInt != 5) {
    Answer.wordTypeString = Vector.wordType.at(Answer.wordTypeInt - 1);
  } else if (Answer.wordTypeInt == 5) {
    Answer.wordTypeString = Vector.wordType.at(4);
  }
}
void languageQuestion() {
  while (true) {
    std::cout << std::endl << "What language would you like to practise? ";
    std::cin >> Answer.language;

    if (vectorChecker(Vector.language, Answer.language)) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };
}
void caseQuestion() {
  while (true) {
    std::cout << std::endl
              << "What case would you like to practise? " << std::endl
              << "  Nominatiivi (type 1), " << std::endl
              << "  Genitiivi (type 2), " << std::endl
              << "  Partitiivi (type 3), " << std::endl
              << "  Akkusatiivi (type 4), " << std::endl;
    std::cin >> Answer.finCase;

    if (1 <= Answer.finCase <= 4) {
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  }
}
void wordAmountQuestion() {
  std::cout << std::endl << "How many words do you want to practise? ";
  std::cin >> Answer.wordAmount;
}
void randomQuestion() {
  while (true) {
    std::string ans;
    std::cout << std::endl << "Would you like to randomise the word order? ";
    std::cin >> ans;

    if (vectorChecker(Vector.yes, ans)) {
      Answer.random = true;
      break;
    } else if (vectorChecker(Vector.no, ans)) {
      Answer.random = false;
      break;
    } else {
      std::cout << std::endl
                << "Sorry, I could not understand that. Please re-enter your "
                   "answer."
                << std::endl;
    }
  };
}

void getFinPractise(std::ifstream &file, int line, int finCase) {
  std::string wordEng = getEng(file, line);

  std::string wordFin = getFin(file, line, finCase);

  std::string wordFinInput;
  std::cout << std::endl << "What is the Finnish word for " << wordEng << "? ";
  std::cin >> wordFinInput;
  std::cout << std::endl;

  if (wordFinInput == wordFin) {
    std::cout << "Yes! :)" << std::endl;
  } else {
    std::cout << "No :( The correct word was " << wordFin << std::endl;
  };
}

void getEngPractise(std::ifstream &file, int line) {
  std::string wordEng = getEng(file, line);

  std::string wordFin = getFin(file, line, 1);

  std::string wordEngInput;
  std::cout << std::endl << "What is the Finnish word for " << wordFin << "? ";
  std::cin >> wordEngInput;
  std::cout << std::endl;

  if (wordEngInput == wordEng) {
    std::cout << "Yes! :)" << std::endl;
  } else {
    std::cout << "No :( The correct word was " << wordEng << std::endl;
  };
}

std::string getEng(std::ifstream &file, int line) {

  std::string wordFin = getElement(file, line, 1);

  return wordFin;
}

std::string getFin(std::ifstream &file, int line, int finCase) {

  std::string wordFin = getElement(file, line, finCase + 1);

  return wordFin;
}

std::string getElement(std::ifstream &file, int row, int column) {
  pointerMover(file, row);

  std::string output;
  getline(file, output);

  std::string tmp; // A string to store the word on each iteration.
  std::stringstream str_strm(output);
  std::vector<std::string> wordsVector; // Create vector to hold our words
  while (str_strm >> tmp) {
    tmp.pop_back();
    wordsVector.push_back(tmp);
  }

  return wordsVector.at(column - 1);
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