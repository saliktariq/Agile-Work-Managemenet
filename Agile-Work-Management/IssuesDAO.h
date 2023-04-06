#ifndef ISSUESDAO_H
#define ISSUESDAO_H

#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "issues.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

class IssuesDAO {
private:
    Database& db_;

public:
    IssuesDAO(Database& db) : db_(db) {}

    void createIssue(Issues& issue) {
        try {
            sql::Connection* conn = db_.getConnection();
            sql::PreparedStatement* pstmt =
                conn->prepareStatement("INSERT INTO issues (summary, description, status, priority, assignee, project_id, issue_type, column_id, estimate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
            pstmt->setString(1, issue.getSummary());
            pstmt->setString(2, issue.getDescription());
            pstmt->setString(3, issue.getStatus());
            pstmt->setString(4, issue.getPriority());
            if (issue.getAssignee() != 0) {
                pstmt->setInt(5, issue.getAssignee());
            }
            else {
                pstmt->setNull(5, sql::DataType::INTEGER);
            }
            pstmt->setInt(6, issue.getProjectId());
            pstmt->setInt(7, issue.getIssueType());
            pstmt->setInt(8, issue.getColumnId());
            if (issue.getEstimate() != 0.0) {
                pstmt->setDouble(9, issue.getEstimate());
            }
            else {
                pstmt->setNull(9, sql::DataType::FLOAT);
            }
            pstmt->execute();
            issue.setIssueId(conn->getLastInsertID());
            delete pstmt;
            db_.disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating issue: " << e.what() << std::endl;
        }
    }

    void updateIssue(const Issues& issue) {
        try {
            sql::Connection* conn = db_.getConnection();
            sql::PreparedStatement* pstmt =
                conn->prepareStatement("UPDATE issues SET summary = ?, description = ?, status = ?, priority = ?, assignee = ?, project_id = ?, issue_type = ?, column_id = ?, estimate = ? WHERE issue_id = ?");
            pstmt->setString(1, issue.getSummary());
            pstmt->setString(2, issue.getDescription());
            pstmt->setString(3, issue.getStatus());
            pstmt->setString(4, issue.getPriority());
            if (issue.getAssignee() != 0) {
                pstmt->setInt(5, issue.getAssignee());
            }
            else {
                pstmt->setNull(5, sql::DataType::INTEGER);
            }
            pstmt->setInt(6, issue.getProjectId());
            pstmt->setInt(7, issue.getIssueType());
            pstmt->setInt(8, issue.getColumnId());
            if (issue.getEstimate() != 0.0) {
                pstmt->setDouble(9, issue.getEstimate());
            }
            else {
                pstmt->setNull(9, sql::DataType::FLOAT);
            }
            pstmt->setInt(10, issue.getIssueId());
            pstmt->execute();
            delete pstmt;
            db_.disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating issue: " << e.what() << std::endl;
        }
    }


};
#endif