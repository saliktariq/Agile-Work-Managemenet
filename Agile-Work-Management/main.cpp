#include <iostream>
#include "credentials.h"
#include "database.h"
#include "ProjectDAO.h"
#include "Project.h"
#include "KanbanColumnsDAO.h"
#include "KanbanBoardsDAO.h"
#include "UsersDAO.h"
#include "IssuesTypesDAO.h"

using namespace std;
int main() {

    /* Database credentials*/
    std::string host = Credentials::LOCALHOST;
    std::string username = Credentials::USERNAME;
    std::string password = Credentials::PASSWORD;
    std::string databaseName = Credentials::DATABASE_NAME;

    /* Instantiating database*/

    //Database* db = new Database(host, username, password, databaseName);

    std::shared_ptr<Database> db = std::make_shared<Database>(host, username, password, databaseName);

    /* Connecting the database*/

    db->connect();
    
    // Test the ProjectDAO
    ProjectsDAO projectDAO(db);
    Project project1(0, "Project 1");
    Project project2(0, "Project 2");

    // Create two projects
    projectDAO.create(project1);
    projectDAO.create(project2);

    // List all projects
    std::vector<std::shared_ptr<Project>> projects = projectDAO.list();
    for (auto& project : projects) {
        std::cout << "Project ID: " << project->getId() << ", Project Name: " << project->getName() << std::endl;
    }

    // Update the name of project 1
    project1.setName("Updated Project 1");
    projectDAO.update(project1);

    // Delete project 2
  //  projectDAO.del(project2.getId());

    // List all projects again
    projects = projectDAO.list();
    for (auto& project : projects) {
        std::cout << "Project ID: " << project->getId() << ", Project Name: " << project->getName() << std::endl;
    }

   //  Test the KanbanBoardsDAO
    KanbanBoardsDAO kanbanBoardsDAO(db);
    KanbanBoard board1(0, "Board 1", project1.getId(), "2023-04-10", "2023-04-20");
    KanbanBoard board2(0, "Board 2", project1.getId(), "2023-04-15", "2023-04-25");

    // Create two boards
    kanbanBoardsDAO.create(board1);
    kanbanBoardsDAO.create(board2);

    // List all boards for project 1
    std::vector<std::shared_ptr<KanbanBoard>> boards = kanbanBoardsDAO.list(project1.getId());
    for (auto& board : boards) {
        std::cout << "Board ID: " << board->getId() << ", Board Name: " << board->getName() << ", Project ID: " << board->getProjectId() << std::endl;
    }

    // Update the name of board 1
    board1.setName("Updated Board 1");
    kanbanBoardsDAO.update(board1);

    // Delete board 2
    kanbanBoardsDAO.del(board2.getId());

    // List all boards for project 1 again
    boards = kanbanBoardsDAO.list(project1.getId());
    for (auto& board : boards) {
        std::cout << "Board ID: " << board->getId() << ", Board Name: " << board->getName() << ", Project ID: " << board->getProjectId() << std::endl;
    }

    // Get board by ID
    std::shared_ptr<KanbanBoard> board = kanbanBoardsDAO.getBoard(1);
    if (board != nullptr) {
        std::cout << "Board ID: " << board->getId() << std::endl;
        std::cout << "Board Name: " << board->getName() << std::endl;
        std::cout << "Project ID: " << board->getProjectId() << std::endl;
        std::cout << "Start Date: " << board->getStartDate() << std::endl;
        std::cout << "End Date: " << board->getEndDate() << std::endl;
    }

    // List all boards for a project
    std::vector<std::shared_ptr<KanbanBoard>> boards2 = kanbanBoardsDAO.list(1);
    for (auto board : boards2) {
        std::cout << "Board ID: " << board->getId() << std::endl;
        std::cout << "Board Name: " << board->getName() << std::endl;
        std::cout << "Project ID: " << board->getProjectId() << std::endl;
        std::cout << "Start Date: " << board->getStartDate() << std::endl;
        std::cout << "End Date: " << board->getEndDate() << std::endl;
    }

    // Test the KanbanColumnsDAO
    KanbanColumnsDAO kanbanColumnsDAO(db);
    KanbanColumn column1(0, "Column 1", 1, 1);
    KanbanColumn column2(0, "Column 2", 1, 2);

    // Create two columns
    kanbanColumnsDAO.create(column1);
    kanbanColumnsDAO.create(column2);

    // List all columns for board 1
    std::vector<std::shared_ptr<KanbanColumn>> columns = kanbanColumnsDAO.list(1);
    for (auto& column : columns) {
        std::cout << "Column ID: " << column->getId() << ", Column Name: " << column->getName() << ", Board ID: " << column->getBoardId() << ", Position: " << column->getPosition() << std::endl;
    }

    // Update the name of column 1
    column1.setName("Updated Column 1");
    kanbanColumnsDAO.update(column1);

    // Delete column 2
    kanbanColumnsDAO.del(column2.getId());

    // List all columns for board 1 again
    columns = kanbanColumnsDAO.list(1);
    for (auto& column : columns) {
        std::cout << "Column ID: " << column->getId() << ", Column Name: " << column->getName() << ", Board ID: " << column->getBoardId() << ", Position: " << column->getPosition() << std::endl;
    }

    // Get column by ID
    std::shared_ptr<KanbanColumn> column = kanbanColumnsDAO.getColumn(1);
    if (column != nullptr) {
        std::cout << "Column ID: " << column->getId() << std::endl;
        std::cout << "Column Name: " << column->getName() << std::endl;
        std::cout << "Board ID: " << column->getBoardId() << std::endl;
        std::cout << "Position: " << column->getPosition() << std::endl;
    }


    // Test the UsersDAO
    UsersDAO usersDAO(db);
    User user1(0, "user1", "User One", "user1@example.com", "user");
    User user2(0, "user2", "User Two", "user2@example.com", "admin");

    // Create two users
    usersDAO.create(user1);
    usersDAO.create(user2);

    // List all users
    std::vector<std::shared_ptr<User>> users = usersDAO.list();
    for (auto& user : users) {
        std::cout << "User ID: " << user->getId() << ", User Name: " << user->getUsername() << ", Full Name: " << user->getFullName() << ", Email: " << user->getEmail() << ", Role: " << user->getRole() << std::endl;
    }

    // Update the role of user 1
    user1.setRole("admin");
    usersDAO.update(user1);

    // Delete user 2
    usersDAO.del(user2.getId());

    // List all users again
    users = usersDAO.list();
    for (auto& user : users) {
        std::cout << "User ID: " << user->getId() << ", User Name: " << user->getUsername() << ", Full Name: " << user->getFullName() << ", Email: " << user->getEmail() << ", Role: " << user->getRole() << std::endl;
    }

    // Get user by ID
    std::shared_ptr<User> user = usersDAO.getUser(1);
    if (user != nullptr) {
        std::cout << "User ID: " << user->getId() << std::endl;
        std::cout << "User Name: " << user->getUsername() << std::endl;
        std::cout << "Full Name: " << user->getFullName() << std::endl;
        std::cout << "Email: " << user->getEmail() << std::endl;
        std::cout << "Role: " << user->getRole() << std::endl;
    }

    // Create the IssueTypesDAO object
    IssueTypesDAO issueTypesDAO(db);

    // Create a new issue type
    IssueType issueType1(0, "Bug");
    issueTypesDAO.create(issueType1);

    // List all issue types
    std::vector<std::shared_ptr<IssueType>> issueTypes = issueTypesDAO.list();
    for (auto& issueType : issueTypes) {
        std::cout << "Issue Type ID: " << issueType->getId() << ", Issue Type Name: " << issueType->getName() << std::endl;
    }

    // Update the name of the issue type
    issueType1.setName("Feature");
    issueTypesDAO.update(issueType1);

    // Delete the issue type
   // issueTypesDAO.del(issueType1.getId());

    // List all issue types again
    issueTypes = issueTypesDAO.list();
    for (auto& issueType : issueTypes) {
        std::cout << "Issue Type ID: " << issueType->getId() << ", Issue Type Name: " << issueType->getName() << std::endl;
    }

    // Get an issue type by ID
    std::shared_ptr<IssueType> issueType = issueTypesDAO.getIssueType(1);
    if (issueType != nullptr) {
        std::cout << "Issue Type ID: " << issueType->getId() << ", Issue Type Name: " << issueType->getName() << std::endl;
    }


    return 0;
}