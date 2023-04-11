// Project.h
#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>

class Project {
private:
    int id_;
    std::string name_;

public:
    Project() : id_(0) {}

    Project(int id, const std::string& name) : id_(id), name_(name) {}

    int getId() const { return id_; }
    void setId(int id) { id_ = id; }

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    std::vector<std::pair<std::string, std::string>> getAllFields() const {
        std::vector<std::pair<std::string, std::string>> fields;
        fields.emplace_back("ID", std::to_string(id_));
        fields.emplace_back("Name", name_);
        return fields;
    }

};

#endif
