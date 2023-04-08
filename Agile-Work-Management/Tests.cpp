#include <iostream>
#include "Repository.h"
#include "users.h"
#include <windows.h>
#include <sstream>
#include <iomanip>


using namespace std;

class TEST {
public:
	TEST() {}

	~TEST() {}

	void Test_User() {
		//system("cls");
		std::cout << "\033[44;37mTESTING USERS CLASS DATABASE OPERATIONS\033[0m" << std::endl;
		string username = "Test_Username";
		string fullname = "Test Full Name";
		string emailaddress = "test@testemail.com";
		string role = "Test Roll";
		User u(0, username, fullname, emailaddress, role);
		std::cout << "Setting username to \'Test_Username\'" << endl;
		std::cout << "Setting full name to \'Test Full Name\'" << endl;
		std::cout << "Setting email address to \'test@testemail.com\'" << endl;
		std::cout << "Setting role to \'Test Roll\'" << endl;
		Repository *repository = new Repository();
		std::cout << "Initialising Repository" << endl;
		std::cout << "Pusing user object to the database..." << endl;
		repository->createUser(u);
		std::cout << "Retrieving all usernames from the database..." << endl;
		std::vector<std::shared_ptr<User>> users = repository->listAllUsers();
		std::cout << std::left << std::setw(10) << "ID"
			<< std::setw(20) << "Username"
			<< std::setw(30) << "Full Name"
			<< std::setw(30) << "Email"
			<< std::setw(20) << "Role" << std::endl;

		std::cout << std::setfill('-') << std::setw(110) << "-" << std::endl;

		std::cout << std::setfill(' ');

		for (auto user : users) {
			std::cout << std::left << std::setw(10) << user->getId()
				<< std::setw(20) << user->getUsername()
				<< std::setw(30) << user->getFullName()
				<< std::setw(30) << user->getEmail()
				<< std::setw(20) << user->getRole() << std::endl;
		}

		cout << "The ID of the last user inserted is: " << repository->getIDofLastUserInserted() << endl;

	}

    void TEST_Project() {
        std::cout << "\033[44;37mTESTING PROJECTS CLASS DATABASE OPERATIONS\033[0m" << std::endl;
        std::string projectName = "Test_Project";
        Project p(0, projectName);
        std::cout << "Setting project name to \'Test_Project\'" << std::endl;
        std::cout << "Initialising Repository" << std::endl;
        Repository* repository = new Repository();
        std::cout << "Pusing project object to the database..." << std::endl;
        repository->createProject(p);
        std::cout << "Retrieving all project names from the database..." << std::endl;
        std::vector<std::shared_ptr<Project>> projects = repository->listProjects();
        std::cout << std::left << std::setw(10) << "ID"
            << std::setw(30) << "Project Name" << std::endl;

        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;

        std::cout << std::setfill(' ');

        for (auto project : projects) {
            std::cout << std::left << std::setw(10) << project->getId()
                << std::setw(30) << project->getName() << std::endl;
        }

		cout << "The ID of the last project inserted is: " << repository->getIDofLastProjectInserted() << endl;
        
    }



	
};