#pragma once
#include "User.h"
#include <string>

// Member class that inherits for User
class Member : public User {
private:
	std::string membershipType;
	int membershipDuration;

public:
	// Default cstr
	Member();

	// Parameterized cstr
	Member(std::string id, std::string name, int age, std::string gender, std::string username, std::string password, double height, double weight, std::string membershipType, int membershipDuration);

	void viewWorkoutPlan(const std::string& username);
	void updateProfile(const std::string& username);
	void viewBMI(const std::string& username);
	void trackProgress(double newWeight, const std::string& achievements);
	void displayProgressHistory();
	void generateWorkoutPlan();
	double calculateBMI();
};