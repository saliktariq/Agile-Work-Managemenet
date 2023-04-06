#include <iostream>
#include "database.h"
#include "project.h"
#include "issue_types.h"
#include "issues.h"
#include "kanban_boards.h"
#include "kanban_columns.h"
#include "Repository.h"
#include "users.h"

using namespace std;
int main() {

    // Create an instance of the Repository class
    Repository* repository = new Repository();

    // Create a new user
    User user1(0, "user1", "User One", "user1@example.com", "user");
    

    // Call the createUser method to add the user to the database
    repository->createUser(user1);

    return 0;
}