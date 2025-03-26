#include "User.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
// Default constructor
User::User() {
    // Initialize user attributes
    userID = "";
    name = "";
    username = "";
    password = "";
    age = 0;
    gender = "";
    role = "";
    height = 0.0;
    weight = 0.0;
}

// Parameterized constructor with all attributes
User::User(std::string id, std::string uname, int uage, std::string ugender, std::string urole,
    std::string uusername, std::string upassword, double uheight, double uweight) {
    // Set user attributes
    userID = id;
    name = uname;
    age = uage;
    gender = ugender;
    role = urole;
    username = uusername;
    password = upassword;
    height = uheight;
    weight = uweight;
}

// Parameterized constructor without height and weight
User::User(std::string id, std::string uname, int uage, std::string ugender, std::string urole,
    std::string uusername, std::string upassword) {
    userID = id;
    name = uname;
    age = uage;
    gender = ugender;
    role = urole;
    username = uusername;
    password = upassword;
    // Default values for height and weight
    height = 0.0;
    weight = 0.0;
}

void User::newProfile() {
    cin.ignore();

    cout << "Enter Name: ";
    getline(std::cin, name);

    cout << "Enter Username: ";
    cin >> username;

    // Get password
    cout << "Enter Password: ";
    cin >> password;

    // Get age
    cout << "Enter Age: ";
    cin >> age;

    // Get gender
    cout << "Enter Gender (Male/Female/Other): ";
    cin >> gender;

    // Get height
    cout << "Enter Height (in cm): ";
    cin >> height;

    // Get weight
    cout << "Enter Weight (in kg): ";
    cin >> weight;

    // Get role
    cout << "Enter Role (Admin/Member/Trainer): ";
    cin >> role;

    cout << "Proifle created successfully\n";

    //File storage
    // Check if file exists to add column header only once
    ifstream checkFile("UserData.csv");
    bool fileExists = checkFile.good();
    checkFile.close();

    //Open file in append mode
    ofstream outFile("UserData.csv", std::ios::app);

    // Check if file opened successfully
    if (!outFile) {
        std::cout << "Error: Unable to open file!\n";
        return;
    }

    // If file is new, add headers
    if (!fileExists) {
        outFile << "Username,Password,Name,Age,Gender,Height,Weight,Role\n";
    }

    // Store user data
    outFile << username << ","
        << password << ","
        << name << ","
        << age << ","
        << gender << ","
        << height << ","
        << weight << ","
        << role << "\n";

    // Close the file
    outFile.close();

    // Display success message
    cout << "Data successfully saved in UserData.csv!\n";
}
void User::viewProfile() {
    // Display user profile information
    cout << "User ID: " << userID
        << "\nName: " << name
        << "\nUsername: " << username
        << "\nAge: " << age
        << "\nGender: " << gender
        << "\nHeight: " << height << " cm"
        << "\nWeight: " << weight << " kg"
        << "\nRole: " << role << std::endl;
}
// Method to authenticate user
bool User::authenticate(std::string uname, std::string pass) {
    // Check if username and password match
    return (username == uname && password == pass);
}

// Getters for user attributes
std::string User::getUsername() {
    return username;
}

std::string User::getRole() {
    return role;
}

void User::addProgressRecord(const ProgressRecord& record) {
    progressHistory.push_back(record);

    // Save to file
    std::ofstream outFile("ProgressTracking.csv", std::ios::app);
    if (!outFile) {
        std::cerr << "Error: Could not open ProgressTracking.csv\n";
        return;
    }

    // Check if file is empty to add headers
    outFile.seekp(0, std::ios::end);
    if (outFile.tellp() == 0) {
        outFile << "Username,Date,Weight,BMI,Achievements\n";
    }

    // Write progress record
    outFile << username << ","
        << record.date << ","
        << record.weight << ","
        << record.bmi << ","
        << record.achievements << "\n";

    outFile.close();
}

std::vector<ProgressRecord> User::getProgressHistory() {
    // If progress history is empty, try to load from file
    if (progressHistory.empty()) {
        std::ifstream inFile("ProgressTracking.csv");
        std::string line;
        bool isHeader = true;

        while (getline(inFile, line)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }

            std::stringstream ss(line);
            std::string fileUsername, date, weightStr, bmiStr, achievements;

            getline(ss, fileUsername, ',');

            // Only load progress for this specific user
            if (fileUsername == username) {
                ProgressRecord record;

                getline(ss, record.date, ',');
                getline(ss, weightStr, ',');
                getline(ss, bmiStr, ',');
                getline(ss, record.achievements);

                record.weight = std::stod(weightStr);
                record.bmi = std::stod(bmiStr);

                progressHistory.push_back(record);
            }
        }
    }

    return progressHistory;
}

double User::calculateAverageBMI() {
    std::vector<ProgressRecord> history = getProgressHistory();

    if (history.empty()) return 0.0;

    double totalBMI = 0.0;
    for (const auto& record : history) {
        totalBMI += record.bmi;
    }

    return totalBMI / history.size();
}