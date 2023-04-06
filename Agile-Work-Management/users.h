#ifndef USERS_H
#define USERS_H

#include <string>

class User {
private:
    int id_;
    std::string username_;
    std::string fullName_;
    std::string email_;
    std::string role_;

public:
    User(int id, const std::string& username, const std::string& fullName, const std::string& email, const std::string& role)
        : id_(id), username_(username), fullName_(fullName), email_(email), role_(role) {}
    int getId() const {
        return id_;
    }

    void setId(int id) {
        id_ = id;
    }

    const std::string& getUsername() const {
        return username_;
    }

    void setUsername(const std::string& username) {
        username_ = username;
    }

    const std::string& getFullName() const {
        return fullName_;
    }

    void setFullName(const std::string& fullName) {
        fullName_ = fullName;
    }

    const std::string& getEmail() const {
        return email_;
    }

    void setEmail(const std::string& email) {
        email_ = email;
    }

    const std::string& getRole() const {
        return role_;
    }

    void setRole(const std::string& role) {
        role_ = role;
    }
};
#endif
