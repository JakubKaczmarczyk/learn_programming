#include <iostream>
#include "mysql.h"
#include <string>
#include <sstream>


int main() {

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "SQLadmin", "sql_passengers", 3306, NULL, 0);

    if(!conn) {
        std::cout << "Cannot connect with database" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Successfully connected to database" << std::endl;

    std::string query = "SELECT * FROM passengers";
    const char * query_c = query.c_str();
    int qstate = 0;
    qstate = mysql_query(conn, query_c);
    if(!qstate) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        while(row) {
            std::stringstream row0(row[0]);
            unsigned int row0_int;
            row0 >> row0_int;
            std::stringstream row7(row[7]);
            bool row7_b;
            row7 >> row7_b;
            std::string row1 = std::string(row[1]);
            std::cout << "Name: " << row[1] << " Surrname: " << row[2] << std::endl;
            row = mysql_fetch_row(res);
        }

    }
    return EXIT_SUCCESS;
}

