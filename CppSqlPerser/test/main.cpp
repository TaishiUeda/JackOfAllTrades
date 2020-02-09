/*
 * main.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CppSqlParser.hpp"

int main(int argc, char* argv[]) {
   /* Open database */
    csp::SqlFetch sql_fetch("test.db");

   /* Create SQL statement */
    std::string sql = argv[1];

   /* Execute SQL statement */
    std::string err;
    csp::ExecResult_t res = sql_fetch.exec(sql, err);

    if(!err.empty()){
	std::cout << err << std::endl;
   } else {
       std::cout << sql_fetch.dump(res) << std::endl;
   }
   return 0;
}


