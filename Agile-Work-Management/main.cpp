#include <iostream>
#include "Repository.h"
#include <windows.h>
#include <sstream>
#include <iomanip>
#include "Tests.cpp"
using namespace std;


   
int main(){

    TEST t; // create an instance of Test class to call its functions
    int option;

    do {
        // display menu options
        cout << "Please choose an option:" << endl;
        cout << "1. Test User" << endl;
        cout << "2. Test Project" << endl;
        cout << "3. Test Kanban Boards" << endl;
        cout << "4. Test Kanban Column" << endl;
        cout << "5. Test Issue Type" << endl;
        cout << "6. Test Issues" << endl;
        cout << "7. Test Full functionality - Integrated Test" << endl;
        cout << "0. Exit" << endl;
        cin >> option;

        // call the selected function based on user's input
        switch (option) {
        case 1:
            t.Test_User();
            break;
        case 2:
            t.TEST_Project();
            break;
        case 3:
            t.TEST_KanbanBoards();
            break;
        case 4:
            t.TEST_Kanban_Column();
            break;
        case 5:
            t.TEST_IssueType();
            break;
        case 6:
            t.TEST_Issues();
            break;
        case 7:

            t.Test_User();
            t.TEST_Project();
            t.TEST_KanbanBoards();
            t.TEST_Kanban_Column();
            t.TEST_IssueType();
            t.TEST_Issues();
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }

    } while (option != 0);

    return 0;
}