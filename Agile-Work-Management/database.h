#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>

class Database {
private:
    std::string host_;
    std::string user_;
    std::string password_;
    std::string database_;

    std::unique_ptr<sql::Connection> connection_;


public:

    Database(const std::string& host, const std::string& username, const std::string& password, const std::string& databaseName)
        : host_(host), user_(username), password_(password), database_(databaseName) {}

    void connect() {
        try {
            sql::Driver* driver = get_driver_instance();
            std::string connectionString = "tcp://" + host_ + ";username=" + user_ + ";password=" + password_ + ";database=" + database_;
            std::string url = "tcp://" + host_;
            std::string user = user_;
            std::string password = password_;
            connection_ = std::unique_ptr<sql::Connection>(driver->connect(url, user, password));
            connection_->setSchema(database_);
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error connecting to database: " << e.what() << std::endl;
        }
    }

    void disconnect() {
        if (connection_ != nullptr) {
            connection_->close();
            connection_.reset();
        }
    }

    sql::Connection* getConnection() {
        connect();
        return connection_.get();
    }

    void reset() {
        try {
            sql::Connection* con = getConnection();
            sql::Statement* stmt = con->createStatement();
            std::vector<std::string> tableNames = {"issues", "issue_types", "kanban_boards", "kanban_columns", "projects", "users" };
            for (const std::string& tableName : tableNames) {
                // Delete all rows from the table
                std::string deleteSql = "DELETE FROM " + tableName;
                stmt->execute(deleteSql);

                // Reset the auto_increment value to 0
                std::string resetSql = "ALTER TABLE " + tableName + " AUTO_INCREMENT=0";
                stmt->execute(resetSql);
            }
            delete stmt;
            disconnect();
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Error resetting database: " << e.what() << std::endl;
        }
    }

};
#endif