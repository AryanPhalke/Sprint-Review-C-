// Trainer.cpp - Implementation of the Trainer class methods
#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Default constructor
Trainer::Trainer() : User() {
    // Initialize trainer-specific attributes
    specialization = "";
    experience = 0;
}

// Parameterized constructor
Trainer::Trainer(std::string id, std::string name, int age, std::string gender,
    std::string username, std::string password,
    std::string specialization, int experience)
    : User(id, name, age, gender, "Trainer", username, password) {
    // Set trainer-specific attributes
    this->specialization = specialization;
    this->experience = experience;
}

// Method to assign workout plan to a member
void Trainer::assignWorkoutPlan(const std::string& memberUsername, const std::string& planDetails) {
    // Open workout plans file in append mode
    std::ofstream outFile("WorkoutPlans.csv", std::ios::app);

    // Check if file opened successfully1`
    if (!outFile) {
        std::cout << "Error: Unable to open WorkoutPlans.csv!\n";
        return;
    }

    // Check if file is empty and add header if needed
    std::ifstream checkFile("WorkoutPlans.csv");
    bool fileEmpty = checkFile.peek() == std::ifstream::traits_type::eof();
    checkFile.close();

    // Add header if file is empty
    if (fileEmpty) {
        outFile << "Username,PlanDetails\n";
    }

    // Write workout plan details to file
    outFile << memberUsername << "," << planDetails << "\n";

    // Close the file
    outFile.close();
    
    // Display success message
    std::cout << "Workout plan assigned successfully to " << memberUsername << "!\n";
}

// Method to view all members assigned to the trainer
void Trainer::viewAssignedMembers(const std::string& trainerUsername) {
    // Open trainer assignments file
    std::ifstream file("TrainerAssignments.csv");

    // Check if file opened successfully
    if (!file) {
        std::cout << "Error: Could not open TrainerAssignments.csv or file doesn't exist!\n";
        std::cout << "No members assigned to you yet.\n";
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
        std::string fileTrainerUsername, memberUsername;

        // Parse trainer and member usernames
        getline(ss, fileTrainerUsername, ',');
        getline(ss, memberUsername, ',');

        // If trainer username matches, display assigned member
        if (fileTrainerUsername == trainerUsername) {
            if (!found) {
                std::cout << "\n====== Your Assigned Members ======\n";
                found = true;
            }
            std::cout << memberUsername << std::endl;
        }
    }

    // Close the file
    file.close();

    // If no members found
    if (!found) {
        std::cout << "No members assigned to you yet.\n";
    }
    else {
        std::cout << "================================\n";
    }
}

void Trainer::removeWorkoutPlan(const std::string& memberUsername) {
    // Open workout plans file
    std::ifstream inFile("WorkoutPlans.csv");
    std::ofstream outFile("TempWorkoutPlans.csv");

    // Check if file opened successfully
    if (!inFile || !outFile) {
        std::cout << "Error: Could not open files for workout plan removal!\n";
        return;
    }

    std::string line;
    bool found = false;
    bool isHeader = true;

    // Read file line by line
    while (getline(inFile, line)) {
        // Handle header row
        if (isHeader) {
            outFile << line << "\n";
            isHeader = false;
            continue;
        }

        // String stream to parse CSV line
        std::stringstream ss(line);
        std::string username;

        // Get username from the line
        getline(ss, username, ',');

        // If username doesn't match, keep the line
        if (username != memberUsername) {
            outFile << line << "\n";
        }
        else {
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
        std::cout << "Workout plan for " << memberUsername << " removed successfully!\n";
    }
    else {
        // Remove temp file if no matching plan found
        remove("TempWorkoutPlans.csv");
        std::cout << "No workout plan found for " << memberUsername << "!\n";
    }
}