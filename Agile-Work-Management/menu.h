#pragma once

#include <iostream>
#include "credentials.h"
#include "database.h"
#include "ProjectDAO.h"
#include "Project.h"
#include "KanbanColumnsDAO.h"
#include "KanbanBoardsDAO.h"
#include "UsersDAO.h"
#include "IssuesTypesDAO.h"
#include "issuesDAO.h"
#include "Repository.h"
#include "users.h"
#include <cstdlib>
#include <iomanip>


using namespace std;

void printFields(const std::string& header, const std::vector<std::pair<std::string, std::string>>& fields) {
    std::string separator(42, '-');
    std::string middle_separator(42, '-');
    middle_separator[13] = '+';

    std::cout << header << std::endl << separator << std::endl;

    for (const auto& field : fields) {
        std::cout << "| " << std::left << std::setw(10) << field.first << " | " << std::right << std::setw(25)
            << field.second << " |" << std::endl;
        std::cout << middle_separator << std::endl;
    }
}

template<typename T>
void printAllObjFields(const std::vector<std::shared_ptr<T>>& objects) {

    if (objects.empty()) {
        std::cout << "No objects to print." << std::endl;
        return;
    }
    // Get the field names from the first object
    const auto fields = objects[0]->getAllFields();

    // Print the headers
    for (const auto& field : fields) {
        std::cout << std::setw(15) << std::left << field.first << " | ";
    }
    std::cout << std::endl;

    // Print the rows
    for (const auto& object : objects) {
        const auto values = object->getAllFields();
        for (const auto& field : values) {
            std::cout << std::setw(15) << std::left << field.second << " | ";
        }
        std::cout << std::endl;
    }
}

string convertToMySQLDateFormat(const string& inputDate) {
    stringstream ss(inputDate);
    string day, month, year;

    getline(ss, day, '/');
    getline(ss, month, '/');
    getline(ss, year);

    return year + "-" + month + "-" + day;
}


void initializeKanbanColumns(Repository* repository, int boardId) {
    const std::vector<std::string> columnNames = { "TO DO", "IN PROGRESS", "DONE" };

    for (int columnPosition = 0; columnPosition < columnNames.size(); ++columnPosition) {
        std::string columnName = columnNames[columnPosition];
        KanbanColumn kc(0, columnName, boardId, columnPosition);
        std::cout << "Setting column name to \'" << columnName << "\' for board id: " << boardId << " at position: "
            << columnPosition << std::endl;
        //std::cout << "Pushing kanban column object to the database..." << std::endl;
        repository->createColumn(kc);
    }
}


int menu() {
    int userChoice;
    Repository* repo = new Repository();


    std::shared_ptr<User> current_user;
    std::shared_ptr<Project> current_project;
    std::shared_ptr<KanbanBoard> current_board;
    std::shared_ptr<KanbanColumn> current_column;

    // repo->resetDatabase();

    bool isAuthenticated = false;
    bool match = 0;


    while (!isAuthenticated) {
        cout << "\n\n1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cin >> userChoice;
        string username, full_name, email, role;
        User* user;

        switch (userChoice) {
        case 3:
            return 0; // Exit
        case 2:
            cout << "Enter username" << endl;
            cin >> username;

            //set current_user
            current_user = repo->getUserByUsername(username);

            if (!current_user) {
                cout << "User login failed or user not found" << endl;
                continue;
            }
            match = current_user->getUsername() == username;
            if (match) {
                cout << "User login successful!" << endl;
                printFields("User details :", current_user->getAllFields());
                isAuthenticated = true;
            }
            else {
                cout << "User login failed or user not found" << endl;
            }

            break;
        case 1:
            cout << "Enter username:" << endl;
            cin >> username;
            cin.ignore(); //ignore newline char
            cout << "Enter full name:" << endl;
            getline(cin, full_name);
            cout << "Enter email:" << endl;
            cin >> email;
            cout << "Enter role:" << endl;
            cin >> role;

            user = new User(0, username, full_name, email, role);
            //ID should be auto generated by mysql

            // Create user
            repo->createUser(*user);

            delete user;

            // fetch and verify created user
            current_user = repo->getUserByUsername(username);

            match = current_user->getUsername() == username;
            if (match) {
                cout << "User created successfuly!" << endl;
                printFields("User details :", current_user->getAllFields());
            }
            else {
                cout << "User creation failed" << endl;
            }

            break;
        default:
            break;
        }

    }

    bool projectSelected = false;
    while (!projectSelected) {
        cout << "\n\nProject Menu:" << endl;
        cout << "1. Create a new project" << endl;
        cout << "2. View existing projects" << endl;
        cout << "3. Select a project" << endl;
        cout << "4. Logout" << endl;
        cin >> userChoice;
        match = 0;
        string projectName;
        vector <shared_ptr<Project>> projects;
        switch (userChoice) {
        case 4:
            isAuthenticated = false;
            menu(); //needs testing
            exit(0);
        case 3:
            int projectId;
            cout << "Enter the project ID: ";
            cin >> projectId;
            cout << endl;
            current_project = repo->getProjectById(projectId);
            match = current_project->getId() == projectId;

            // if valid project selected:
            if (match) {
                cout << "Valid project selected" << endl;
                cout << "Project selected :" << current_project->getName() << endl << endl;
                projectSelected = true;
            }
            break;
        case 2:
            projects = repo->listProjects();
            cout << "\nPROJECTS\n";
            /*for (int i = 0; i < projects.size(); i++) {
                projects = projectDAO.list();
                Project temp = *projects[i].get();
                cout << temp.getId() << endl;
                cout << temp.getName() << endl;
            }
            cout << endl;*/
            printAllObjFields(projects);
            cout << endl;

            projectSelected = false;
            match = 0;
            break;
        case 1:
            cout << "Enter the project name: ";
            cin >> projectName;
            cout << endl;
            Project* p = new Project(0, projectName);
            repo->createProject(*p);
            delete p;

            current_project = repo->getProjectById(repo->getIDofLastProjectInserted());

            match = current_project->getName() == projectName;
            if (match) {
                cout << "Project " << current_project->getName() << "created successfuly!" << endl;
                printFields("Project details :", current_project->getAllFields());
                match = 0; // best to select the proj
            }
            else {
                cout << "Project creation failed" << endl;
            }
            break;
        }

    }


    match = 0;
    while (!match) {
        cout << "Board Menu:" << endl;
        cout << "1. Create a Kanban board" << endl;
        cout << "2. View kanban boards for selected project" << endl;
        cout << "3. Select a kanban board" << endl;
        cout << "4. Back to Project Menu" << endl;
        cin >> userChoice;


        int boardId, projectId;
        vector <shared_ptr<KanbanBoard>> boards;

        switch (userChoice) {
        case 4:
            break;
        case 3:
            cout << "Enter the board ID: ";
            cin >> boardId;
            cout << endl;

            current_board = repo->getBoardById(boardId);
            match = current_board->getId() == boardId;

            // if valid project selected:
            if (match) {
                cout << "Valid kanban board selected" << endl;
                cout << "Board selected :" << current_board->getName() << endl << endl;

            }
            else {
                cout << "Error selecting kanban board" << endl;
            }

            break;

        case 2:
            boards = repo->listBoardsByProjectId(current_project->getId());
            if (!boards.empty()) {
                cout << "BOARDS\n";
                for (const auto& board : boards) {
                    KanbanBoard temp = *board.get();
                    cout << "Board ID: " << temp.getId() << endl
                        << "Name: " << temp.getName() << endl
                        << "Started: " << temp.getStartDate() << endl
                        << "Ends: " << temp.getEndDate() << endl
                        << "Belongs to project: " << current_project->getName()
                        << "(" << temp.getProjectId() << ")" << endl
                        << endl;
                }
            }
            else {
                cout << "\nNo boards found for selected project, select 1 to create a board\n" << endl;
            }
            break;

        case 1:
            string name, startDate, endDate;

            cout << "Enter the board name: ";
            cin.ignore();
            getline(cin, name);
            cout << endl;

            cout << "Enter the start date of the board (format: DD/MM/YYYY): ";
            cin >> startDate;
            cout << endl;

            cout << "Enter the end of the board (format: DD/MM/YYYY): ";
            cin >> endDate;
            cout << endl;

            startDate = convertToMySQLDateFormat(startDate);
            endDate = convertToMySQLDateFormat(endDate);

            KanbanBoard* board = new KanbanBoard(0, name, current_project->getId(), startDate, endDate);
            //current_board = *kanbanBoardsDAO.create(board);
            repo->createKanbanBoards(*board);
            delete board;

            current_board = repo->getBoardById(repo->getIDofLastKanbanBoardInserted());

            match = current_board->getName() == name;
            if (match) {
                cout << "Board " << current_board->getName() << "created successfuly!" << endl;
                vector <pair<string, string>> boardFields = current_board->getAllFields();

                // Add the "Belongs to project" field to the boardFields vector
                string projectNameAndId =
                    current_project->getName() + " (ID: " + to_string(current_project->getId()) + ")";
                boardFields.emplace_back(make_pair("Belongs to project", projectNameAndId));

                printFields("Board details :", boardFields);

                match = 0; // best to select the board

                //get list of users
                //assign team lead
                cout << "initializing board columns..." << endl;
                // init to-do,in-progress,done columns
                initializeKanbanColumns(repo, current_board->getId());
            }
            else {
                cout << "Board creation failed" << endl;
            }
            break;
        }
    }

    match = 0;
    while (!match) {
        cout << "\n\nBoard columns Menu:" << endl;
        //cout << "1. View columns with issues" << endl;
        cout << "1. View columns" << endl;
        cout << "2. Select a column" << endl;
        cout << "3. Back to boards Menu" << endl;
        cin >> userChoice;


        shared_ptr <KanbanColumn> current_col;
        vector <shared_ptr<KanbanColumn>> columns;
        switch (userChoice) {
        case 3:
            break;
        case 2:
            int columnId;
            //cout << "Enter the column ID: \n1 = TO DO\n2 = IN PROGRESS\n3 = DONE\n=> ";
            cout << "Enter the column ID:" << endl;
            cin >> columnId;
            cout << endl;

            current_col = repo->getColumnById(columnId);

            match = current_col->getId() == columnId;

            // if valid column selected:
            if (match) {
                cout << "Valid kanban column selected" << endl;
                cout << "Column selected :" << current_col->getName() << "for board: " << current_board->getName() << endl << endl;

            }
            else {
                cout << "Error selecting kanban column" << endl;
            }
            break;

        case 1:

            columns = repo->listColumns(current_board->getId());
            cout << "COLUMNS\n";
            for (int i = 0; i < columns.size(); i++) {
                KanbanColumn temp = *columns[i].get();
                cout << "Column Name(pos:" << temp.getPosition() << "#ID:" << temp.getId() << "): " << temp.getName() << endl;
            }
            cout << "For board(#" << current_board->getId() << "): " << current_board->getName() << endl;
            cout << endl;
            break;
        }

    }

    /*
    while (true) {
                cout << "Issues Menu:" << endl;
                cout << "1. Create an issue" << endl;
                cout << "2. View issues" << endl;
                cout << "3. Edit an issue" << endl;
                cout << "4. Delete an issue" << endl;
                cout << "5. Update issue status" << endl; // or move column
                cout << "6. Assign issue to a team member" << endl;
                cout << "7. Set priority for an issue" << endl;
                cout << "8. Set estimate for an issue" << endl;
                cout << "9. Back to Board Menu" << endl;
                cin >> userChoice;

                IssuesDAO issuesDAO(db);

                if (userChoice == 9) {
                    break;
                } else {
                    int issueId;
                    switch (userChoice) {
                        case 1: {
                            // Create an issue
                            std::string summary, description, status, priority;
                            int assignee, project_id, issue_type, column_id;
                            float estimate;

                            cout << "Enter the issue summary: ";
                            cin.ignore();
                            getline(cin, summary);

                            cout << "Enter the issue description: ";
                            getline(cin, description);

                            cout << "Enter the issue status: ";
                            cin >> status;

                            cout << "Enter the issue priority: ";
                            cin >> priority;

                            cout << "Enter the assignee ID (0 if unassigned): ";
                            cin >> assignee;

                            cout << "Enter the project ID: ";
                            cin >> project_id;

                            cout << "Enter the issue type ID: ";
                            cin >> issue_type;

                            cout << "Enter the column ID: ";
                            cin >> column_id;

                            cout << "Enter the issue estimate: ";
                            cin >> estimate;

                            Issues issue(0, summary, description, status, priority, assignee, project_id, issue_type,
                                         column_id, estimate);
                            issuesDAO.createIssue(issue);
                            cout << "Issue created with ID: " << issue.getIssueId() << endl;
                            break;
                        }
                        case 2: {
                            // View issues
                            int project_id;
                            cout << "Enter the project ID: ";
                            cin >> project_id;

                            std::vector<std::shared_ptr<Issues>> issuesList = issuesDAO.listIssues(project_id);
                            for (const auto &issue: issuesList) {
                                cout << "Issue ID: " << issue->getIssueId() << ", Summary: " << issue->getSummary()
                                     << ", Status: " << issue->getStatus() << endl;
                            }
                            break;
                        }
                        case 3: {
                            // Edit an issue
                            int issue_id;
                            cout << "Enter the issue ID to edit: ";
                            cin >> issue_id;

                            std::shared_ptr<Issues> issue = issuesDAO.getIssueById(issue_id);
                            if (issue) {
                                std::string new_summary, new_description;
                                cin.ignore();
                                cout << "Enter the new summary (leave empty to keep the current summary): ";
                                getline(cin, new_summary);

                                cout << "Enter the new description (leave empty to keep the current description): ";
                                getline(cin, new_description);

                                if (!new_summary.empty()) {
                                    issue->setSummary(new_summary);
                                }
                                if (!new_description.empty()) {
                                    issue->setDescription(new_description);
                                }

                                issuesDAO.updateIssue(*issue);
                                cout << "Issue updated successfully." << endl;
                            } else {
                                cout << "Issue not found." << endl;
                            }
                            break;
                        }
                        case 4: {
                            // Delete an issue
                            int issue_id;
                            cout << "Enter the issue ID to delete: ";
                            cin >> issue_id;

                            issuesDAO.deleteIssue(issue_id);
                            cout << "Issue deleted successfully." << endl;
                            break;
                        }
                        case 5: {
                            // Update issue status
                            int issue_id;
                            std::string new_status;
                            cout << "Enter the issue ID to update the status: ";
                            cin >> issue_id;

                            cout << "Enter the new status: ";
                            cin >> new_status;

                            std::shared_ptr<Issues> issue = issuesDAO.getIssueById(issue_id);
                            if (issue) {
                                issue->setStatus(new_status);
                                issuesDAO.updateIssue(*issue);
                                cout << "Issue status updated successfully." << endl;
                            } else {
                                cout << "Issue not found." << endl;
                            }
                            break;
                        }
                        case 6: {
                            // Assign issue to a team member
                            int issue_id, new_assignee;
                            cout << "Enter the issue ID to assign: ";
                            cin >> issue_id;

                            cout << "Enter the new assignee ID: ";
                            cin >> new_assignee;

                            std::shared_ptr<Issues> issue = issuesDAO.getIssueById(issue_id);
                            if (issue) {
                                issue->setAssignee(new_assignee);
                                issuesDAO.updateIssue(*issue);
                                cout << "Issue assigned successfully." << endl;
                            } else {
                                cout << "Issue not found." << endl;
                            }
                            break;
                        }
                        case 7: {
                            // Set priority for an issue
                            int issue_id;
                            std::string new_priority;
                            cout << "Enter the issue ID to set priority: ";
                            cin >> issue_id;

                            cout << "Enter the new priority: ";
                            cin >> new_priority;

                            std::shared_ptr<Issues> issue = issuesDAO.getIssueById(issue_id);
                            if (issue) {
                                issue->setPriority(new_priority);
                                issuesDAO.updateIssue(*issue);
                                cout << "Issue priority updated successfully." << endl;
                            } else {
                                cout << "Issue not found." << endl;
                            }
                            break;
                        }
                        case 8: {
                            // Set estimate for an issue
                            int issue_id;
                            float new_estimate;
                            cout << "Enter the issue ID to set estimate: ";
                            cin >> issue_id;

                            cout << "Enter the new estimate: ";
                            cin >> new_estimate;

                            std::shared_ptr<Issues> issue = issuesDAO.getIssueById(issue_id);
                            if (issue) {
                                issue->setEstimate(new_estimate);
                                issuesDAO.updateIssue(*issue);
                                cout << "Issue estimate updated successfully." << endl;
                            } else {
                                cout << "Issue not found." << endl;
                            }
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
            } 
    
    */

    return 0;
}

