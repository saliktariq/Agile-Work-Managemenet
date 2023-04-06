#ifndef ISSUE_TYPES_H
#define ISSUE_TYPES_H

#include <string>

class IssueType {
private:
    int id_;
    std::string name_;

public:
    IssueType(int id, std::string name)
        : id_(id), name_(name) {}

    int getId() const { return id_; }
    void setId(int id) { id_ = id; }

    std::string getName() const { return name_; }
    void setName(std::string name) { name_ = name; }
};

#endif
