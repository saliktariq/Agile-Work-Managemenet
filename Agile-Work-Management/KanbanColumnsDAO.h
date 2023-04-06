#ifndef KANBAN_COLUMNS_DAO_H
#define KANBAN_COLUMNS_DAO_H

#include "kanban_columns.h"
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include "Database.h"

class KanbanColumnsDAO {
private:
    std::shared_ptr<Database> db_;

public:
    KanbanColumnsDAO(std::shared_ptr<Database> db) : db_(db) {}

    void create(KanbanColumn& column) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO kanban_columns (column_name, board_id, column_position) VALUES (?, ?, ?)");
            pstmt->setString(1, column.getName());
            pstmt->setInt(2, column.getBoardId());
            pstmt->setInt(3, column.getPosition());
            pstmt->execute();
            delete pstmt;

            // Retrieve the last inserted ID
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                column.setId(rs->getInt(1));
            }
            delete rs;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating kanban column: " << e.what() << std::endl;
        }
    }

    void update(const KanbanColumn& column) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE kanban_columns SET column_name = ?, board_id = ?, column_position = ? WHERE column_id = ?");
            pstmt->setString(1, column.getName());
            pstmt->setInt(2, column.getBoardId());
            pstmt->setInt(3, column.getPosition());
            pstmt->setInt(4, column.getId());
            pstmt->execute();
            delete pstmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating kanban column: " << e.what() << std::endl;
        }
    }

    // Delete a kanban column by ID
    void del(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM kanban_columns WHERE column_id = ?");
            pstmt->setInt(1, id);
            pstmt->execute();
            delete pstmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting kanban column: " << e.what() << std::endl;
        }
    }

    std::vector<std::shared_ptr<KanbanColumn>> list(int boardId) {
        std::vector<std::shared_ptr<KanbanColumn>> columns;

        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT column_id, column_name, column_position FROM kanban_columns WHERE board_id = ?");
            pstmt->setInt(1, boardId);
            sql::ResultSet* rs = pstmt->executeQuery();

            while (rs->next()) {
                int columnId = rs->getInt("column_id");
                std::string name = rs->getString("column_name");
                int position = rs->getInt("column_position");
                std::shared_ptr<KanbanColumn> column = std::make_shared<KanbanColumn>(columnId, name, boardId, position);
                columns.push_back(column);
            }

            delete rs;
            delete pstmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing Kanban columns: " << e.what() << std::endl;
        }

        return columns;
    }

    std::shared_ptr<KanbanColumn> getColumn(int columnId) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM kanban_columns WHERE column_id = ?");
            pstmt->setInt(1, columnId);
            sql::ResultSet* rs = pstmt->executeQuery();

            if (rs->next()) {
                std::shared_ptr<KanbanColumn> column =
                    std::make_shared<KanbanColumn>(rs->getInt("column_id"),
                        rs->getString("column_name"),
                        rs->getInt("board_id"),
                        rs->getInt("column_position"));
                delete rs;
                delete pstmt;

                return column;
            }
            else {
                delete rs;
                delete pstmt;
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error getting column: " << e.what() << std::endl;
            return nullptr;
        }
    }


};

#endif
