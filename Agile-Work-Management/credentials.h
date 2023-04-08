#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>

namespace Credentials {

    // Local Database Credentials (Cache)
    //const std::string LOCALHOST = "127.0.0.1:3306";
    //const std::string USERNAME = "root";
    //const std::string PASSWORD = "rs232rj11";
    //const std::string DATABASE_NAME = "kanban_agile_work_management";

    // Azure Cloud Credentials
    const std::string LOCALHOST = "cpp-backend.mysql.database.azure.com:3306";
    const std::string USERNAME = "salik_azure_sql_db";
    const std::string PASSWORD = "rh32-b@$$-vxhu";
    const std::string DATABASE_NAME = "kanban_agile_work_management";
}

#endif