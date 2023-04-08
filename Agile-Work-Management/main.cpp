#include <iostream>
#include "Repository.h"
#include <windows.h>
#include <sstream>
#include <iomanip>
#include "Tests.cpp"
using namespace std;


   
int main(){

    TEST t;
    t.Test_User();
    t.TEST_Project();
    t.TEST_KanbanBoards();
    t.TEST_Kanban_Column();
    t.TEST_IssueType();
    return 0;
}