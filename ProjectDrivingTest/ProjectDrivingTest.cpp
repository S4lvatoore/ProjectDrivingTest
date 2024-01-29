#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>.
#include <conio.h>
#include <vector>
#include <sstream>
using namespace std;
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // ДЛЯ КУРСОРА
}
class EncryptionUtility {
public:
    static string caesarEncrypt(const string& data, int shift) {
        string encrypted = data;
        for (char& c : encrypted) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }
        return encrypted;
    }

    static string caesarDecrypt(const string& data, int shift) {
        return caesarEncrypt(data, 26 - shift);
    }
};

class FileManager {
public:
    static void saveToFile(const string& data, const string& filename) {
        ofstream file(filename, ios::app);
        file << data << endl;
    }
    static string readFromFile(const string& filename) {
        ifstream file(filename);
        string data, line;
        while (getline(file, line)) {
            data += line + "\n";
        }
        return data;
    }
};
class Admin {
    static const string adminDefaultUsername;
    static const string adminDefaultPassword;
public:
    static void initializeAdminAccount(const string& filename) {
        int shift = 5;
        string encryptedAdminUsername = EncryptionUtility::caesarEncrypt(adminDefaultUsername, shift);
        string encryptedAdminPassword = EncryptionUtility::caesarEncrypt(adminDefaultPassword, shift);
    };
    static bool adminLogin(const string& adminUsername, const string& adminPassword, const string& filename) {
        int shift = 5;
        string fileContent = FileManager::readFromFile(filename);
        string encryptedAdminUsername = EncryptionUtility::caesarEncrypt(adminUsername, shift);
        string encryptedAdminPassword = EncryptionUtility::caesarEncrypt(adminPassword, shift);
        string encryptedAdminData = encryptedAdminUsername + " " + encryptedAdminPassword;
        return fileContent.find(encryptedAdminData) != string::npos;
    }

    static void addUser(const string& username, const string& password, const string& phoneNumber, const string& fullName, const string& filename) {
        int shift = 5;
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);
        string encryptedPassword = EncryptionUtility::caesarEncrypt(password, shift);
        string encryptedPhoneNumber = EncryptionUtility::caesarEncrypt(phoneNumber, shift);
        string encryptedFullName = EncryptionUtility::caesarEncrypt(fullName, shift);
        string userData = encryptedUsername + " " + encryptedPassword + " " + encryptedPhoneNumber + " " + encryptedFullName;
        FileManager::saveToFile(userData, filename);
        cout << "User added successfully!\n";
    }

    static bool removeUser(const string& username, const string& phoneNumber, const string& password, const string& fullName, const string& filename) {
        int shift = 5;
        string fileContent = FileManager::readFromFile(filename);
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);
        string encryptedPassword = EncryptionUtility::caesarEncrypt(password, shift);
        string encryptedPhoneNumber = EncryptionUtility::caesarEncrypt(phoneNumber, shift);
        string encryptedFullName = EncryptionUtility::caesarEncrypt(fullName, shift);


        string toFind = encryptedUsername + " " + encryptedPassword + " " + encryptedPhoneNumber + " " + encryptedFullName + "\n";
        int foundPos = fileContent.find(toFind);

        if (foundPos != string::npos) {
            fileContent.erase(foundPos, toFind.length()); // ERASE ДЛЯ УДАЛЕНИЯ СТРОКИ
            ofstream file(filename, ios::out | ios::trunc);  // PEREZAPIS FAYLA
            file << fileContent;
            system("CLS");
            cout << "User removed successfully!\n";
            Sleep(2000);
            return true;
        }
        cout << "User not found. Deletion failed.\n";
        return false;
    }

    static void addQuestionToTest(const string& testFilename) {
        cout << "Adding new question to " << testFilename << endl;
        string questionText, option;
        vector<string> options;
        string answerInput;
        char correctAnswer;

        cin.ignore();
        cout << "Enter question text: ";
        getline(cin, questionText);

        for (int i = 0; i < 4; i++) {
            cout << "Enter option " << char('A' + i) << ": ";
            getline(cin, option);
            options.push_back(option);
        }

        cout << "Enter correct answer (A, B, C, or D): ";
        getline(cin, answerInput);

        if (!answerInput.empty() && (answerInput[0] == 'A' || answerInput[0] == 'a' || answerInput[0] == 'B' || answerInput[0] == 'b' || answerInput[0] == 'C' || answerInput[0] == 'c' || answerInput[0] == 'd' || answerInput[0] == 'D')) {
            correctAnswer = answerInput[0];
        }
        else {
            cout << "Invalid input. Please enter a valid answer (A, B, C, or D).\n";
            return;
        }

        string questionLine = questionText + '|';
        for (const auto& opt : options) {
            questionLine += opt + '|';
        }
        questionLine += correctAnswer;

        ofstream file(testFilename, ios::app);
        file << questionLine << endl;
        system("CLS");
        gotoxy(50, 7);
        cout << "Question added successfully!\n";

    }

};
const string Admin::adminDefaultUsername = "ADMIN";
const string Admin::adminDefaultPassword = "ADMIN";
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string fullName;

public:
    User(const string& username, const string& password, const string& phoneNumber, const string& fullName)
        : username(username), password(password), phoneNumber(phoneNumber), fullName(fullName) {}


    void registerUser(const string& filename) {
        int shift = 5;
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);
        string encryptedPassword = EncryptionUtility::caesarEncrypt(password, shift);
        string encryptedPhoneNumber = EncryptionUtility::caesarEncrypt(phoneNumber, shift);
        string encryptedFullName = EncryptionUtility::caesarEncrypt(fullName, shift);

        FileManager::saveToFile(encryptedUsername + " " + encryptedPassword + " " + encryptedPhoneNumber + " " + encryptedFullName, filename);
        cout << "Registration successful!\n";
    }

    bool loginUser(const string& filename) {
        int shift = 5;
        string fileContent = FileManager::readFromFile(filename);
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);
        string encryptedPassword = EncryptionUtility::caesarEncrypt(password, shift);

        string toFind = encryptedUsername + " " + encryptedPassword;
        return fileContent.find(toFind) != string::npos;
    }

    static bool userExists(const string& username, const string& filename, const string& phoneNumber, const string& fullName) {
        int shift = 5;
        string fileContent = FileManager::readFromFile(filename);
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);
        string encryptedPhoneNumber = EncryptionUtility::caesarEncrypt(phoneNumber, shift);
        string encryptedFullName = EncryptionUtility::caesarEncrypt(fullName, shift);

        string toFind = encryptedUsername + " " + encryptedPhoneNumber + " " + encryptedFullName;
        return fileContent.find(toFind) != string::npos;
    }
    static bool isUsernameTaken(const string& username, const string& filename) {
        int shift = 5;
        string fileContent = FileManager::readFromFile(filename);
        string encryptedUsername = EncryptionUtility::caesarEncrypt(username, shift);

        int foundPos = fileContent.find(encryptedUsername);
        return (foundPos != string::npos);
    }
};

class Question {
public:
    string text;
    vector<string> options;
    char correctAnswer;

    Question(const string& text, const vector<string>& options, char correctAnswer)
        : text(text), options(options), correctAnswer(correctAnswer) {}
};
static int countOfPassedExams = 0;
class Test {
private:
    string filename;
    vector<Question> questions;

    void loadQuestions() {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string questionText, optionsPart, option;
            vector<string> options;
            char correctAnswer = ' ';

            int delimiterPos = line.find('|');
            if (delimiterPos != string::npos) {
                questionText = line.substr(0, delimiterPos);
                optionsPart = line.substr(delimiterPos + 1);

                if (!optionsPart.empty()) {
                    correctAnswer = optionsPart.back();
                    optionsPart.pop_back();
                }

                stringstream ssOptions(optionsPart);
                while (getline(ssOptions, option, '|')) {
                    options.push_back(option);
                }

                questions.emplace_back(questionText, options, correctAnswer);
            }
        }
    }


public:
    Test(const string& filename) : filename(filename) {
        loadQuestions();
    }
    void runTest(const string& username) {
        int score = 0;
        for (const auto& q : questions) {
            cout << q.text << endl;
            char optionChar = 'A';
            for (const auto& option : q.options) {
                cout << optionChar++ << ") " << option << endl;
            }
            cout << "Your answer: ";
            char answer;
            cin >> answer;
            if (toupper(answer) == q.correctAnswer) {
                score++;
            }
        }
        saveTestResult(username, score);
        if (score >= 9) {
            system("CLS");
            cout << "Your score: " << score << " out of " << questions.size() << endl << endl;
            cout << "You passed this part of exam" << endl << endl;
            countOfPassedExams++;
            cout << "Count of passed exams = " << countOfPassedExams << endl << endl;
            Sleep(4000);
            system("CLS");
        }
        else {
            system("CLS");
            cout << "Your score: " << score << " out of " << questions.size() << endl << endl;
            cout << "You missed this part of exam" << endl;
            cout << "Count of passed exams = " << countOfPassedExams << endl;
            Sleep(4000);
            system("CLS");
        }

    }

    void saveTestResult(const string& username, int score) {
        string result = username + " scored " + to_string(score) + " on " + filename;
        FileManager::saveToFile(result, "test_results.txt");
    }

    static void viewAllTestResults() {
        cout << "All Test Results:\n";
        cout << FileManager::readFromFile("test_results.txt");
    }
};

void loginOrRegisterUser(const string& usersFilename) {
    cout << "1. Login\n2. Register\nChoose option (1-2): ";
    int choice;
    cin >> choice;

    string username, password, fullName, phoneNumber;
    gotoxy(50, 7);
    cout << "Enter username: "; cin >> username;
    gotoxy(50, 8);
    cout << "Enter Full name: "; cin >> fullName;
    gotoxy(50, 9);
    cout << "Enter Phone Number: "; cin >> phoneNumber;
    gotoxy(50, 10);

    if (choice == 1) {
        cout << "Enter password: "; cin >> password;
        gotoxy(50, 11);
        User user(username, password, phoneNumber, fullName);
        if (user.loginUser(usersFilename)) {
            system("CLS");
            gotoxy(50, 7);
            cout << "Login successful!\n";
            cout << "1. Take a Test\n2. View Test Results\nChoose option (1-2): ";
            cin >> choice;
            if (choice == 1) {
                Test theoryTest("theory_test.txt");
                Test roadSignsTest("road_signs_test.txt");
                Test practicalTest("practical_test.txt");
                theoryTest.runTest(username);
                roadSignsTest.runTest(username);
                practicalTest.runTest(username);
            }
            else if (choice == 2) {
                Test::viewAllTestResults();
            }
            else {
                gotoxy(50, 7);
                cout << "Invalid option.\n";
            }
        }
        else {
            system("CLS");
            gotoxy(50, 7);

            cout << "Invalid username or password. Login failed.\n";
            exit(0);
        }
    }
    else if (choice == 2) {
        if (choice == 2) {
            gotoxy(50, 11);
            cout << "Enter password: "; cin >> password;

            if (!User::isUsernameTaken(username, usersFilename)) {
                User user(username, password, phoneNumber, fullName);
                user.registerUser(usersFilename);
            }
            else {
                system("CLS");
                gotoxy(50, 7);

                cout << "Username is already taken. Please choose another one.\n";
                Sleep(2000);
                system("CLS");

            }
        }
    }
    else {
        gotoxy(50, 7);
        cout << "Invalid option.\n";
        exit(0);
    }
}
int main() {
    const string userFilename = "users.txt";
    const string adminFilename = "admin.txt";

    Admin::initializeAdminAccount(adminFilename);

    gotoxy(50, 7);
    cout << "Welcome to the Car Driving Test" << endl;
    Sleep(2000);
    system("cls");

    while (true) {
        gotoxy(50, 7);
        cout << "Are you an admin or a user?" << endl;
        gotoxy(50, 8);
        cout << "1) Admin" << endl;
        gotoxy(50, 9);
        cout << "2) User" << endl;
        gotoxy(50, 10);
        cout << "3) Exit" << endl;
        gotoxy(50, 11);

        char choice = _getch();
        system("CLS");
        if (choice == '1') {
            string adminUsername, adminPassword;
            gotoxy(50, 7);
            cout << "Enter admin username: ";
            cin >> adminUsername;
            gotoxy(50, 8);
            cout << "Enter admin password: ";
            cin >> adminPassword;
            system("CLS");
            if (Admin::adminLogin(adminUsername, adminPassword, adminFilename)) {
                gotoxy(50, 7);
                cout << "Admin login successful!\n";
                Sleep(2000);
                system("CLS");
                while (true) {
                    gotoxy(50, 7);
                    cout << "Admin Menu:";
                    gotoxy(50, 8);
                    cout << "1. Add User";
                    gotoxy(50, 9);
                    cout << "2. Remove User\n";
                    gotoxy(50, 10);
                    cout << "3. Add Test to Category";
                    gotoxy(50, 11);
                    cout << "4. View All Test Results";
                    gotoxy(50, 12);
                    cout << "5. Exit Admin Mode";
                    gotoxy(50, 13);
                    cout << "Choose option (1-5): ";
                    gotoxy(50, 14);

                    char adminChoice = _getch();

                    if (adminChoice == '1') {
                        system("CLS");
                        string username, password, fullName, phoneNumber;
                        cout << "Enter username: "; cin >> username;
                        cout << "Enter surname: "; cin >> fullName;
                        cout << "Enter Phone Number: "; cin >> phoneNumber;
                        cout << "Enter password: "; cin >> password;

                        Admin::addUser(username, password, phoneNumber, fullName, userFilename);
                    }
                    else if (adminChoice == '2') {
                        system("CLS");
                        string username, phoneNumber, fullName, password;
                        cout << "Enter username: "; cin >> username;
                        cout << "Enter Full name: "; cin >> fullName;
                        cout << "Enter Phone Number: "; cin >> phoneNumber;
                        cout << "Enter password: "; cin >> password;
                        Admin::removeUser(username, phoneNumber, password, fullName, userFilename);
                    }
                    else if (adminChoice == '3') {
                        system("CLS");
                        gotoxy(50, 7);
                        cout << "Enter test filename to add: ";
                        string testFilename;
                        cin >> testFilename;
                        Admin::addQuestionToTest(testFilename);
                    }
                    else if (adminChoice == '4') {
                        Test::viewAllTestResults();
                    }
                    else if (adminChoice == '5') {
                        break;
                    }
                    else {
                        cout << "Invalid option.\n";
                    }
                }
            }
            else {
                cout << "Invalid admin credentials. Login failed.\n";
            }
        }
        else if (choice == '2') {
            loginOrRegisterUser(userFilename);
        }
        else if (choice == '3') {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid option selected." << endl;
        }
    }

}
