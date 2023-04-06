#include <iostream>
#include "credentials.h"
#include "database.h"
#include "ProjectDAO.h"
#include "Project.h"
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
    
    // Create a new ProjectsDAO object
    ProjectsDAO dao(db);

    // Create a new project and insert it into the database
    Project project1(0, "Project 1");
    dao.create(project1);
    std::cout << "Created project with ID: " << project1.getId() << std::endl;

    // Read the project from the database
    std::shared_ptr<Project> project1Ptr = dao.getProject(project1.getId());
    if (project1Ptr != nullptr) {
        std::cout << "Project name: " << project1Ptr->getName() << std::endl;
    }
    else {
        std::cout << "Project not found." << std::endl;
    }

    // Update the name of the project in the database
    project1.setName("Project 1 Updated");
    dao.update(project1);

    // Read the project from the database again to verify the update
    project1Ptr = dao.getProject(project1.getId());
    if (project1Ptr != nullptr) {
        std::cout << "Project name: " << project1Ptr->getName() << std::endl;
    }
    else {
        std::cout << "Project not found." << std::endl;
    }

    // List all projects in the database
    std::vector<std::shared_ptr<Project>> projects = dao.list();
    std::cout << "List of projects:" << std::endl;
    for (const auto& project : projects) {
        std::cout << "  " << project->getName() << ", ID: " << project->getId() << std::endl;
    }

    // Delete the project from the database
    dao.del(project1.getId());
    std::cout << "Deleted project with ID: " << project1.getId() << std::endl;

    return 0;
}