#ifndef ISSUES_H
#define ISSUES_H

#include <string>

class Issues {
private:
    int id_;
    std::string summary_;
    std::string description_;
    std::string status_;
    std::string priority_;
    int assignee_;
    int reporter_;
    int projectId_;
    int issueType_;
    int columnId_;
    float estimate_;

public:
    Issues(int id, std::string summary, std::string description, std::string status, std::string priority, int assignee, int reporter, int projectId, int issueType, int columnId, float estimate)
        : id_(id), summary_(summary), description_(description), status_(status), priority_(priority), assignee_(assignee), reporter_(reporter), projectId_(projectId), issueType_(issueType), columnId_(columnId), estimate_(estimate) {}

    int getId() const { return id_; }
    std::string getSummary() const { return summary_; }
    std::string getDescription() const { return description_; }
    std::string getStatus() const { return status_; }
    std::string getPriority() const { return priority_; }
    int getAssignee() const { return assignee_; }
    int getReporter() const { return reporter_; }
    int getProjectId() const { return projectId_; }
    int getIssueType() const { return issueType_; }
    int getColumnId() const { return columnId_; }
    float getEstimate() const { return estimate_; }

    void setId(int id) { id_ = id; }
    void setSummary(std::string summary) { summary_ = summary; }
    void setDescription(std::string description) { description_ = description; }
    void setStatus(std::string status) { status_ = status; }
    void setPriority(std::string priority) { priority_ = priority; }
    void setAssignee(int assignee) { assignee_ = assignee; }
    void setReporter(int reporter) { reporter_ = reporter; }
    void setProjectId(int projectId) { projectId_ = projectId; }
    void setIssueType(int issueType) { issueType_ = issueType; }
    void setColumnId(int columnId) { columnId_ = columnId; }
    void setEstimate(float estimate) { estimate_ = estimate; }
};

#endif
