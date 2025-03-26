#pragma once
#include "User.h"
#include <string>

// Trainer class that inherits from User
class Trainer : public User {
private:
    // Trainer-specific attributes
    std::string specialization;
    int experience;

public:
    // Default constructor
    Trainer();

    // Parameterized constructor
    Trainer(std::string id, std::string name, int age, std::string gender,
        std::string username, std::string password,
        std::string specialization, int experience);

    // Trainer-specific methods
    void assignWorkoutPlan(const std::string& memberUsername, const std::string& planDetails);
    void removeWorkoutPlan(const std::string& memberUsername);
    void viewAssignedMembers(const std::string& trainerUsername);
};