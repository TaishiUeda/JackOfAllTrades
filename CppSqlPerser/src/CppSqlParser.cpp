/*
 * CppSqlParser.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "CppSqlParser.hpp"

namespace csp{

    //##############################################################
    // Data
    //---------------------------------------------------------
    Data::Data(){}
    //---------------------------------------------------------
    Data::Data(const KeyFlag_t& flg)
	:key_flg_(flg){}
    //---------------------------------------------------------
    Data::Data(const Type_t& type, const KeyFlag_t& flg)
	:key_flg_(flg), type_(type){}

    //---------------------------------------------------------
    template<>
    bool Data::get(int8_t& value){
	if(this->type_ == INT8){
	    value = data_[0];
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int16_t& value){
	if(this->type_ == INT16){
	    for(size_t k=0u; k<data_.size(); ++k){
		reinterpret_cast<int8_t*>(&value)[k] = data_[k];
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int32_t& value){
	if(this->type_ == INT32){
	    for(size_t k=0u; k<data_.size(); ++k){
		reinterpret_cast<int8_t*>(&value)[k] = data_[k];
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int64_t& value){
	if(this->type_ == INT64){
	    for(size_t k=0u; k<data_.size(); ++k){
		reinterpret_cast<int8_t*>(&value)[k] = data_[k];
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(double& value){
	if(this->type_ == REAL){
	    for(size_t k=0u; k<data_.size(); ++k){
		reinterpret_cast<int8_t*>(&value)[k] = data_[k];
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(std::string& value){
	if(this->type_ == TEXT){
	    for(size_t k=0u; k<this->data_.size(); ++k){
		value[k] = static_cast<char>(this->data_[k]);
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(Binary_t& value){
	if(this->type_ == BLOB){
	    value = this->data_;
	    return true;
	}
	else{
	    return false;
	}
    }

    //---------------------------------------------------------
    template<>
    void Data::set(const int8_t& value){
	this->data_.resize(1);
	this->data_[0] = value;
	this->type_ = INT8;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const int16_t& value){
	this->data_.resize(2);
	int16_t value_k = value;
	for(size_t k=0u; k<2u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value_k)[k];
	}
	this->type_ = INT16;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const int32_t& value){
	this->data_.resize(4);
	int32_t value_k = value;
	for(size_t k=0u; k<4u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value_k)[k];
	}
	this->type_ = INT32;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const int64_t& value){
	this->data_.resize(8u);
	int64_t value_k = value;
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value_k)[k];
	}
	this->type_ = INT64;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const double& value){
	this->data_.resize(8u);
	double value_k = value;
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value_k)[k];
	}
	this->type_ = REAL;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const std::string& value){
	this->data_.clear();
	for(size_t k=0u; k<value.size(); ++k){
	    this->data_.push_back(static_cast<uint8_t>(value[k]));
	}
	this->type_ = TEXT;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const Binary_t& value){
	this->data_ = value;
	this->type_ = BLOB;
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const int8_t& value){
	if(this->type_ == INT8){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const int16_t& value){
	if(this->type_ == INT16){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const int32_t& value){
	if(this->type_ == INT32){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const int64_t& value){
	if(this->type_ == INT64){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const double& value){
	if(this->type_ == REAL){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const std::string& value){
	if(this->type_ == TEXT){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const Binary_t& value){
	if(this->type_ == BLOB){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }

    //---------------------------------------------------------
    std::string Data::str(){
	std::string ret;
	switch(type_){
	    case NONE:{
			  ret = "";
			  break;
		      }
	    case INT8:{
			  int8_t value_int8 = 0;
			  this->get(value_int8);
			  ret = std::to_string(value_int8);
			  break;
		      }
	    case INT16:{
			   int16_t value_int16 = 0;
			   this->get(value_int16);
			   ret = std::to_string(value_int16);
			   break;
		       }
	    case INT32:{
			   int32_t value_int32 = 0;
			   this->get(value_int32);
			   ret = std::to_string(value_int32);
			   break;
		       }
	    case INT64:{
			   int64_t value_int64 = 0;
			   this->get(value_int64);
			   ret = std::to_string(value_int64);
			   break;
		       }
	    case REAL:{
			  double value_real = 0;
			  this->get(value_real);
			  ret = std::to_string(value_real);
			  break;
		      }
	    case TEXT:{
			  std::string value_text;
			  this->get(value_text);
			  ret = value_text;
			  break;
		      }
	    case BLOB:{
			  Binary_t value_blob;
			  this->get(value_blob);
			  char buff[value_blob.size()];
			  for(size_t k=0u; k<value_blob.size(); ++k){
			      sprintf(buff,"%x",value_blob[k]);
			  }
			  ret = std::string(buff);
			  break;
		      }
	}
	return ret;
    }

    //########################################################################
    // SqlFetch
    // Constructor
    SqlFetch::SqlFetch(){}

    //-------------------------------------------------------------------
    // Constructor. Open database.
    SqlFetch::SqlFetch(const std::string& db_name){
       int32_t retval = sqlite3_open(db_name.c_str(), &db_ptr_);
       if(retval != SQLITE_OK){
	   last_err_ = sqlite3_errstr(retval);
       }
       else{
	   is_opened_ = true;
	   last_table_info_ = getMaster(last_err_);
       }
    } 

    //-------------------------------------------------------------------
    // Open database.
    int32_t SqlFetch::open(const std::string& db_name, std::string& err_msg,
	    const int32_t& flags, const char* zVfs){
       int32_t retval 
	   = sqlite3_open_v2(db_name.c_str(), &db_ptr_, flags, zVfs);
       if(retval != SQLITE_OK){
	   this->last_err_ = sqlite3_errstr(retval);
       }
       else{
	   this->is_opened_ = true;
	   last_table_info_ = getMaster(last_err_);
       }
       return retval;
    }

    static int execCallback(void *result_ptr, int argc, char **argv, char **col_name){
	ResultElement_t a_res;
        for(int k=0; k<argc; ++k){
	    a_res[col_name[k]] = argv[k];
	}
	reinterpret_cast<ExecResult_t*>(result_ptr)->result.push_back(a_res);
	return 0;
    }

    //-------------------------------------------------------------------
    // Execute SQLite query
    ExecResult_t SqlFetch::exec(const std::string& query, std::string& err_msg){
	char *err_char = 0;
	last_exec_result_.in_sql = query;
	last_exec_result_.result.clear();
        int32_t ret = sqlite3_exec(db_ptr_, query.c_str(), 
		execCallback, &last_exec_result_, &err_char);
	if(ret != SQLITE_OK){
	    err_msg = err_char;
	    sqlite3_free(err_char);
	}
	return last_exec_result_;
    }

    //-------------------------------------------------------------------
    // Dump result of exec function into string.
    std::string SqlFetch::dump(const ExecResult_t& res) const{
	std::string ret = "Input query: " + res.in_sql + "\n";
	auto i_res = res.result.begin();
	auto i_res_end = res.result.end();
	ret += "Result:\n";
	for(;i_res != i_res_end; ++i_res){
	    auto i_elem = i_res->begin();
	    auto i_elem_end = i_res->end();
	    for(;i_elem != i_elem_end; ++i_elem){
		ret += i_elem->first + ": " + i_elem->second + "\n";
	    }
	}
	return ret;
    }

    // Fetch column list from result of executed query for SELECT.
    /*
     * \param[in] res Result output by exec function with SELECT queries.
     * \param[out] err_msg Error message. In case of fething successfully, this becomes empty.
     * \retval list of columns selected by queries.
     */
    ColumnList_t SqlFetch::fetchColumn(const ExecResult_t& res, std::string& err_msg) const{}

    // Get master table.
    /*
     * \param[out] err_list List of errors
     * \retval Table information. This is usefull to create colmuns
     *     corresponded to tables in database.
     */
    TableInfo_t SqlFetch::getMaster(std::string& err_msg){}

    // Generate a query to create table from a column list.
    /* If the column_list doen't contain a data as primary key,
     *  a row with primary key is automatically created.
     * \param[in] name name of table to be created.
     * \param[in] column_list list of columns to be saved in table.
     * \param[out] err_msg Error message.
     * \retval Query message to create table.
     */
    std::string SqlFetch::genQueryCreate(const std::string& name,
	    const ColumnList_t& column_list, std::string& err_msg){}

    // Generate queries to create table from a table info.
    /*
     * \param[in] table_info Table information containing definition of tables.
     * \param[out] err_msg Error message.
     * \retval Query message to create table.
     */
    std::string SqlFetch::genQueryCreate(const TableInfo_t& table_info, std::string& err_msg){}

    // Generate a query to insert a column.
    /*
     * \param[in] name name of a table to be inserted a column into.
     * \param[in] col A column to be inserted into the table.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string SqlFetch::genQueryInsert(const std::string& table_name,
	    const Column_t& col, std::string& err_msg){}

    // Generate a query to update a column.
    /* This is used to update a column which does not contain primary key,
     *  and the user have to point at the target column by input primary hey.
     * \param[in] name name of a table to be updated.
     * \param[in] col An updated column.
     * \param[in] key Primary key of the column.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string SqlFetch::genQueryUpdate(const std::string table_name,
	    const Column_t& col, const int64_t& key, std::string& err_msg){}

    // Generate a query to update a column.
    /* This is used to update a column which contains primary key.
     * \param[in] name name of a table to be updated.
     * \param[in] col An updated column.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string SqlFetch::genQueryUpdate(const std::string& table_name,
	    const Column_t& col, std::string& err_msg){}
}
