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

    using namespace sf;

    /* Open database */
    Fetcher sql_fetch("test.db");

    // Execution of SQL query
    std::string err_msg;
    ExecResult_t res = sql_fetch.exec("SELECT * FROM sqlite_master", err_msg);
    
    // Dump result. dump as a string in JSON format.
    std::cout << sql_fetch.dump(res) << std::endl;

    //###############################################################
    //  Creating table
    //
    // 1. From table_info A
    std::cout << "--- 1. Create table from TableInfo_t ---" << std::endl;
    TableInfo_t table_info_A = {
	{"user",{ 
		    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
		    {"name", Data(TEXT, NOT_NULL)},
		    {"sex", Data(TEXT)},
		    {"age", Data(INT8)},
		    {"country", Data(TEXT)},
		    {"height_cm", Data(FLOAT)},
		    {"size", Data(TEXT)}
		}
	},
	{"area",{ 
		    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
		    {"country", Data("Japan", NOT_NULL | DEFAULT)},
		    {"city", Data(TEXT)},
		    {"population", Data(DOUBLE)},
		}
	}
    };
    //Generating SQL query
    std::string query = sql_fetch.genQueryCreate(table_info_A, err_msg);
    std::cout << query << std::endl;

    // 2. From table_info B
    std::cout << "--- 2. Create table from TableInfo_t ---" << std::endl;
    Column_t user_col_1 ={
	{"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
	{"name", Data(TEXT, NOT_NULL)},
	{"sex", Data(TEXT)},
	{"age", Data(INT8)},
	{"country", Data(TEXT)},
	{"height_cm", Data(FLOAT)},
	{"size", Data("Medium", "CHAR(8)", DEFAULT)}
    };
    Column_t area_col_1 ={
	{"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
	{"country", Data(TEXT, NOT_NULL)},
	{"prefecture", Data(TEXT)},
	{"population", Data(DOUBLE)},
    };
    TableInfo_t table_info_B;
    table_info_B["user"] = user_col_1;
    table_info_B["area"] = area_col_1;
    //Generating SQL query
    query = sql_fetch.genQueryCreate(table_info_B, err_msg);
    std::cout << query << std::endl;

    // 3. From a column
    std::cout << "--- 3. Create table from a Column_t ---" << std::endl;
    //Change values. change function keeps the types of values.
    user_col_1["name"].change("Michel");
    user_col_1["sex"].change("Male");
    user_col_1["age"].change<int8_t>(35); //Specify type if it is ambiguous.
    user_col_1["country"].change("USA");
    user_col_1["height_cm"].change<float>(189.3);//Specify type if it is ambiguous.
    //Generating SQL query
    query = sql_fetch.genQueryCreate("user",user_col_1,err_msg);
    std::cout << query << std::endl;

    //4. From a list of columns
    std::cout << "--- 4. Create table from a ColumnList_t ---" << std::endl;
    //Construction of column by initial values
     Column_t user_col_2 = {// primary key is needed only in the fromt column.
	{"name", Data("Saki")},
	{"sex", Data("Female")},
	{"age", Data(28)},
	{"country", Data("Japan")},
	{"height_cm", Data(158.2)},
     };
     //Construction of column by set function. set function redifines the types of values
     Column_t user_col_3;
     user_col_3["name"].set("Chang");
     user_col_3["sex"].set("Male");
     user_col_3["age"].set(69);
     user_col_3["country"].set("China");
     user_col_3["height_cm"].set(168.2);
     //Push columns into a list
     ColumnList_t user_col_list;
     user_col_list.push_back(user_col_1);
     user_col_list.push_back(user_col_2);
     user_col_list.push_back(user_col_3);
    //Generating SQL query
    query = sql_fetch.genQueryCreate("user",user_col_list,err_msg);
    std::cout << query << std::endl;

    // 4. From a Table
    std::cout << "--- 5. Create table from a Table_t ---" << std::endl;
    ColumnList_t area_col_list = { 
	{
	    {"ID", Data(0, PRIMARY_KEY | NOT_NULL)},
	    {"country", Data("Japan", NOT_NULL)},
	    {"city", Data("Ibaraki")},
	    {"population", Data(287.1)}
	},
	{
	    //primary key and flags are needed by only in front column
	    {"country", Data("USA")},
	    {"city", Data("Losangels")},
	    {"population", Data(400.0)}
	},
	{
	    //primary key and flags are needed by only in front column
	    {"country", Data("China")},
	    {"city", Data("Beijing")},
	    {"population", Data(2154.0)}
	}
    };
    Table_t a_table = {
	{"user", user_col_list},
	{"area", area_col_list}
    };
    //Generating SQL query
    std::string str = sql_fetch.genQueryCreate(a_table, err_msg);
    std::cout << str << std::endl;

    //execute query
    //res = sql_fetch.exec(str, err_msg);
    //std::cout << sql_fetch.dump(res) << std::endl;

    //###############################################################
    //  Fetch colmun
    //
    std::cout << "--- 7. Fetch columns ---" << std::endl;
    
    //Fetcher can execute multiple queries connected by semicolon.
    std::list<ExecResult_t> res_list
	= sql_fetch.execSeparate("SELECT * FROM user; SELECT city, population FROM area;", err_msg);
    std::cout << sql_fetch.dump(res_list);
    
    auto i_res = res_list.begin();
    ColumnList_t selected_1 = sql_fetch.fetchColumn(*i_res, err_msg);
    //get some of values by "get" function
    std::string user_name_1;
    selected_1[0]["name"].get(user_name_1);
    double user1_height_cm;
    selected_1[0]["height_cm"].get(user1_height_cm);
    std::cout << "From user, name: " << user_name_1 
	<< ", height_cm: " << user1_height_cm << std::endl;

    ++i_res;
    ColumnList_t selected_2 = sql_fetch.fetchColumn(*i_res, err_msg);
    //get some of values by "get" function
    double pop;
    std::string city;
    std::string country;
    auto i_sel2_end = selected_2.end();
    std::cout << "From area, " << std::endl;
    for(auto i_sel2 = selected_2.begin(); i_sel2 != i_sel2_end; ++i_sel2){
	try{
	    i_sel2->at("population").get(pop); 
	    i_sel2->at("city").get(city);
	    //If key words are not in selected columns,
	    //it through iexeption from std::map
	    //i_sel2->at("contry").get(country);
	}
	catch(std::exception& e){
	    std::cerr << "Error in get values. what: " << e.what() << std::endl;
	}
	std::cout << city << ": population = " << pop << std::endl;
    }

    //###############################################################
    //  Insert column
    //
    std::cout << "--- 8. Insert a column ---" << std::endl;
     Column_t user_col_4 = {// primary key is needed only in the fromt column.
	{"name", Data("Charles")},
	{"sex", Data("Male")},
	{"age", Data(22)},
	{"country", Data("Monaco")},
	{"height_cm", Data(180.2)},
     };
     str = sql_fetch.genQueryInsert("user", user_col_4, err_msg);
     std::cout << str << std::endl;

    std::cout << "--- 9. Insert a list of columns ---" << std::endl;
     Column_t user_col_5 = {// primary key is needed only in the fromt column.
	{"name", Data("Max")},
	{"sex", Data("Male")},
	{"age", Data(22)},
	{"country", Data("Belgique")},
	{"height_cm", Data(180.0)},
     };
     ColumnList_t column_list2 = {user_col_4, user_col_5};
     str = sql_fetch.genQueryInsert("user", column_list2, err_msg);
     std::cout << str << std::endl;
     
    //###############################################################
    //  Update column
    //
    //res = sql_fetch.exec(str, err_msg);
    //std::cout << sql_fetch.dump(res);
    std::cout << "--- 10. update a column ---" << std::endl;
    res = sql_fetch.exec("SELECT ID, size FROM user WHERE height_cm >= 180.0;", err_msg);
    std::cout << sql_fetch.dump(res);
    ColumnList_t large_user = sql_fetch.fetchColumn(res, err_msg);

    auto i_large_end = large_user.end();
    for(auto i_large = large_user.begin(); i_large != i_large_end; ++i_large){
	i_large->at("size").change("Large");
	str = sql_fetch.genQueryUpdate("user", *i_large, err_msg);
	std::cout << str << std::endl;
	//res = sql_fetch.exec(str, err_msg);
	//std::cout << sql_fetch.dump(res);
    }

    res = sql_fetch.exec("SELECT * from user", err_msg);
    std::cout << sql_fetch.dump(res);
    
    return 0;
}


