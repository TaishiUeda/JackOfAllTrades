/*
 * main.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SqliteFetcher.hpp"

int main(int argc, char* argv[]) {
    /* Open database */
    sf::Fetcher sql_fetch("test.db");

    sf::Column_t a_col ={
	{"ID", sf::Data(0,sf::PRIMARY_KEY)},
	{"name", sf::Data("Taishi Ueda")},
	{"sex", sf::Data("Male", sf::DEFAULT)},
	{"age", sf::Data(35)}
    };

    std::string err_msg;
    std::string str = sql_fetch.genQueryCreate("people", a_col, err_msg);
    std::cout << str << std::endl;

    //sf::ExecResult_t res = sql_fetch.exec(str, err_msg);
    //std::cout << sql_fetch.dump(res) << std::endl;

    sf::Column_t b_col ={
	{"name", sf::Data("Saki Ueda")},
	{"sex", sf::Data("Female")},
	{"age", sf::Data(35)}
    };

    str = sql_fetch.genQueryInsert("people", b_col, err_msg);
    std::cout << str << std::endl;

    str = sql_fetch.genQueryUpdate("people", a_col, err_msg);
    std::cout << str << std::endl;
    //res = sql_fetch.exec(str, err_msg);
    //std::cout << sql_fetch.dump(res) << std::endl;;

    //res = sql_fetch.exec(sql_fetch.genQueryInsert("people", a_col, err_msg), err_msg);
    //std::cout << sql_fetch.dump(res) << std::endl;;

    sf::ExecResult_t res = sql_fetch.exec("SELECT * FROM people", err_msg);
    std::cout << sql_fetch.dump(res) << std::endl;;

    sf::ColumnList_t selected = sql_fetch.fetchColumn(res, err_msg);

    std::string user_name;
    selected[0]["name"].get(user_name);
    std::string sex;
    selected[0]["sex"].get(sex);
    int32_t age;
    selected[0]["age"].get(age);

    selected[1]["name"].get(user_name);
    selected[1]["sex"].get(sex);
    selected[1]["age"].get(age);

    selected[1]["age"].change(36);

    str = sql_fetch.genQueryUpdate("people", selected[1], err_msg);
    std::cout << str << std::endl;

    res = sql_fetch.exec(str, err_msg);
    std::cout << sql_fetch.dump(res) << std::endl;;

    res = sql_fetch.exec("SELECT * FROM people", err_msg);
    std::cout << sql_fetch.dump(res) << std::endl;;
    
    return 0;
}


