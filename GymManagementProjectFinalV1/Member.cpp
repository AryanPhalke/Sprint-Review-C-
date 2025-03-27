#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>


using namespace std;

// Default constructor 
Member::Member() : User() {
    membershipType = "";
    membershipDuration = 0;
}

// Parameterized constructor
Member::Member(std::string id, std::string name, int age, std::string gender,
    std::string username, std::string password, double height, double weight,
    std::string membershipType, int membershipDuration)
    : User(id, name, age, gender, "Member", username, password, height, weight) {
    // Set member-specific attributes
    this->membershipType = membershipType;
    this->membershipDuration = membershipDuration;
}

// Method to view member's workout plan
void Member::viewWorkoutPlan(const std::string& username) {
    ifstream file("WorkoutPlans.csv");

    // Check if file opened
    if (!file) {
        cout << "Error in opening the file\n";
        return;
    }

    // Variables for reading file
    std::string line;
    bool isHeader = true;
    bool found = false;

    // Read file line by line
    while (getline(file, line)) {
        // Skip header row
        if (isHeader) {
            isHeader = false;
            continue;
        }

        // String stream to parse CSV line
        std::stringstream ss(line);
        std::string fileUsername, planDetails;

        // Parse username and plan details
        getline(ss, fileUsername, ',');

        // If username matches, display workout plan
        if (fileUsername == username) {
            getline(ss, planDetails);
            cout << "\n====== Your Workout Plan ======\n";
            cout << planDetails << std::endl;
            cout << "==============================\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "No workout plan found for your account\n";
    }
}

void Member::updateProfile(const std::string& username) {
    // Open user data file.
    std::ifstream infile("UserData.csv");

    // Check if file opened the successfully
    if (!infile) {
        cout << "Error: Could not Open UserData.csv\n";
        return;
    }

    // Temporary file to store updated data
    ofstream outFile("TempUserData.csv");

    // Variable for reading file
    string line;
    bool isHeader = true;
    bool updated = false;

    // Read file line by line
    while (getline(infile, line)) {
        // Handle header row
        if (isHeader) {
            outFile << line << "\n";
            isHeader = false;
            continue;
        }

        // String stream to parse CSV line
        std::stringstream ss(line);
        std::string fileUsername, password, name, age, gender, height, weight, role;

        // Parse user data
        getline(ss, fileUsername, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, height, ',');
        getline(ss, weight, ',');
        getline(ss, role, ',');

        // If username matches, update profile
        if (fileUsername == username) {
            // Get new values
            string newName;
            double newHeight, newWeight;
            string newPassword;

            // Menu for updating profile
            int choice;
            cout << "What would you like to Update?\n";
            cout << "1. Name \n2. Password\n3. Height\n4. Weight\n5. All\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter new name: ";
                cin >> newName;
                name = newName;
                break;
            case 2:
                cout << "Enter new password: ";
                cin >> newPassword;
                password = newPassword;
                break;
            case 3:
                cout << "Enter new height (in cm): ";
                cin >> newHeight;
                height = std::to_string(newHeight);
                break;
            case 4:
                cout << "Enter new weight (in kg): ";
                cin >> newWeight;
                weight = std::to_string(newWeight);
                break;
            case 5:
                cout << "Enter new password: ";
                cin >> newPassword;
                password = newPassword;

                cout << "Enter new height (in cm): ";
                cin >> newHeight;
                height = std::to_string(newHeight);

                cout << "Enter new weight (in kg): ";
                cin >> newWeight;
                weight = std::to_string(newWeight);
                break;
            default:
                cout << "Invalid choice!\n";
                break;
            }

            updated = true;
        }

        // Write either updated or original data
        outFile << fileUsername << "," << password << "," << name << "," << age << ","
            << gender << "," << height << "," << weight << "," << role << "\n";
    }

    // Close files
    infile.close();
    outFile.close();

    // Remove original file and rename temp file, with error checking
    if (remove("UserData.csv") != 0) {
        perror("Error deleting old file");
    }
    else if (rename("TempUserData.csv", "UserData.csv") != 0) {
        perror("Error renaming file");
    }
    else {
        if (updated) {
            cout << "Profile updated successfully!\n";
        }
        else {
            cout << "No changes made to your profile.\n";
        }
    }
}

// Method to view BMI
void Member::viewBMI(const std::string& username) {
    ifstream infile("UserData.csv");
    if (!infile) {
        cout << "Error: Could not Open UserData.csv\n";
        return;
    }

    string line;
    bool isHeader = true;
    bool found = false;

    while (getline(infile, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string fileUsername, password, name, age, gender, height, weight, role;
        getline(ss, fileUsername, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, height, ',');
        getline(ss, weight, ',');
        getline(ss, role, ',');

        if (fileUsername == username) {
            double h = stod(height) / 100.0;
            double w = stod(weight);
            double bmi = w / (h * h);

            cout << "\n====== Your BMI ======\n";
            cout << "Height: " << height << " cm\n";
            cout << "Weight: " << weight << " kg\n";
            cout << "BMI: " << bmi << "\n";
            cout << "=======================\n";

            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << "No user found with your username.\n";
    }
}

void Member::trackProgress(double newWeight, const std::string& achievements) {
    // Validate weight input
    if (newWeight <= 0) {
        std::cerr << "Invalid weight value provided.\n";
        return;
    }

    // Calculate BMI
    double height = getHeight() / 100.0; // Assuming height is given in centimeters
    if (height <= 0) {
        std::cerr << "Invalid height value provided.\n";
        return;
    }

    double bmi = newWeight / (height * height);

    // Get current date
    std::time_t now = std::time(nullptr);
    std::tm currentTime{};

    // Use localtime_s for safer time conversion
    if (localtime_s(&currentTime, &now) == 0) {
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &currentTime);
        std::string currentDate(buffer);

        // Output the current date
        std::cout << "Current date: " << currentDate << std::endl;

        // Create progress record
        ProgressRecord record = {
            currentDate,
            newWeight,
            bmi,
            achievements
        };

        // Add to progress history
        addProgressRecord(record);

        std::cout << "Progress record added successfully!\n";
    }
    else {
        std::cerr << "Error converting time.\n";
    }
}

void Member::displayProgressHistory() {
    std::vector<ProgressRecord> history = getProgressHistory();

    if (history.empty()) {
        std::cout << "No progress history found.\n";
        return;
    }

    std::cout << "\n====== Progress History ======\n";
    std::cout << std::left
        << std::setw(15) << "Date"
        << std::setw(10) << "Weight"
        << std::setw(10) << "BMI"
        << "Achievements\n";
    std::cout << "-------------------------------------\n";

    for (const auto& record : history) {
        std::cout << std::left
            << std::setw(15) << record.date
            << std::setw(10) << record.weight
            << std::setw(10) << record.bmi
            << record.achievements << "\n";
    }
    std::cout << "===============================\n";
}

void Member::generateWorkoutPlan() {
    // Predefined workout plans based on BMI or fitness goals
    std::ofstream outFile("WorkoutPlans.csv", std::ios::app);

    if (!outFile) {
        std::cout << "Error creating workout plan.\n";
        return;
    }

    double bmi = calculateBMI();
    std::string workoutPlan;

    if (bmi < 18.5) {  // Underweight
        workoutPlan = "Muscle Building Plan: Strength Training 3x/week, High Protein Diet, Weight Gain Focus";
    }
    else if (bmi >= 18.5 && bmi < 25) {  // Normal weight
        workoutPlan = "Balanced Fitness Plan: Cardio 2x/week, Strength Training 2x/week, Balanced Diet";
    }
    else if (bmi >= 25 && bmi < 30) {  // Overweight
        workoutPlan = "Weight Loss Plan: Cardio 3x/week, HIIT 2x/week, Calorie Deficit Diet";
    }
    else {  // Obese
        workoutPlan = "Comprehensive Fitness Plan: Low Impact Cardio 3x/week, Resistance Training 2x/week, Nutritional Guidance";
    }

    // Append to existing workout plans
    outFile << getUsername() << "," << workoutPlan << "\n";
    outFile.close();

    std::cout << "Personalized Workout Plan Generated:\n" << workoutPlan << "\n";
}

double Member::calculateBMI() {
    double h = getHeight() / 100.0;
    return getWeight() / (h * h);
}