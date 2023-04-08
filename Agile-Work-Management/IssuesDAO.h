#ifndef ISSUESDAO_H
#define ISSUESDAO_H

#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "issues.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class IssuesDAO {
private:
    std::shared_ptr<Database> db_;

public:
    IssuesDAO(std::shared_ptr<Database> db) : db_(db) {}

    void createIssue(Issues& issue) {
        try {
            sql::Connection* con = db_->getConnection();
            // Insert the new issue and retrieve the last inserted ID
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO issues (summary, description, status, priority, assignee, project_id, issue_type, column_id, estimate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
            pstmt->setString(1, issue.summary_);
            pstmt->setString(2, issue.description_);
            pstmt->setString(3, issue.status_);
            pstmt->setString(4, issue.priority_);
            pstmt->setInt(5, issue.assignee_);
            pstmt->setInt(6, issue.project_id_);
            pstmt->setInt(7, issue.issue_type_);
            pstmt->setInt(8, issue.column_id_);
            pstmt->setDouble(9, issue.estimate_);
            pstmt->execute();

            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                issue.setIssueId(rs->getInt(1));
            }

            delete rs;
            delete stmt;
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating issue: " << e.what() << std::endl;
        }
    }

    void updateIssue(const Issues& issue) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt =
                con->prepareStatement("UPDATE issues SET summary = ?, description = ?, status = ?, priority = ?, assignee = ?, project_id = ?, issue_type = ?, column_id = ?, estimate = ? WHERE issue_id = ?");
            pstmt->setString(1, issue.summary_);
            pstmt->setString(2, issue.description_);
            pstmt->setString(3, issue.status_);
            pstmt->setString(4, issue.priority_);
            if (issue.assignee_ != 0) {
                pstmt->setInt(5, issue.assignee_);
            }
            else {
                pstmt->setNull(5, sql::DataType::INTEGER);
            }
            pstmt->setInt(6, issue.project_id_);
            pstmt->setInt(7, issue.issue_type_);
            pstmt->setInt(8, issue.column_id_);
            pstmt->setDouble(9, issue.estimate_);
            //if (issue.estimate_ != 0.0) {
            //    pstmt->setDouble(9, issue.estimate_);
            //}
            //else {
            //    pstmt->setDouble(9, 0);
            //}
            pstmt->setInt(10, issue.issue_id_);
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating issue: " << e.what() << std::endl;
        }
    }


    void deleteIssue(int issue_id) {
        try {
            sql::Connection* conn = db_->getConnection();
            sql::PreparedStatement* pstmt =
                conn->prepareStatement("DELETE FROM issues WHERE issue_id = ?");
            pstmt->setInt(1, issue_id);
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting issue: " << e.what() << std::endl;
        }
    }

    std::vector<std::shared_ptr<Issues>> listIssues(int project_id) {
        std::vector<std::shared_ptr<Issues>> issuesList;

        try {
            sql::Connection* conn = db_->getConnection();
            sql::PreparedStatement* pstmt =
                conn->prepareStatement("SELECT * FROM issues WHERE project_id = ?");
            pstmt->setInt(1, project_id);
            sql::ResultSet* rs = pstmt->executeQuery();

            while (rs->next()) {
                int issueId = rs->getInt("issue_id");
                std::string summary = rs->getString("summary");
                std::string description = rs->getString("description");
                std::string status = rs->getString("status");
                std::string priority = rs->getString("priority");
                int assignee = rs->getInt("assignee");
                int project = rs->getInt("project_id");
                int issueType = rs->getInt("issue_type");
                int columnId = rs->getInt("column_id");
                double estimate = rs->getDouble("estimate");
                std::shared_ptr<Issues> issue = std::make_shared<Issues>(issueId, summary, description, status, priority, assignee, project, issueType, columnId, estimate);
                issuesList.push_back(issue);
            }

            delete rs;
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing issues: " << e.what() << std::endl;
        }

        return issuesList;
    }

    std::shared_ptr<Issues> getIssueById(int issue_id) {
        try {
            sql::Connection* conn = db_->getConnection();
            sql::PreparedStatement* pstmt =
                conn->prepareStatement("SELECT * FROM issues WHERE issue_id = ?");
            pstmt->setInt(1, issue_id);
            sql::ResultSet* rs = pstmt->executeQuery();

            if (rs->next()) {
                std::string summary = rs->getString("summary");
                std::string description = rs->getString("description");
                std::string status = rs->getString("status");
                std::string priority = rs->getString("priority");
                int assignee = rs->getInt("assignee");
                int project = rs->getInt("project_id");
                int issueType = rs->getInt("issue_type");
                int columnId = rs->getInt("column_id");
                double estimate = rs->getDouble("estimate");
                std::shared_ptr<Issues> issue = std::make_shared<Issues>(issue_id, summary, description, status, priority, assignee, project, issueType, columnId, estimate);
                delete rs;
                delete pstmt;
                db_->disconnect();
                return issue;
            }
            else {
                delete rs;
                delete pstmt;
                db_->disconnect();
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error getting issue: " << e.what() << std::endl;
            return nullptr;
        }
    }

};
#endif
