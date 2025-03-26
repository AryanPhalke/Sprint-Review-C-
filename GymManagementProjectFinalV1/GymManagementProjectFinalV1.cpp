#include "GymManagementSystem.h"
#include "User.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	cout << "Welcome to Arnold Gym" << endl;
	cout << "1. Existing User\n";
	cout << "2. New User\n";
	cout << "3. Exit User\n";

	int choice;
	cout << "Enter your choice ";
	cin >> choice;

	// GymManagementSystem Object

	GymManagementSystem system;

	switch (choice) {
	case 1:
		system.authenticateUser();
		break;
	case 2:
	{
		User newUser;
		newUser.newProfile();

		// authenticate the user
		system.authenticateUser();
	}
	case 3:
		cout << "Thank You! Visit again!\n";
		return 0;

	default:
		cout << "Invalid please start again";
	}





	return 0;
}