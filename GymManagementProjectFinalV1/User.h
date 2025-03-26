#pragma once
#include <string>
#include <vector>

struct ProgressRecord {
    std::string date;
    double weight;
    double bmi;
    std::string achievements;
};

// Base User class
class User {
private:
    // User attributes
    std::string userID;
    std::string username;
    std::string password;
    std::string name;
    int age;
    std::string gender;
    std::string role;
    double height;
    double weight;
    std::vector<ProgressRecord> progressHistory;
public:
    // Default constructor
    User();

    // Parameterized constructor with all attributes
    User(std::string id, std::string uname, int uage, std::string ugender, std::string urole,
        std::string uusername, std::string upassword, double uheight, double uweight);

    // Parameterized constructor without height and weight
    User(std::string id, std::string uname, int uage, std::string ugender, std::string urole,
        std::string uusername, std::string upassword);

    // User methods
    void newProfile();
    void viewProfile();
    bool authenticate(std::string uname, std::string pass);

    // Getters
    std::string getUsername();
    std::string getRole();

    double getHeight() const { return height; }
    double getWeight() const { return weight; }
    std::string getUsername() const { return username; }

    void addProgressRecord(const ProgressRecord& record);
    std::vector<ProgressRecord> getProgressHistory();
    double calculateAverageBMI();
};