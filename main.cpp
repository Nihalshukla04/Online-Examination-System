#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// MODULE 1: Question Management
class Question {
public:
    string question;
    string options[4];
    char correctAnswer;

    void display(int n) {
        cout << "\nQ" << n << ". " << question << endl;

        for (int i = 0; i < 4; i++) {
            cout << char('A' + i) << ". "
                 << options[i] << endl;
        }
    }
};

// Student Class
class Student {
public:
    string name;
    string id;
    int marks = 0;
    vector<char> answers;
};

// Main Class
class OnlineExaminationSystem {
private:
    vector<Question> questions;

public:

    // Add Questions
    void addQuestion() {
        Question q;

        cout << "Enter question: ";
        getline(cin, q.question);

        for (int i = 0; i < 4; i++) {
            cout << "Enter option " << char('A' + i) << ": ";
            getline(cin, q.options[i]);
        }

        cout << "Enter correct answer (A/B/C/D): ";
        cin >> q.correctAnswer;
        cin.ignore();

        q.correctAnswer = toupper(q.correctAnswer);

        questions.push_back(q);

        cout << "\nQuestion added successfully!\n";
    }

    // View Questions
    void viewQuestions() {
        if (questions.empty()) {
            cout << "\nNo questions available.\n";
            return;
        }

        for (int i = 0; i < questions.size(); i++) {
            questions[i].display(i + 1);
        }
    }

    // Delete Question
    void deleteQuestion() {
        viewQuestions();

        if (questions.empty())
            return;

        int n;
        cout << "\nEnter question number to delete: ";
        cin >> n;
        cin.ignore();

        if (n >= 1 && n <= questions.size()) {
            questions.erase(questions.begin() + n - 1);
            cout << "Question deleted successfully!\n";
        }
        else {
            cout << "Invalid question number!\n";
        }
    }

    // MODULE 1: Admin Module
    void adminModule() {
        string username, password;

        cout << "\nAdmin Username: ";
        getline(cin, username);

        cout << "Admin Password: ";
        getline(cin, password);

        if (username != "admin" || password != "1234") {
            cout << "Invalid login!\n";
            return;
        }

        int choice;

        do {
            cout << "\n--- QUESTION MANAGEMENT ---\n";
            cout << "1. Add Question\n";
            cout << "2. View Questions\n";
            cout << "3. Delete Question\n";
            cout << "4. Back\n";

            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    addQuestion();
                    break;

                case 2:
                    viewQuestions();
                    break;

                case 3:
                    deleteQuestion();
                    break;

                case 4:
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 4);
    }

    // MODULE 2: Conduct Examination
    void conductExam() {
        if (questions.empty()) {
            cout << "\nNo questions available. Admin must add questions first.\n";
            return;
        }

        Student s;

        cout << "\nEnter student name: ";
        getline(cin, s.name);

        cout << "Enter student ID: ";
        getline(cin, s.id);

        for (int i = 0; i < questions.size(); i++) {
            questions[i].display(i + 1);

            char answer;

            cout << "Enter your answer: ";
            cin >> answer;

            answer = toupper(answer);
            s.answers.push_back(answer);
        }

        cin.ignore();

        // MODULE 3: Evaluate Answers
        for (int i = 0; i < questions.size(); i++) {
            if (s.answers[i] == questions[i].correctAnswer) {
                s.marks++;
            }
        }

        float percentage =
            (s.marks * 100.0) / questions.size();

        // MODULE 4: Display Scorecard
        cout << "\n========== SCORECARD ==========\n";

        cout << "Student Name: " << s.name << endl;
        cout << "Student ID: " << s.id << endl;

        cout << "Marks: " << s.marks
             << "/" << questions.size() << endl;

        cout << fixed << setprecision(2);

        cout << "Percentage: "
             << percentage << "%" << endl;

        if (percentage >= 40)
            cout << "Result: PASS\n";
        else
            cout << "Result: FAIL\n";

        // Save result in file
        ofstream file("results.txt", ios::app);

        file << s.name << " "
             << s.id << " "
             << s.marks << "/"
             << questions.size() << " "
             << percentage << "%\n";

        file.close();
    }

    // View Saved Results
    void displayResults() {
        ifstream file("results.txt");

        if (!file) {
            cout << "\nNo results available.\n";
            return;
        }

        string line;

        cout << "\n========== EXAMINATION RESULTS ==========\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    // Main Menu
    void run() {
        int choice;

        do {
            cout << "\n================================\n";
            cout << "   ONLINE EXAMINATION SYSTEM\n";
            cout << "================================\n";

            cout << "1. Admin - Manage Questions\n";
            cout << "2. Student - Attend Exam\n";
            cout << "3. Display Results\n";
            cout << "4. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    adminModule();
                    break;

                case 2:
                    conductExam();
                    break;

                case 3:
                    displayResults();
                    break;

                case 4:
                    cout << "Thank you!\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 4);
    }
};

// Main Function
int main() {

    OnlineExaminationSystem system;

    system.run();

    return 0;
}