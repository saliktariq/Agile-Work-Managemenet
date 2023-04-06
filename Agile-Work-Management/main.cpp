#include <iostream>
#include "credentials.h"
#include "database.h"
#include "ProjectDAO.h"
#include "Project.h"
//#include "kanban_boards.h"
#include "KanbanBoardsDAO.h"
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



    return 0;
}