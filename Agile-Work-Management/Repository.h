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

    ~Repository() {
        db_->disconnect();
    }


    /* Database credentials*/
    std::string host = Credentials::LOCALHOST;
    std::string username = Credentials::USERNAME;
    std::string password = Credentials::PASSWORD;
    std::string databaseName = Credentials::DATABASE_NAME;

    /* Declaring and Instantiating database*/
    //std::shared_ptr<Database> db_ = std::make_shared<Database>(host, username, password, databaseName);
    
    std::shared_ptr<Database> db_ = std::make_shared<Database>(host, username, password, databaseName);
    

    void createIssue(Issues& issue) {

        IssuesDAO dao(db_);
        dao.createIssue(issue);

    }

    void updateIssue(const Issues& issue) {

        IssuesDAO dao(db_);
        dao.updateIssue(issue);

    }

    void deleteIssue(int issue_id) {

        IssuesDAO dao(db_);
        dao.deleteIssue(issue_id);
    }

    std::vector<std::shared_ptr<Issues>> listIssues(int project_id) {

        IssuesDAO dao(db_);
        return dao.listIssues(project_id);

    }

    std::shared_ptr<Issues> getIssueById(int issue_id) {

        IssuesDAO dao(db_);
        return dao.getIssueById(issue_id);
    }

    void createIssueType(IssueType& issueType) {

        IssueTypesDAO dao(db_);
        dao.create(issueType);

    }

    void updateIssueType(const IssueType& issueType) {

        IssueTypesDAO dao(db_);
        dao.update(issueType);
    }

    void deleteIssueType(int id) {

        IssueTypesDAO dao(db_);
        dao.del(id);
    }

    std::vector<std::shared_ptr<IssueType>> listIssueTypes() {

        IssueTypesDAO dao(db_);
        return dao.list();

    }

    std::shared_ptr<IssueType> getIssueTypeById(int id) {

        IssueTypesDAO dao(db_);
        return dao.getIssueType(id);

    }



    std::vector<std::shared_ptr<KanbanBoard>> list(int projectId) {

        std::vector<std::shared_ptr<KanbanBoard>> boards;
        KanbanBoardsDAO dao(db_);
        return dao.list(projectId);
    }

    std::shared_ptr<KanbanBoard> getBoard(int boardId) {

        std::shared_ptr<KanbanBoard> board;
        KanbanBoardsDAO dao(db_);
        return dao.getBoard(boardId);
    }

    void createKanbanBoards(KanbanBoard& board) {

        KanbanBoardsDAO dao(db_);
        dao.create(board);

    }

    void updateKanbanBoards(const KanbanBoard& board) {

        KanbanBoardsDAO dao(db_);
        dao.update(board);

    }

    void delKanbanBoardById(int id) {

        KanbanBoardsDAO dao(db_);
        dao.del(id);
    }

    std::vector<std::shared_ptr<KanbanColumn>> listColumns(int boardId) {

        KanbanColumnsDAO dao(db_);
        return dao.list(boardId);
    }

    std::shared_ptr<KanbanColumn> getColumnById(int columnId) {

        KanbanColumnsDAO dao(db_);
        return dao.getColumn(columnId);
    }

    void createColumn(KanbanColumn& column) {

        KanbanColumnsDAO dao(db_);
        dao.create(column);

    }

    void updateColumn(const KanbanColumn& column) {

        KanbanColumnsDAO dao(db_);
        dao.update(column);
    }

    void deleteColumn(int id) {

        KanbanColumnsDAO dao(db_);
        dao.del(id);
    }

    void createProject(Project& project) {

        ProjectsDAO dao(db_);
        dao.create(project);

    }

    void updateProject(const Project& project) {

        ProjectsDAO dao(db_);
        dao.update(project);

    }

    void deleteProject(int id) {

        ProjectsDAO dao(db_);
        dao.del(id);

    }

    std::vector<std::shared_ptr<Project>> listProjects() {

        ProjectsDAO dao(db_);
        return dao.list();

    }

    std::shared_ptr<Project> getProjectById(int projectId) {

        ProjectsDAO dao(db_);
        return dao.getProject(projectId);
        
    }

    int getIDofLastProjectInserted() {
        // Retrieve all projects from the database
        std::vector<std::shared_ptr<Project>> projects = listProjects();

        // Check if the list is empty
        if (projects.empty()) {
            return 0; // No projects in the database
        }

        // Loop through all projects and find the last ID
        int lastID = 0;
        for (auto project : projects) {
            int projectID = project->getId();
            if (projectID > lastID) {
                lastID = projectID;
            }
        }

        return lastID;
    }

    void createUser(User& user) {

        UsersDAO dao(db_);
        dao.create(user);

    }

    void updateUser(const User& user) {

        UsersDAO dao(db_);
        dao.update(user);

    }

    void deleteUser(int id) {

        UsersDAO dao(db_);
        dao.del(id);

    }

    std::vector<std::shared_ptr<User>> listAllUsers() {
        UsersDAO dao(db_);
        return dao.list();
    }

    int getIDofLastUserInserted() {
        UsersDAO dao(db_);
        std::vector<std::shared_ptr<User>> users = listAllUsers();
        int lastId = 0;
        for (auto user : users) {
            int id = user->getId();
            if (id > lastId) {
                lastId = id;
            }
        }
        return lastId;
    }
    

    
};

#endif
