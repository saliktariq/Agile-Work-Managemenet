/*while (true) {
            cout << "Board columns Menu:" << endl;
            cout << "1. View columns with issues" << endl;
            cout << "2. Select a column" << endl;
            cout << "3. Back to boards Menu" << endl;
            cin >> userChoice;

            if (userChoice == 3) {
                break;
            } else {
                KanbanColumn c;
                vector <shared_ptr<KanbanColumn>> columns;
                switch (userChoice) {
                    case 2:
                        int columnId;
                        cout << "Enter the column ID: ";
                        cin >> columnId;
                        cout << endl;

                        c = *kanbanColumnsDAO.getColumn(columnId);

                    case 1:
                        int boardId;
                        cout << "Enter the board ID: ";
                        cin >> boardId;
                        cout << endl;

                        columns = kanbanColumnsDAO.list(boardId);
                        cout << "COLUMNS\n";
                        for (int i = 0; i < columns.size(); i++) {
                            KanbanColumn temp = *columns[i].get();
                            cout << temp.getName() << endl;
                            cout << "Found at board " << temp.getBoardId() << endl;
                            cout << temp.getPosition() << endl;
                        }
                        cout << endl;
                }
            }
            
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