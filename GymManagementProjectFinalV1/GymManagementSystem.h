#pragma once

#include "Member.h"
#include "Trainer.h"
#include "Admin.h"
#include <vector>

// GymManagementSystem class
class GymManagementSystem {
private:
    // Collections of users
    std::vector<Member> members;
    std::vector<Trainer> trainers;
    std::vector<Admin> admins;

public:
    // Authentication method
    void authenticateUser();

    // Menu display methods
    void displayAdminMenu(Admin& admin);
    void displayMemberMenu(Member& member);
    void displayTrainerMenu(Trainer& trainer);

    // User management methods
    void viewMembers();
    void viewTrainers();

    void displayGymStatistics();
};