#include <iostream>
#include "Repository.h"
#include "Tests.cpp"
#include <thread>
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
        {
            thread t1([&t]() {
                t.Test_User();
                });
            t1.join();
        }
            break;
        case 2:
        {
            thread t1([&t]() {
                t.TEST_Project();
                });
            t1.join();
        }
        break;
        case 3:
        {
            thread t1([&t]() {
                t.TEST_KanbanBoards();
                });
            t1.join();
        }
        break;
        case 4:
        {
            thread t1([&t]() {
                t.TEST_Kanban_Column();
                });
            t1.join();
        }
        break;
        case 5:
        {
            thread t1([&t]() {
                t.TEST_IssueType();
                });
            t1.join();
        }
        break;
        case 6:
        {
            thread t1([&t]() {
                t.TEST_Issues();
                });
            t1.join();
        }
        break;
        case 7:
        {
            thread t1([&t]() {
                t.Test_User();
                t.TEST_Project();
                t.TEST_KanbanBoards();
                t.TEST_Kanban_Column();
                t.TEST_IssueType();
                t.TEST_Issues();
                });
            t1.join();
        }
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