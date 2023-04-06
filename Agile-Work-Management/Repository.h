#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "credentials.h"
#include <memory>
#include <thread>
#include "database.h"
#include "IssuesDAO.h"
#include "IssuesTypesDAO.h"
#include "KanbanBoardsDAO.h"
#include "KanbanColumnsDAO.h"
#include "ProjectDAO.h"
#include "UsersDAO.h"


class Repository {

public:
    Repository() {}


    /* Database credentials*/
    std::string host = Credentials::LOCALHOST;
    std::string username = Credentials::USERNAME;
    std::string password = Credentials::PASSWORD;
    std::string databaseName = Credentials::DATABASE_NAME;

    /* Declaring and Instantiating database*/
    std::shared_ptr<Database> db_ = std::make_shared<Database>(host, username, password, databaseName);

    

    void createIssue(Issues& issue) {
        db_->connect();
        IssuesDAO dao(db_);
        dao.createIssue(issue);

    }

    void updateIssue(const Issues& issue) {
        db_->connect();
        IssuesDAO dao(db_);
        dao.updateIssue(issue);

    }

    void deleteIssue(int issue_id) {
        db_->connect();
        IssuesDAO dao(db_);
        dao.deleteIssue(issue_id);
    }

    std::vector<std::shared_ptr<Issues>> listIssues(int project_id) {
        db_->connect();
        IssuesDAO dao(db_);
        return dao.listIssues(project_id);

    }

    std::shared_ptr<Issues> getIssueById(int issue_id) {
        db_->connect();
        IssuesDAO dao(db_);
        return dao.getIssueById(issue_id);
    }

    void createIssueType(IssueType& issueType) {
        db_->connect();
        IssueTypesDAO dao(db_);
        dao.create(issueType);

    }

    void updateIssueType(const IssueType& issueType) {
        db_->connect();
        IssueTypesDAO dao(db_);
        dao.update(issueType);
    }

    void deleteIssueType(int id) {
        db_->connect();
        IssueTypesDAO dao(db_);
        dao.del(id);
    }

    std::vector<std::shared_ptr<IssueType>> listIssueTypes() {
        db_->connect();
        IssueTypesDAO dao(db_);
        return dao.list();

    }

    std::shared_ptr<IssueType> getIssueTypeById(int id) {
        db_->connect();
        IssueTypesDAO dao(db_);
        return dao.getIssueType(id);

    }



    std::vector<std::shared_ptr<KanbanBoard>> list(int projectId) {
        db_->connect();
        std::vector<std::shared_ptr<KanbanBoard>> boards;
        KanbanBoardsDAO dao(db_);
        return dao.list(projectId);
    }

    std::shared_ptr<KanbanBoard> getBoard(int boardId) {
        db_->connect();
        std::shared_ptr<KanbanBoard> board;
        KanbanBoardsDAO dao(db_);
        return dao.getBoard(boardId);
    }

    void createKanbanBoards(KanbanBoard& board) {
        db_->connect();
        KanbanBoardsDAO dao(db_);
        dao.create(board);

    }

    void updateKanbanBoards(const KanbanBoard& board) {
        db_->connect();
        KanbanBoardsDAO dao(db_);
        dao.update(board);

    }

    void delKanbanBoardById(int id) {
        db_->connect();
        KanbanBoardsDAO dao(db_);
        dao.del(id);
    }

    std::vector<std::shared_ptr<KanbanColumn>> listColumns(int boardId) {
        db_->connect();
        KanbanColumnsDAO dao(db_);
        return dao.list(boardId);
    }

    std::shared_ptr<KanbanColumn> getColumnById(int columnId) {
        db_->connect();
        KanbanColumnsDAO dao(db_);
        return dao.getColumn(columnId);
    }

    void createColumn(KanbanColumn& column) {
        db_->connect();
        KanbanColumnsDAO dao(db_);
        dao.create(column);

    }

    void updateColumn(const KanbanColumn& column) {
        db_->connect();
        KanbanColumnsDAO dao(db_);
        dao.update(column);
    }

    void deleteColumn(int id) {
        db_->connect();
        KanbanColumnsDAO dao(db_);
        dao.del(id);
    }

    void createProject(Project& project) {
        db_->connect();
        ProjectsDAO dao(db_);
        dao.create(project);

    }

    void updateProject(const Project& project) {
        db_->connect();
        ProjectsDAO dao(db_);
        dao.update(project);

    }

    void deleteProject(int id) {
        db_->connect();
        ProjectsDAO dao(db_);
        dao.del(id);

    }

    std::vector<std::shared_ptr<Project>> listProjects() {
        db_->connect();
        ProjectsDAO dao(db_);
        return dao.list();

    }

    std::shared_ptr<Project> getProjectById(int projectId) {
        db_->connect();
        ProjectsDAO dao(db_);
        return dao.getProject(projectId);
        
    }

    void createUser(User& user) {
        db_->connect();
        UsersDAO dao(db_);
        dao.create(user);

    }

    void updateUser(const User& user) {
        db_->connect();
        UsersDAO dao(db_);
        dao.update(user);

    }

    void deleteUser(int id) {
        db_->connect();
        UsersDAO dao(db_);
        dao.del(id);

    }


    
};

#endif
