#include "Database.h"

void testLogin(DatabaseHandler *db)
{
    // test login
    std::string username;
    std::cout << "Enter a username: ";
    std::getline(std::cin, username);
    // repeat with password
    std::string password;
    std::cout << "Enter a password: ";
    std::getline(std::cin, password);

    db->checkLogin(username, password);
}

void testCreateAcoount(DatabaseHandler *db)
{
    // test login
    std::string username;
    std::cout << "Enter a username: ";
    std::getline(std::cin, username);
    // repeat with password
    std::string password;
    std::cout << "Enter a password: ";
    std::getline(std::cin, password);

    db->createAccount(username, password);
}

int main(int argc, char *argv[])
{
    DatabaseHandler db;

    std::cout << "Test account creation(1) or login(2): ";
    std::string choice;
    std::getline(std::cin, choice);
    int choiceInt = std::stoi(choice);
    if (choiceInt == 1) {
        testCreateAcoount(&db);
    } else if (choiceInt == 2) {
        testLogin(&db);
    } else {
        std::cout << "Invalid choice" << std::endl;
    }

    return 0;
}
