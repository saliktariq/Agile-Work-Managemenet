#ifndef ISSUES_H
#define ISSUES_H

#include <iostream>
#include <string>

class Issues {
public:

    int issue_id_;
    std::string summary_;
    std::string description_;
    std::string status_;
    std::string priority_;
    int assignee_;
    int project_id_;
    int issue_type_;
    int column_id_;
    double estimate_;


    Issues(int issue_id, std::string summary, std::string description, std::string status, std::string priority,
        int assignee, int project_id, int issue_type, int column_id, double estimate)
        : issue_id_(issue_id), summary_(summary), description_(description), status_(status), priority_(priority),
        assignee_(assignee), project_id_(project_id), issue_type_(issue_type), column_id_(column_id), estimate_(estimate) {}

    int getIssueId() const { return issue_id_; }
    void setIssueId(int issue_id) { issue_id_ = issue_id; }

    std::string getSummary() const { return summary_; }
    void setSummary(const std::string& summary) { summary_ = summary; }

    std::string getDescription() const { return description_; }
    void setDescription(const std::string& description) { description_ = description; }

    std::string getStatus() const { return status_; }
    void setStatus(const std::string& status) { status_ = status; }

    std::string getPriority() const { return priority_; }
    void setPriority(const std::string& priority) { priority_ = priority; }

    int getAssignee() const { return assignee_; }
    void setAssignee(int assignee) { assignee_ = assignee; }

    int getProjectId() const { return project_id_; }
    void setProjectId(int project_id) { project_id_ = project_id; }

    int getIssueType() const { return issue_type_; }
    void setIssueType(int issue_type) { issue_type_ = issue_type; }

    int getColumnId() const { return column_id_; }
    void setColumnId(int column_id) { column_id_ = column_id; }

    double getEstimate() const { return estimate_; }
    void setEstimate(double estimate) { estimate_ = estimate; }
};

#endif