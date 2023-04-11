#ifndef USERS_DAO_H
#define USERS_DAO_H

#include "users.h"
#include <memory>
#include <vector>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include "Database.h"

class UsersDAO {
private:
    std::shared_ptr<Database> db_;

public:
    UsersDAO(std::shared_ptr<Database> db) : db_(db) {}
    void create(User& user) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO users (user_name, full_name, user_email, role) VALUES (?, ?, ?, ?)");
            pstmt->setString(1, user.getUsername());
            pstmt->setString(2, user.getFullName());
            pstmt->setString(3, user.getEmail());
            pstmt->setString(4, user.getRole());
            pstmt->execute();
            delete pstmt;

            // Retrieve the last inserted ID
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
            if (rs->next()) {
                user.setId(rs->getInt(1));
            }
            delete rs;
            delete stmt;

            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error creating user: " << e.what() << std::endl;
        }
    }

    void update(const User& user) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE users SET user_name = ?, full_name = ?, user_email = ?, role = ? WHERE user_id = ?");
            pstmt->setString(1, user.getUsername());
            pstmt->setString(2, user.getFullName());
            pstmt->setString(3, user.getEmail());
            pstmt->setString(4, user.getRole());
            pstmt->setInt(5, user.getId());
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error updating user: " << e.what() << std::endl;
        }
    }

    // Delete a user by ID
    void del(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM users WHERE user_id = ?");
            pstmt->setInt(1, id);
            pstmt->execute();
            delete pstmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error deleting user: " << e.what() << std::endl;
        }
    }

    // List all users
    std::vector<std::shared_ptr<User>> list() {
        std::vector<std::shared_ptr<User>> users;

        try {
            sql::Connection* con = db_->getConnection();
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT * FROM users");

            while (rs->next()) {
                int id = rs->getInt("user_id");
                std::string userName = rs->getString("user_name");
                std::string fullName = rs->getString("full_name");
                std::string email = rs->getString("user_email");
                std::string role = rs->getString("role");
                std::shared_ptr<User> user = std::make_shared<User>(id, userName, fullName, email, role);
                users.push_back(user);
            }

            delete rs;
            delete stmt;
            db_->disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error listing users: " << e.what() << std::endl;
        }

        return users;
    }

    // Get a user by ID
    std::shared_ptr<User> getUser(int id) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM users WHERE user_id = ?");
            pstmt->setInt(1, id);
            sql::ResultSet* rs = pstmt->executeQuery();

            if (rs->next()) {
                std::shared_ptr<User> user = std::make_shared<User>(
                    rs->getInt("user_id"),
                    rs->getString("user_name"),
                    rs->getString("full_name"),
                    rs->getString("user_email"),
                    rs->getString("role")
                );
                delete rs;
                delete pstmt;
                db_->disconnect();
                return user;
            }
            else {
                delete rs;
                delete pstmt;
                db_->disconnect();
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error getting user: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // Get the ID of the last inserted row in the users table
    int getLastID() {
        try {
            sql::Connection* con = db_->getConnection();
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");

            if (rs->next()) {
                int lastID = rs->getInt(1);
                delete rs;
                delete stmt;
                db_->disconnect();
                return lastID;
            }
            else {
                delete rs;
                delete stmt;
                db_->disconnect();
                return -1; // or some other error code to indicate failure
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error getting last ID: " << e.what() << std::endl;
            return -1; // or some other error code to indicate failure
        }
    }




    //Get a user by username
    std::shared_ptr<User> getUserByUsername(const std::string& username) {
        try {
            sql::Connection* con = db_->getConnection();
            sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM users WHERE user_name = ?");
            pstmt->setString(1, username);
            sql::ResultSet* rs = pstmt->executeQuery();

            if (rs->next()) {
                std::shared_ptr<User> user = std::make_shared<User>(
                    rs->getInt("user_id"),
                    rs->getString("user_name"),
                    rs->getString("full_name"),
                    rs->getString("user_email"),
                    rs->getString("role")
                );
                delete rs;
                delete pstmt;
                db_->disconnect();
                return user;
            }
            else {
                delete rs;
                delete pstmt;
                db_->disconnect();
                return nullptr;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error getting user by username: " << e.what() << std::endl;
            return nullptr;
        }
    }

};
#endif
