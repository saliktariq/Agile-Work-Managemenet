#ifndef KANBAN_BOARDS_DAO_H
#define KANBAN_BOARDS_DAO_H

#include "kanban_boards.h"
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include "Database.h"

class KanbanBoardsDAO {
private:
    std::shared_ptr<Database> db_;

public:
    KanbanBoardsDAO(std::shared_ptr<Database> db) : db_(db) {}

    void create(KanbanBoard& board) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO kanban_boards (board_name, project_id, start_date, end_date) VALUES (?, ?, ?, ?)");
            pstmt->setString(1, board.getName());
            pstmt->setInt(2, board.getProjectId());
            pstmt->setString(3, board.getStartDate());
            pstmt->setString(4, board.getEndDate());
            pstmt->execute();
            delete pstmt;

            // Retrieve the last inserted ID
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                board.setId(rs->getInt(1));
            }
            delete rs;
            delete stmt;


        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating kanban board: " << e.what() << std::endl;
        }
    }

    void update(const KanbanBoard& board) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE kanban_boards SET board_name = ?, project_id = ?, start_date = ?, end_date = ? WHERE board_id = ?");
            pstmt->setString(1, board.getName());
            pstmt->setInt(2, board.getProjectId());
            pstmt->setString(3, board.getStartDate());
            pstmt->setString(4, board.getEndDate());
            pstmt->setInt(5, board.getId());
            pstmt->execute();
            delete pstmt;

        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating kanban board: " << e.what() << std::endl;
        }
    }

    // Delete a kanban board by ID
    void del(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM kanban_boards WHERE board_id = ?");
            pstmt->setInt(1, id);
            pstmt->execute();
            delete pstmt;

        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting kanban board: " << e.what() << std::endl;
        }
    }

    std::vector<std::shared_ptr<KanbanBoard>> list(int projectId) {
        std::vector<std::shared_ptr<KanbanBoard>> boards;

        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT board_id, board_name, project_id, start_date, end_date FROM kanban_boards WHERE project_id = ?");
            pstmt->setInt(1, projectId);
            sql::ResultSet* rs = pstmt->executeQuery();

            while (rs->next()) {
                int boardId = rs->getInt("board_id");
                std::string name = rs->getString("board_name");
                int projectId = rs->getInt("project_id");
                std::string startDate = rs->getString("start_date");
                std::string endDate = rs->getString("end_date");
                std::shared_ptr<KanbanBoard> board =
                    std::make_shared<KanbanBoard>(boardId, name, projectId, startDate, endDate);
                boards.push_back(board);
            }

            delete rs;
            delete pstmt;

        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing Kanban boards: " << e.what() << std::endl;
        }

        return boards;
    }


    std::shared_ptr<KanbanBoard> getBoard(int boardId) {
        // Construct a SQL statement to retrieve the kanban board by ID
        std::string sql = "SELECT board_id, board_name, project_id, start_date, end_date FROM kanban_boards WHERE board_id = ?";

        try {
            // Create a prepared statement with the SQL statement
            sql::Connection* connection_ = db_->getConnection();
            std::unique_ptr<sql::PreparedStatement> stmt(connection_->prepareStatement(sql));
            stmt->setInt(1, boardId);

            // Execute the query and retrieve the result set
            std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

            // Check if a row was returned
            if (result->next()) {
                // Create a new KanbanBoard object with the values from the row
                int id = result->getInt("board_id");
                std::string name = result->getString("board_name");
                int projectId = result->getInt("project_id");
                std::string startDate = result->getString("start_date");
                std::string endDate = result->getString("end_date");
                std::shared_ptr<KanbanBoard> board = std::make_shared<KanbanBoard>(id, name, projectId, startDate, endDate);
                return board;
            }
            else {
                // Return a null shared pointer if the board was not found
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error retrieving kanban board: " << e.what() << std::endl;
            return nullptr;
        }
    }


};

#endif