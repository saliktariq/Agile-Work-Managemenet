#include <iostream>
#include "Repository.h"
#include "users.h"
#include <windows.h>
#include <sstream>
#include <iomanip>


using namespace std;

class TEST {
public:
	int last_user = 0;
	int last_project = 0;
	int last_kanban_board = 0;

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
        std::cout << "--Resetting testing Database--" << endl;
        repository->resetDatabase();
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
		last_user = repository->getIDofLastUserInserted();
		cout << "The ID of the last user inserted is: " << last_user << endl;

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
		last_project = repository->getIDofLastProjectInserted();
		cout << "The ID of the last project inserted is: " << last_project << endl;
        
    }

    void TEST_KanbanBoards() {
        std::cout << "\033[44;37mTESTING KANBAN BOARD CLASS DATABASE OPERATIONS\033[0m" << std::endl;

        int projectId = 1;
        std::string boardName = "Test Kanban Board";
        std::string startDate = "2023-01-01";
        std::string endDate = "2023-12-31";
        KanbanBoard kb(0, boardName, last_project, startDate, endDate);

        std::cout << "Setting board name to \'Test Kanban Board\'" << std::endl;
        std::cout << "Setting foreign key project id to last project's id to create relation: " << last_project << std::endl;
        std::cout << "Setting start date to \'2023-01-01\'" << std::endl;
        std::cout << "Setting end date to \'2023-12-31\'" << std::endl;
        std::cout << "Initialising Repository" << std::endl;
        Repository* repository = new Repository();
        std::cout << "Pusing Kanban Board object to the database..." << std::endl;
        repository->createKanbanBoards(kb);
        std::cout << "Retrieving all Kanban Boards from the database..." << std::endl;
        std::vector<std::shared_ptr<KanbanBoard>> boards = repository->getListOfAllKanbanBoards();
        std::cout << std::left << std::setw(10) << "ID"
            << std::setw(30) << "Board Name"
            << std::setw(15) << "Project ID"
            << std::setw(15) << "Start Date"
            << std::setw(15) << "End Date" << std::endl;

        std::cout << std::setfill('-') << std::setw(90) << "-" << std::endl;

        std::cout << std::setfill(' ');

        for (auto board : boards) {
            std::cout << std::left << std::setw(10) << board->getId()
                << std::setw(30) << board->getName()
                << std::setw(15) << board->getProjectId()
                << std::setw(15) << board->getStartDate()
                << std::setw(15) << board->getEndDate() << std::endl;
        }
        last_kanban_board = repository->getIDofLastKanbanBoardInserted();
        std::cout << "The ID of the last Kanban Board inserted is: " << last_kanban_board << std::endl;
    }

    void TEST_Kanban_Column() {
        std::cout << "\033[44;37mTESTING KANBAN COLUMNS CLASS DATABASE OPERATIONS\033[0m" << std::endl;
        std::string columnName = "TO DO";
        int boardId = last_kanban_board;
        int columnPosition = 0;
        KanbanColumn kc(0, columnName, boardId, columnPosition);
        std::cout << "Setting first column name to \'" << columnName << "\' for board id: " << boardId << " at position: " << columnPosition << std::endl;
        std::cout << "Initialising Repository" << std::endl;
        Repository* repository = new Repository();
        std::cout << "Pusing kanban column object to the database..." << std::endl;
        repository->createColumn(kc);

        columnName = "IN PROGRESS";
        boardId = last_kanban_board;
        columnPosition = 1;
        KanbanColumn kc1(0, columnName, boardId, columnPosition);
        std::cout << "Setting first column name to \'" << columnName << "\' for board id: " << boardId << " at position: " << columnPosition << std::endl;


        std::cout << "Pusing kanban column object to the database..." << std::endl;
        repository->createColumn(kc1);

        columnName = "COMPLETED";
        boardId = last_kanban_board;
        columnPosition = 2;
        KanbanColumn kc2(0, columnName, boardId, columnPosition);
        std::cout << "Setting first column name to \'" << columnName << "\' for board id: " << boardId << " at position: " << columnPosition << std::endl;

        std::cout << "Pusing kanban column object to the database..." << std::endl;
        repository->createColumn(kc2);


        std::cout << "Retrieving all kanban columns from the database for board id: " << boardId << "..." << std::endl;
        std::vector<std::shared_ptr<KanbanColumn>> columns = repository->listColumns(boardId);
        std::cout << std::left << std::setw(10) << "ID"
            << std::setw(30) << "Column Name"
            << std::setw(10) << "Board ID"
            << std::setw(15) << "Position"
            << std::endl;
        std::cout << std::setfill('-') << std::setw(70) << "-" << std::endl;
        std::cout << std::setfill(' ');
        for (auto column : columns) {
            std::cout << std::left << std::setw(10) << column->getId()
                << std::setw(30) << column->getName()
                << std::setw(10) << column->getBoardId()
                << std::setw(15) << column->getPosition()
                << std::endl;
        }

    }

    void TEST_IssueType() {
        std::cout << "\033[44;37mTESTING ISSUE TYPES CLASS DATABASE OPERATIONS\033[0m" << std::endl;
        std::string issueTypeName = "Epic";
        IssueType issueType(0, issueTypeName);
        std::cout << "Setting issue type name to \'Epic\'" << std::endl;
        std::cout << "Initialising Repository" << std::endl;
        Repository* repository = new Repository();
        std::cout << "Pusing issue type object to the database..." << std::endl;
        repository->createIssueType(issueType);

        issueTypeName = "Bug";
        IssueType issueType1(0, issueTypeName);
        std::cout << "Setting issue type name to \'Bug\'" << std::endl;
        std::cout << "Pusing issue type object to the database..." << std::endl;
        repository->createIssueType(issueType1);

        issueTypeName = "Story";
        IssueType issueType2(0, issueTypeName);
        std::cout << "Setting issue type name to \'Story\'" << std::endl;
        std::cout << "Pusing issue type object to the database..." << std::endl;
        repository->createIssueType(issueType2);

        issueTypeName = "Task";
        IssueType issueType3(0, issueTypeName);
        std::cout << "Setting issue type name to \'Task\'" << std::endl;
        std::cout << "Pusing issue type object to the database..." << std::endl;
        repository->createIssueType(issueType3);



        std::cout << "Retrieving all issue types from the database..." << std::endl;
        std::vector<std::shared_ptr<IssueType>> issueTypes = repository->listIssueTypes();
        std::cout << std::left << std::setw(10) << "ID"
            << std::setw(30) << "Issue Type Name" << std::endl;

        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;

        std::cout << std::setfill(' ');

        for (auto issueType : issueTypes) {
            std::cout << std::left << std::setw(10) << issueType->getId()
                << std::setw(30) << issueType->getName() << std::endl;
        }
    }




	
};