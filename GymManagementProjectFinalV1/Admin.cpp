#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Admin cstr
Admin::Admin() : User() {
    adminID = "";
}

// Parameterized constructor for Admin
Admin::Admin(std::string id, std::string name, int age, std::string gender,
    std::string username, std::string password, std::string adminID)
    : User(id, name, age, gender, "Admin", username, password) {
    // Set admin-specific ID
    this->adminID = adminID;
}

// Remove the Member
void Admin::removeMember(const std::string& memberUsername) {
    // Open user data file
    ifstream inFile("UserData.csv");
    ofstream outFile("TempUserData.csv");

    // Check if files opened successfully
    if (!inFile || !outFile) {
        cout << "Error: Could not open files for member removal!\n";
        return;
    }

    string line;
    bool found = false;
    bool isHeader = true;

    // Read and process file
    while (getline(inFile, line)) {
        if (isHeader) {
            outFile << line << "\n";  // Write header to new file
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string username, password, name, age, gender, height, weight, role;

        // Extract fields correctly
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, height, ',');
        getline(ss, weight, ',');
        getline(ss, role, ',');  // Fetch role correctly

        // Trim any trailing spaces or newlines in role
        role.erase(role.find_last_not_of(" \n\r\t") + 1);

        // Convert role to lowercase to avoid case sensitivity issues
        transform(role.begin(), role.end(), role.begin(), ::tolower);

        // Debugging output to verify what we are reading
        cout << "Checking Username: " << username << " | Role: [" << role << "]\n";

        // If not the member to remove, write back to temp file
        if (username != memberUsername || role != "member") {
            outFile << line << "\n";
        }
        else {
            found = true;
        }
    }

    // Close files
    inFile.close();
    outFile.close();

    // Replace original file with the new file if the member was found
    if (found) {
        remove("UserData.csv");
        rename("TempUserData.csv", "UserData.csv");

        // Remove associated workout plans
        ifstream inWorkout("WorkoutPlans.csv");
        ofstream outWorkout("TempWorkoutPlans.csv");

        if (!inWorkout || !outWorkout) {
            cout << "Error: Could not open workout plans file!\n";
            return;
        }

        string workoutLine;
        bool workoutFound = false;
        bool isWorkoutHeader = true;

        while (getline(inWorkout, workoutLine)) {
            if (isWorkoutHeader) {
                outWorkout << workoutLine << "\n";
                isWorkoutHeader = false;
                continue;
            }

            stringstream ss(workoutLine);
            string username;
            getline(ss, username, ',');

            if (username != memberUsername) {
                outWorkout << workoutLine << "\n";
            }
            else {
                workoutFound = true;
            }
        }

        inWorkout.close();
        outWorkout.close();

        remove("WorkoutPlans.csv");
        rename("TempWorkoutPlans.csv", "WorkoutPlans.csv");

        cout << "Member " << memberUsername << " removed successfully!\n";
    }
    else {
        remove("TempUserData.csv");  // Cleanup unused temp file
        cout << "Member " << memberUsername << " not found!\n";
    }
}

// Remove Trainer
void Admin::removeTrainer(const std::string& memberUsername) {
    // Open user data file
    ifstream inFile("UserData.csv");
    ofstream outFile("TempUserData.csv");

    // Check if files opened successfully
    if (!inFile || !outFile) {
        cout << "Error: Could not open files for member removal!\n";
        return;
    }

    string line;
    bool found = false;
    bool isHeader = true;

    // Read and process file
    while (getline(inFile, line)) {
        if (isHeader) {
            outFile << line << "\n";  // Write header to new file
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string username, password, name, age, gender, height, weight, role;

        // Extract fields correctly
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, height, ',');
        getline(ss, weight, ',');
        getline(ss, role, ',');  // Fetch role correctly

        // Trim any trailing spaces or newlines in role
        role.erase(role.find_last_not_of(" \n\r\t") + 1);

        // Convert role to lowercase to avoid case sensitivity issues
        transform(role.begin(), role.end(), role.begin(), ::tolower);

        // Debugging output to verify what we are reading
        cout << "Checking Username: " << username << " | Role: [" << role << "]\n";

        // If not the member to remove, write back to temp file
        if (username != memberUsername || role != "trainer") {
            outFile << line << "\n";
        }
        else {
            found = true;
        }
    }

    // Close files
    inFile.close();
    outFile.close();

    // Replace original file with the new file if the member was found
    if (found) {
        remove("UserData.csv");
        rename("TempUserData.csv", "UserData.csv");

        // Remove associated workout plans
        ifstream inWorkout("WorkoutPlans.csv");
        ofstream outWorkout("TempWorkoutPlans.csv");

        if (!inWorkout || !outWorkout) {
            cout << "Error: Could not open workout plans file!\n";
            return;
        }

        string workoutLine;
        bool workoutFound = false;
        bool isWorkoutHeader = true;

        while (getline(inWorkout, workoutLine)) {
            if (isWorkoutHeader) {
                outWorkout << workoutLine << "\n";
                isWorkoutHeader = false;
                continue;
            }

            stringstream ss(workoutLine);
            string username;
            getline(ss, username, ',');

            if (username != memberUsername) {
                outWorkout << workoutLine << "\n";
            }
            else {
                workoutFound = true;
            }
        }

        inWorkout.close();
        outWorkout.close();

        remove("WorkoutPlans.csv");
        rename("TempWorkoutPlans.csv", "WorkoutPlans.csv");

        cout << "Trainer " << memberUsername << " removed successfully!\n";
    }
    else {
        remove("TempUserData.csv");  // Cleanup unused temp file
        cout << "Trainer " << memberUsername << " not found!\n";
    }
}

void Admin::assignMemberToTrainer(const std::string& memberUsername, const std::string& trainerUsername) {
    // Open trainer assignments file in append mode
    ofstream outFile("TrainerAssignments.csv", ios::app);

    // Check if file opened successfully
    if (!outFile) {
        cout << "Error: Unable to open TrainerAssignments.csv!\n";
        return;
    }

    // Check if file is empty and add header if needed
    ifstream checkFile("TrainerAssignments.csv");
    bool fileEmpty = checkFile.peek() == ifstream::traits_type::eof();
    checkFile.close();

    // Add header if file is empty
    if (fileEmpty) {
        outFile << "TrainerUsername,MemberUsername\n";
    }

    // Write trainer-member assignment
    outFile << trainerUsername << "," << memberUsername << "\n";

    // Close the file
    outFile.close();

    cout << "Member " << memberUsername << " assigned to Trainer " << trainerUsername << " successfully!\n";
}

// Method to add a new workout plan
void Admin::addWorkoutPlan(const std::string& memberUsername, const std::string& planDetails) {
    // Open workout plans file in append mode
    ofstream outFile("WorkoutPlans.csv", std::ios::app);

    // Check if file opened successfully
    if (!outFile) {
        cout << "Error: Unable to open WorkoutPlans.csv!\n";
        return;
    }

    // Write workout plan details to file
    outFile << memberUsername << "," << planDetails << "\n";

    // Close the file
    outFile.close();

    // Display success message
    cout << "Workout plan added successfully for " << memberUsername << "!\n";
}

// Method to view all workout plans
void Admin::viewWorkoutPlans() {
    //Open workout plans file
    ifstream file("WorkoutPlans.csv");

    // Check if file Opened successfully
    if (!file) {
        cout << "Error in opening the file!\n";
        return;
    }

    // Variables for reading file
    string line;
    bool isHeader = true;

    // Display header
    cout << "\n Workout Plans \n";
    cout << std::setw(15) << std::left << "Member"
        << std::setw(50) << std::left << "Plan Details"
        << std::endl;
    std::cout << std::setw(15) << std::left << "Member"
        << std::setw(50) << std::left << "Plan Details"
        << std::endl;
    // Read file line by line
    while (getline(file, line)) {
        // Skip header row
        if (isHeader) {
            isHeader = false;
            continue;
        }

        // String stream to parse CSV line
        std::stringstream ss(line);
        std::string username, planDetails;

        // Parse username and plan details
        getline(ss, username, ',');
        getline(ss, planDetails);

        // Display workout plan details
        cout << std::setw(15) << std::left << username
            << std::setw(50) << std::left << planDetails
            << std::endl;
    }

    // Close the file
    file.close();
}

// Method to remove a workout plan
void Admin::removeWorkoutPlan(const std::string& memberUsername) {
    // Open workout plans file
    std::ifstream inFile("WorkoutPlans.csv");

    // Check if file opened successfully
    if (!inFile) {
        cout << "Error: Could not open WorkoutPlans.csv!\n";
        return;
    }

    // Temporary file to store updated data
    ofstream outFile("TempWorkoutPlans.csv");

    // Variables for reading file
    string line;
    bool isHeader = true;
    bool found = false;

    // Read file line by line
    while (getline(inFile, line)) {
        // Handle header row
        if (isHeader) {
            outFile << line << "\n";
            isHeader = false;
            continue;
        }

        // String stream to parse CSV line
        stringstream ss(line);
        string username;

        // Get username from the line
        getline(ss, username, ',');

        // If username doesn't match, keep the line
        if (username != memberUsername) {
            outFile << line << "\n";
        }
        else {
            // Mark that we found the plan to remove
            found = true;
        }
    }

    // Close files
    inFile.close();
    outFile.close();

    // Remove original file and rename temp file
    if (found) {
        remove("WorkoutPlans.csv");
        rename("TempWorkoutPlans.csv", "WorkoutPlans.csv");
        cout << "Workout plan for " << memberUsername << " removed successfully!\n";
    }
    else {
        // Remove temp file if no matching plan found
        remove("TempWorkoutPlans.csv");
        cout << "No workout plan found for " << memberUsername << "!\n";
    }
}

void Admin::viewGymStatistics() {
    // Total members
    int totalMembers = 0, totalTrainers = 0;
    int underweightCount = 0, normalCount = 0, overweightCount = 0, obeseCount = 0;
    double totalBMI = 0.0;

    // Open user data file
    ifstream file("UserData.csv");
    if (!file) {
        cout << "Error: Could not open UserData.csv\n";
        return;
    }

    string line;
    bool isHeader = true;

    // Read file line by line
    while (getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string username, password, name, age, gender, height, weight, role;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, height, ',');
        getline(ss, weight, ',');
        getline(ss, role, ',');

        // Count members and trainers
        if (role == "Member") {
            totalMembers++;

            double h = stod(height) / 100.0;
            double w = stod(weight);
            double bmi = w / (h * h);

            totalBMI += bmi;

            // Categorize BMI
            if (bmi < 18.5) underweightCount++;
            else if (bmi >= 18.5 && bmi < 25) normalCount++;
            else if (bmi >= 25 && bmi < 30) overweightCount++;
            else obeseCount++;
        }
        else if (role == "Trainer") {
            totalTrainers++;
        }
    }
    file.close();

    // Trainer-Member Assignment Statistics
    int totalAssignments = 0;
    std::vector<std::string> trainerAssignments;

    // Open trainer assignments file
    ifstream assignFile("TrainerAssignments.csv");
    if (assignFile) {
        string assignLine;
        bool isAssignHeader = true;
        std::map<std::string, int> trainerMemberCount;

        while (getline(assignFile, assignLine)) {
            if (isAssignHeader) {
                isAssignHeader = false;
                continue;
            }

            stringstream ss(assignLine);
            string trainerUsername, memberUsername;
            getline(ss, trainerUsername, ',');
            getline(ss, memberUsername, ',');

            trainerMemberCount[trainerUsername]++;
            totalAssignments++;
        }

        // Collect trainer with most/least assignments
        for (const auto& pair : trainerMemberCount) {
            trainerAssignments.push_back(pair.first + ": " + to_string(pair.second) + " members");
        }
    }
    assignFile.close();

    // Display statistics
    cout << "\n===== Comprehensive Gym Statistics =====\n";

    // Membership Statistics
    cout << "\nMembership Overview:\n";
    cout << "Total Members: " << totalMembers << "\n";
    cout << "Total Trainers: " << totalTrainers << "\n";

    // BMI Distribution
    cout << "\nBMI Distribution:\n";
    cout << "Underweight (BMI < 18.5): " << underweightCount << " members\n";
    cout << "Normal Weight (18.5 - 24.9): " << normalCount << " members\n";
    cout << "Overweight (25 - 29.9): " << overweightCount << " members\n";
    cout << "Obese (BMI >= 30): " << obeseCount << " members\n";

    // Average BMI
    double avgBMI = totalMembers > 0 ? (totalBMI / totalMembers) : 0.0;
    cout << "\nAverage Member BMI: " << fixed << setprecision(2) << avgBMI << "\n";

    // Trainer-Member Assignments
    cout << "\nTrainer-Member Assignments:\n";
    cout << "Total Member Assignments: " << totalAssignments << "\n";
    cout << "Trainer Assignment Breakdown:\n";
    for (const auto& assignment : trainerAssignments) {
        cout << "  " << assignment << "\n";
    }

    cout << "======================================\n";
}