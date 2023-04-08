
#ifndef ISSUES_TYPES_DAO_H
#define ISSUES_TYPES_DAO_H

#include "issue_types.h"
#include <memory>
#include <vector>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include "Database.h"

class IssueTypesDAO {
private:
    std::shared_ptr<Database> db_;

public:
    IssueTypesDAO(std::shared_ptr<Database> db) : db_(db) {}

    void create(IssueType& issueType) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO issue_types (issue_type_name) VALUES (?)");
            pstmt->setString(1, issueType.getName());
            pstmt->execute();
            delete pstmt;

            // Retrieve the last inserted ID
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                issueType.setId(rs->getInt(1));
            }
            delete rs;
            delete stmt;

            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating issue type: " << e.what() << std::endl;
        }
    }

    void update(const IssueType& issueType) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE issue_types SET issue_type_name = ? WHERE issue_type_id = ?");
            pstmt->setString(1, issueType.getName());
            pstmt->setInt(2, issueType.getId());
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating issue type: " << e.what() << std::endl;
        }
    }

    // Delete an issue type by ID
    void del(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM issue_types WHERE issue_type_id = ?");
            pstmt->setInt(1, id);
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting issue type: " << e.what() << std::endl;
        }
    }

    // List all issue types
    std::vector<std::shared_ptr<IssueType>> list() {
        std::vector<std::shared_ptr<IssueType>> issueTypes;

        try {
            sql::Connection* con = db_->getConnection();
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT * FROM issue_types");

            while (rs->next()) {
                int id = rs->getInt("issue_type_id");
                std::string name = rs->getString("issue_type_name");
                std::shared_ptr<IssueType> issueType = std::make_shared<IssueType>(id, name);
                issueTypes.push_back(issueType);
            }

            delete rs;
            delete stmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing issue types: " << e.what() << std::endl;
        }

        return issueTypes;
    }



    // Get an issue type by ID
    std::shared_ptr<IssueType> getIssueType(int id) {
    try {
        sql::Connection* con = db_->getConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM issue_types WHERE issue_type_id = ?");
        pstmt->setInt(1, id);
        sql::ResultSet* rs = pstmt->executeQuery();

        if (rs->next()) {
            std::shared_ptr<IssueType> issueType = std::make_shared<IssueType>(
                rs->getInt("issue_type_id"),
                rs->getString("issue_type_name")
            );
            delete rs;
            delete pstmt;
            db_->disconnect();
            return issueType;
        }
        else {
            delete rs;
            delete pstmt;
            db_->disconnect();
            return nullptr;
        }
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Error getting issue type: " << e.what() << std::endl;
        return nullptr;
    }
}

            };
#endif