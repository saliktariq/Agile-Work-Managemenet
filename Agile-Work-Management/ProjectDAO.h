#include "Project.h"
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include "database.h"

class ProjectsDAO {
private:
    std::shared_ptr<Database> db_;

public:
    ProjectsDAO(std::shared_ptr<Database> db) : db_(db) {}

    void create(Project& project) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO projects (project_name) VALUES (?)");
            pstmt->setString(1, project.getName());
            pstmt->execute();
            delete pstmt;

            // Retrieve the last inserted ID
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                project.setId(rs->getInt(1));
            }
            delete rs;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating project: " << e.what() << std::endl;
        }
    }

    void update(const Project& project) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE projects SET project_name = ? WHERE project_id = ?");
            pstmt->setString(1, project.getName());
            pstmt->setInt(2, project.getId());
            pstmt->execute();
            delete pstmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating project: " << e.what() << std::endl;
        }
    }

    // Delete a project by ID
    void del(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM projects WHERE project_id = ?");
            pstmt->setInt(1, id);
            pstmt->execute();
            delete pstmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting project: " << e.what() << std::endl;
        }
    }

    // List all projects
    std::vector<std::shared_ptr<Project>> list() {
        std::vector<std::shared_ptr<Project>> projects;
        try {
            sql::Connection* con = db_->getConnection();
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT project_id, project_name FROM projects");
            while (rs->next()) {
                int id = rs->getInt("project_id");
                std::string name = rs->getString("project_name");
                projects.push_back(std::make_shared<Project>(id, name));
            }
            delete rs;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing projects: " << e.what() << std::endl;
        }
        return projects;
    }

    std::shared_ptr<Project> getProject(int projectId) {
        // Construct a SQL statement to retrieve the project by ID
        std::string sql = "SELECT project_id, project_name FROM projects WHERE project_id = ?";

        try {
            // Create a prepared statement with the SQL statement
            sql::Connection* connection_ = db_->getConnection();
            std::unique_ptr<sql::PreparedStatement> stmt(connection_->prepareStatement(sql));
            stmt->setInt(1, projectId);

            // Execute the query and retrieve the result set
            std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

            // Check if a row was returned
            if (result->next()) {
                // Create a new Project object with the values from the row
                int id = result->getInt("project_id");
                std::string name = result->getString("project_name");
                std::shared_ptr<Project> project = std::make_shared<Project>(id, name);
                return project;
            }
            else {
                // Return a null shared pointer if the project was not found
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error retrieving project: " << e.what() << std::endl;
            return nullptr;
        }
    }

};
