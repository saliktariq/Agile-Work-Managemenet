#ifndef KANBAN_BOARDS_H
#define KANBAN_BOARDS_H

#include <string>
#include <memory>

class KanbanBoard {
private:
    int id_;
    std::string name_;
    int project_id_;
    std::string start_date_;
    std::string end_date_;

public:
    KanbanBoard() : id_(0), project_id_(0) {}

    //KanbanBoard(int id, const std::string& name, int project_id, const std::string& start_date, const std::string& end_date)
    //    : id_(id), name_(name), project_id_(project_id), start_date_(start_date), end_date_(end_date) {}

    KanbanBoard(int id, const std::string& name, int project_id, const std::string& start_date, const std::string& end_date)
        : id_(id), name_(name), project_id_(project_id), start_date_(start_date), end_date_(end_date) {}

    int getId() const { return id_; }
    void setId(int id) { id_ = id; }

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    int getProjectId() const { return project_id_; }
    void setProjectId(int project_id) { project_id_ = project_id; }

    const std::string& getStartDate() const { return start_date_; }
    void setStartDate(const std::string& start_date) { start_date_ = start_date; }

    const std::string& getEndDate() const { return end_date_; }
    void setEndDate(const std::string& end_date) { end_date_ = end_date; }


    std::vector<std::pair<std::string, std::string>> getAllFields() const {
        std::vector<std::pair<std::string, std::string>> fields;
        fields.emplace_back("ID", std::to_string(id_));
        fields.emplace_back("Name", name_);
        fields.emplace_back("Project ID", std::to_string(project_id_));
        fields.emplace_back("Start Date", start_date_);
        fields.emplace_back("End Date", end_date_);
        return fields;
    }
};

#endif
