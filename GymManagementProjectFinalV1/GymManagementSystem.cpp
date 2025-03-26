#include "GymManagementSystem.h"
#include "User.h"
#include "Admin.h"
#include "Member.h"
#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h> 
using namespace std;

// Method to authenticate the user
void GymManagementSystem::authenticateUser() {
	// Declare variable for input
	string inputUsername, inputPassword;

	// Get username from user
	cout << "Enter your username: ";
	cin >> inputUsername;

	// Get password from the user
	char ch;
	while ((ch = _getch()) != '\r') {
		inputPassword += ch;
		cout << '*'; // Mask character with '*'
	}

	cout << endl;

	ifstream file("UserData.csv");

	// check if the file is opened successfully
	if (!file) {
		cout << "Error: Could not open UserData.csv\n";
		return;
	}

	// Variable for reading file
	string line, username, password, name, age, gender, height, weight, role;
	bool isAuthenticated = false;
	bool isFirstRow = true;

	// Read file line by line
	while (getline(file, line)) {
		// Skip header row
		if (isFirstRow) {
			isFirstRow = false;
			continue;
		}

		// Parse CSV line
		stringstream ss(line);
		getline(ss, username, ',');
		getline(ss, password, ',');
		getline(ss, name, ',');
		getline(ss, age, ',');
		getline(ss, gender, ',');
		getline(ss, height, ',');
		getline(ss, weight, ',');
		getline(ss, role, ',');

		// Check if credentials match
		if (inputUsername == username && inputPassword == password) {
			isAuthenticated = true;
			break;
		}
	}

	// CLose the file
	file.close();

	// If authentication succesful
	if (isAuthenticated) {
		cout << "Login Successfull Welcome, " << username << "!\n";
		if (role == "Admin") {
			// Admin creds
			if (role == "Admin") {
				// Create admin object
				Admin admin("A001", name, std::stoi(age), gender, username, password, "ADMIN001");

				// Display admin menu
				displayAdminMenu(admin);
			}
		}
		else if (role == "Member") {
			// Member creds
			Member member("M001", name, std::stoi(age), gender, username, password,
				std::stod(height), std::stod(weight), "Regular", 12);

			// display member menu
			displayMemberMenu(member);
		}
		else if (role == "Trainer") {
			// Create trainer object
			Trainer trainer("T001", name, std::stoi(age), gender, username, password,
				"General Fitness", 5);

			// Display trainer menu
			displayTrainerMenu(trainer);
		}
		else {
			// Invalid role
			std::cout << "Invalid user role!\n";
		}
	}
	else {
		// Authentication failed
		std::cout << "Invalid credentials! Try again.\n";
		authenticateUser();
	}
}

// New Admin
void GymManagementSystem::displayAdminMenu(Admin& admin) {
	// Enhanced Admin Menu
	cout << "\n===== Admin Menu =====\n";
	cout << "1. View Members\n";
	cout << "2. View Trainers\n";
	//cout << "3. Manage Workouts\n";
	cout << "3. Remove Member\n";
	cout << "4. Remove Trainer\n";
	cout << "5. Assign Member to Trainer\n";
	cout << "6. Exit\n";

	// Get user choice
	int choice;
	cout << "Enter a number: ";
	cin >> choice;

	// Handle user choice
	switch (choice) {
	case 1:
		// View all members
		viewMembers();
		displayAdminMenu(admin);
		break;
	case 2:
		// View all trainers
		viewTrainers();
		displayAdminMenu(admin);
		break;
	case 3: {
		string memberUsername;
		cout << "Enter username of member to remove: ";
		cin >> memberUsername;
		admin.removeMember(memberUsername);
		displayAdminMenu(admin);
		break;
	}
	case 4: {
		string trainerUsername;
		cout << "Enter username of trainer to remove: ";
		cin >> trainerUsername;
		admin.removeTrainer(trainerUsername);
		displayAdminMenu(admin);
		break;
	}
	case 5: {
		string memberUsername, trainerUsername;
		cout << "Enter member username: ";
		cin >> memberUsername;
		cout << "Enter trainer username: ";
		cin >> trainerUsername;
		admin.assignMemberToTrainer(memberUsername, trainerUsername);
		displayAdminMenu(admin);
		break;
	}
	case 6:
		cout << "Exiting admin menu...\n";
		return;
	default:
		cout << "Invalid choice! Try again.\n";
		displayAdminMenu(admin);
	}
}


// Method to view all members
void GymManagementSystem::viewMembers() {
	// Open user data file
	ifstream file("UserData.csv");

	// Check if file opened succesfully
	if (!file) {
		cout << "Error: Could not open UserData.csv\n ";
		return;
	}
	// Variables for reading file
	std::string line;
	bool isHeader = true;

	// Display header
	cout << "\n Gym Members \n";
	cout << std::setw(12) << std::left << "Username"
		<< std::setw(12) << std::left << "Name"
		<< std::setw(4) << std::left << "Age"
		<< std::setw(8) << std::left << "Gender"
		<< std::setw(8) << std::left << "Height"
		<< std::setw(8) << std::left << "Weight"
		<< std::setw(8) << std::left << "Role"
		<< std::endl;
	cout << "---------------------------\n";

	// Read file line by line
	while (getline(file, line)) {
		// Skip header row
		if (isHeader) {
			isHeader = false;
			continue;
		}

		// Parse CSV line
		std::stringstream ss(line);
		std::string username, password, name, age, gender, height, weight, role;

		getline(ss, username, ',');  // Read username
		getline(ss, password, ',');  // Read password
		getline(ss, name, ',');      // Read name
		getline(ss, age, ',');       // Read age
		getline(ss, gender, ',');    // Read gender
		getline(ss, height, ',');    // Read height
		getline(ss, weight, ',');    // Read weight
		getline(ss, role, ',');      // Read role

		// Display member function
		if (role == "Member") {
			cout << std::setw(12) << std::left << username
				<< std::setw(12) << std::left << name
				<< std::setw(4) << std::left << age
				<< std::setw(8) << std::left << gender
				<< std::setw(8) << std::left << height
				<< std::setw(8) << std::left << weight
				<< std::setw(8) << std::left << role
				<< std::endl;
		}

	}

	// Close the file after processing all records
	file.close();
}

// Method to display trainer menu
void GymManagementSystem::displayTrainerMenu(Trainer& trainer) {
	// Enhanced Trainer Menu
	cout << "\n===== Trainer Menu =====\n";
	cout << "1. View Profile\n";
	cout << "2. View Assigned Members\n";
	cout << "3. Assign Workout Plan\n";
	cout << "4. Remove Workout Plan\n";
	cout << "5. Exit\n";

	// Get user choice
	int choice;
	cout << "Enter a number: ";
	cin >> choice;

	// Handle user choice
	switch (choice) {
	case 1:
		// View profile
		trainer.viewProfile();
		displayTrainerMenu(trainer);
		break;
	case 2:
		// View assigned members
		trainer.viewAssignedMembers(trainer.getUsername());
		displayTrainerMenu(trainer);
		break;
	case 3: {
		// Get member username
		string memberUsername;
		cout << "Enter member username: ";
		cin >> memberUsername;

		// Clear input buffer
		cin.ignore();

		// Get workout plan details
		string planDetails;
		cout << "Enter workout plan details: ";
		getline(cin, planDetails);

		// Assign workout plan
		trainer.assignWorkoutPlan(memberUsername, planDetails);
		displayTrainerMenu(trainer);
		break;
	}
	case 4: {
		// Remove workout plan
		string memberUsername;
		cout << "Enter member username to remove plan: ";
		cin >> memberUsername;
		trainer.removeWorkoutPlan(memberUsername);
		displayTrainerMenu(trainer);
		break;
	}
	case 5:
		// Exit trainer menu
		cout << "Exiting trainer menu...\n";
		return;
	default:
		// Invalid choice
		cout << "Invalid choice! Try again.\n";
		displayTrainerMenu(trainer);
	}
}

// Method to view Trainers
void GymManagementSystem::viewTrainers() {
	// Open user data file
	ifstream file("UserData.csv");

	// Check if file opened successfully
	if (!file) {
		cout << "Error: Could not open UserData.csv\n ";
		return;
	}
	// Variables for reading file
	std::string line;
	bool isHeader = true;

	// Display header
	cout << "\n Gym Trainers \n";
	cout << std::setw(12) << std::left << "Username"
		<< std::setw(12) << std::left << "Name"
		<< std::setw(4) << std::left << "Age"
		<< std::setw(8) << std::left << "Gender"
		<< std::setw(15) << std::left << "Specialization"
		<< std::endl;
	cout << "---------------------------\n";

	// Read file line by line
	while (getline(file, line)) {
		// Skip header row
		if (isHeader) {
			isHeader = false;
			continue;
		}

		// Parse CSV line
		std::stringstream ss(line);
		std::string username, password, name, age, gender, height, weight, role;

		getline(ss, username, ',');  // Read username
		getline(ss, password, ',');  // Read password
		getline(ss, name, ',');      // Read name
		getline(ss, age, ',');       // Read age
		getline(ss, gender, ',');    // Read gender
		getline(ss, height, ',');    // Read height
		getline(ss, weight, ',');    // Read weight
		getline(ss, role, ',');      // Read role

		// Display trainer information
		if (role == "Trainer") {
			cout << std::setw(12) << std::left << username
				<< std::setw(12) << std::left << name
				<< std::setw(4) << std::left << age
				<< std::setw(8) << std::left << gender
				<< std::setw(15) << std::left << "General Fitness"
				<< std::endl;
		}
	}

	// Close the file after processing all records
	file.close();
}

// Method to display Member Menu
void GymManagementSystem::displayMemberMenu(Member& member) {
	// Updated member menu with new options
	cout << "\n===== Member Menu =====\n";
	cout << "1. View Profile\n";
	cout << "2. Edit Profile\n";
	cout << "3. View Workout Plan\n";
	cout << "4. View BMI\n";
	cout << "5. Track Progress\n";
	cout << "6. View Progress History\n";
	cout << "7. Generate Personalized Workout Plan\n";
	cout << "8. Gym Statistics\n";
	cout << "9. Exit\n";

	int choice;
	cout << "Enter a number: ";
	cin >> choice;

	switch (choice) {
	case 1:
		// View profile
		member.viewProfile();

		// Return to member menu
		displayMemberMenu(member);
		break;
	case 2:
		// Edit profile
		member.updateProfile(member.getUsername());

		// Return to member menu
		displayMemberMenu(member);
		break;
	case 3:
		// View workout plan
		member.viewWorkoutPlan(member.getUsername());

		// Return to member menu
		displayMemberMenu(member);
		break;
	case 4:
		member.viewBMI(member.getUsername());
		displayMemberMenu(member);
		break;

	case 5: {
		double newWeight;
		string achievements;

		cout << "Enter your current weight: ";
		cin >> newWeight;

		cin.ignore(); // Clear input buffer
		cout << "Enter achievements or notes: ";
		getline(cin, achievements);

		member.trackProgress(newWeight, achievements);
		displayMemberMenu(member);
		break;
	}

	case 6:
		member.displayProgressHistory();
		displayMemberMenu(member);
		break;

	case 7:
		member.generateWorkoutPlan();
		displayMemberMenu(member);
		break;

	case 8:
		displayGymStatistics();
		displayMemberMenu(member);
		break;

	case 9:
		cout << "Exiting member menu...\n";
		return;

	default:
		cout << "Invalid choice! Try again.\n";
		displayMemberMenu(member);
	}
}

// Method to view Gym Statistics
void GymManagementSystem::displayGymStatistics() {
	// Total members
	int totalMembers = 0;
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

		// Only process members
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
	}
	file.close();

	// Display statistics
	cout << "\n===== Gym Statistics =====\n";
	cout << "Total Members: " << totalMembers << "\n";

	// BMI Distribution
	cout << "\nBMI Distribution:\n";
	cout << "Underweight (BMI < 18.5): " << underweightCount << " members\n";
	cout << "Normal Weight (18.5 - 24.9): " << normalCount << " members\n";
	cout << "Overweight (25 - 29.9): " << overweightCount << " members\n";
	cout << "Obese (BMI >= 30): " << obeseCount << " members\n";

	// Average BMI
	double avgBMI = totalMembers > 0 ? (totalBMI / totalMembers) : 0.0;
	cout << "\nAverage Member BMI: " << std::fixed << std::setprecision(2) << avgBMI << "\n";
	cout << "===============================\n";
}