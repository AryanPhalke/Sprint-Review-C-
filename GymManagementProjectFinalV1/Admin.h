#pragma once
#include "User.h"
#include <string>

// Admin class inherits from User
class Admin : public User {
private:
    std::string adminID;

public:
    // Default constructor
    Admin();

    // Parameterized constructor
    Admin(std::string id, std::string name, int age, std::string gender,
        std::string username, std::string password, std::string adminID);

    // Admin-specific methods
    void addWorkoutPlan(const std::string& memberUsername, const std::string& planDetails);
    void viewWorkoutPlans();
    void removeWorkoutPlan(const std::string& memberUsername);

    // New admin functionalities
    void removeMember(const std::string& memberUsername);
    void removeTrainer(const std::string& trainerUsername);
    void assignMemberToTrainer(const std::string& memberUsername, const std::string& trainerUsername);
    void viewGymStatistics();
};