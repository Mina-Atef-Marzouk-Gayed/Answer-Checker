#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for system("CLS")



//Mina Adel 2022/05319
//Mina Atef 2022/05542
//Youssef Hussein 2022/02811

using namespace std;

// Function declarations
int compareAnswers(char student[], char modelAnswer[], int num);
void showFireworks();



int main() {
    string userType;
    cout << "Are you a student or teacher? ";
    cin >> userType;

    if (userType == "teacher") {
        int numQuestions;
        cout << "Enter the number of questions you want to add: ";
        cin >> numQuestions;

        ofstream numFile("number_of_questions.txt");
        numFile << numQuestions;
        numFile.close();

        ofstream examFile("Quiz.txt");
        ofstream answerFile("model_answer.txt");

        for (int i = 1; i <= numQuestions; ++i) {
            string trash, questionText, options[4];

            cin.ignore(); // To skip newline after previous input
            cout << "\nEnter question " << i << ": ";
            getline(cin, questionText);
            examFile << "Q" << i << ": " << questionText << endl;

            cout << "Enter the 4 possible answers:\n";
            for (int j = 0; j < 4; ++j) {
                string option;
                getline(cin, option);
                options[j] = string(1, 'A' + j) + "- " + option;
                examFile << options[j] << endl;
            }

            system("CLS");

            cout << questionText << endl;
            for (const string& opt : options)
                cout << opt << endl;

            char correctAnswer;
            cout << "Which answer is correct? (a-d): ";
            cin >> correctAnswer;
            answerFile << correctAnswer << endl;
        }

        examFile.close();
        answerFile.close();
    }
    else if (userType == "student") {
        ifstream examFile("Quiz.txt");
        string line;

        while (getline(examFile, line)) {
            cout << line << endl;
        }
        examFile.close();

        int numQuestions;
        ifstream numFile("number_of_questions.txt");
        numFile >> numQuestions;
        numFile.close();

        char studentAnswers[100]{};
        cout << "\nBegin answering the quiz (enter one answer per question):\n";
        for (int i = 0; i < numQuestions; ++i) {
            cin >> studentAnswers[i];
        }

        char correctAnswers[100]{};
        ifstream answerFile("model_answer.txt");
        for (int i = 0; i < numQuestions; ++i) {
            answerFile >> correctAnswers[i];
        }
        answerFile.close();

        int score = compareAnswers(studentAnswers, correctAnswers, numQuestions);
        cout << "\nYour final grade is: " << score << " out of " << numQuestions << endl;

        if (score == numQuestions) {
            showFireworks();
        }
    }
    else {
        cout << "Invalid input.\n";
    }

    return 0;
}

// Compare student answers with model answers
int compareAnswers(char student[], char modelAnswer[], int num) {
    int grades = 0;
    for (int i = 0; i < num; ++i) {
        if (tolower(student[i]) == tolower(modelAnswer[i])) {
            grades++;
        }
    }
    return grades;
}

// Display simple text-based fireworks
void showFireworks() {
    cout << R"(
   *     *     *     *     *     *     *     *
      *        *   *     *     *     *     *
 *     *   🎆 Congratulations! 🎆   *     *
      *     You got full marks!     *
 *     *     *     *     *     *     *     *
    )" << endl;
}
