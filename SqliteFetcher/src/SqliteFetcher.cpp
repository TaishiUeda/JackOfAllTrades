/*
 * CppSqlParser.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "SqliteFetcher.hpp"

namespace sf{

    //##############################################################
    // Data
    //---------------------------------------------------------
    Data::Data(){}
    
    //---------------------------------------------------------
    Data::Data(const KeyFlag_t& flg)
	:key_flg_(flg){}

    //---------------------------------------------------------
    Data::Data(sql_types::TypeStr_t type, const KeyFlag_t& flg)
	:key_flg_(flg), type_str_(type){
	    setType(type);
    }

    //---------------------------------------------------------
    Data::Data(const std::string& dflt_str, sql_types::TypeStr_t type, 
		    const KeyFlag_t& flg)
	:key_flg_(flg), type_str_(type){

	    setType(type);
	    set(type_, dflt_str);
	}

    //---------------------------------------------------------
    void Data::setType(sql_types::TypeStr_t type){
	//typeから括弧部分を消去する
	size_t cpos = type.find('(');
	if(cpos != std::string::npos){
	    type = type.substr(0u,cpos);
	}

	if(TypeDef.find(type) != TypeDef.end()){
	    type_ = TypeDef.at(type);
	}
	else{
	    type_ = BLOB;
	}
    }

    //---------------------------------------------------------
    const sql_types::TypeStr_t& Data::type() const{
	return type_str_;
    }

    //---------------------------------------------------------
    bool Data::get(void* value_ptr, const Type_t& type) const{
	if(type_ == type){
	    for(size_t k=0u; k<data_.size(); ++k){
		reinterpret_cast<int8_t*>(value_ptr)[k] = data_[k];
	    }
	    return true;
	}
	else{
	    return false;
	}
    }

    //---------------------------------------------------------
    void Data::set(void* value_ptr, const Type_t& type, const uint32_t& size){
	this->data_.resize(size);
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(value_ptr)[k];
	}
	this->type_ = type;
	
    }

    //---------------------------------------------------------
    bool Data::change(void* value_ptr, const Type_t& type, const uint32_t& size){
	if(this->type_ == type){
	    this->set(value_ptr, type, size);
	    return true;
	}
	else{
	    return false;
	}

    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int8_t& value) const{
	return get(&value, INT8);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int16_t& value) const{
	return get(&value, INT16);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int32_t& value) const{
	return get(&value, INT32);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(int64_t& value) const{
	return get(&value, INT64);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(uint64_t& value) const{
	return get(&value, UINT64);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(float& value) const{
	return get(&value, FLOAT);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(double& value) const{
	return get(&value, DOUBLE);
    }
    //---------------------------------------------------------
    template<>
    bool Data::get(std::string& value) const{
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
    bool Data::get(bool& value) const{
	if(this->type_ == BOOL){
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
    bool Data::get(Binary_t& value) const{
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
    void Data::set(int8_t value){
	set(&value, INT8, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(int16_t value){
	set(&value, INT16, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(int32_t value){
	set(&value, INT32, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(int64_t value){
	set(&value, INT64, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(uint64_t value){
	set(&value, UINT64, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(bool value){
	set(&value, BOOL, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(float value){
	set(&value, FLOAT, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(double value){
	set(&value, DOUBLE, sizeof(value));
    }
    //---------------------------------------------------------
    template<>
    void Data::set(std::string value){
	this->data_.clear();
	for(size_t k=0u; k<value.size(); ++k){
	    this->data_.push_back(static_cast<uint8_t>(value[k]));
	}
	this->type_ = TEXT;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(Binary_t value){
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
    bool Data::change(const uint64_t& value){
	if(this->type_ == UINT64){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const float& value){
	if(this->type_ == FLOAT){
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
	if(this->type_ == DOUBLE){
	    this->set(value);
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    template<>
    bool Data::change(const bool& value){
	if(this->type_ == BOOL){
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
	    case BOOL:{
			  bool value_bool = 0;
			  this->get(value_bool);
			  ret = std::to_string(value_bool);
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
	    case UINT64:{
			   uint64_t value_uint64 = 0;
			   this->get(value_uint64);
			   ret = std::to_string(value_uint64);
			   break;
		       }
	    case FLOAT:{
			  float value_float = 0.0f;
			  this->get(value_float);
			  ret = std::to_string(value_float);
			  break;
		      }
	    case DOUBLE:{
			  double value_real = 0.0;
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

    //---------------------------------------------------------
    void Data::set(const Type_t& type, const std::string& dflt_str){
	switch(type){
	    case NONE:{
			  break;
		      }
	    case BOOL:{
			  bool value_bool 
			      = static_cast<bool>(std::stoi(dflt_str));
			  this->set(value_bool);
			  break;
		      }
	    case INT8:{
			  int8_t value_int8_t 
			      = static_cast<int8_t>(std::stoi(dflt_str));
			  this->set(value_int8_t);
			  break;
		      }
	    case INT16:{
			  int16_t value_int16_t 
			      = static_cast<int16_t>(std::stoi(dflt_str));
			  this->set(value_int16_t);
			   break;
		       }
	    case INT32:{
			  int32_t value_int32_t 
			      = static_cast<int32_t>(std::stoi(dflt_str));
			  this->set(value_int32_t);
			   break;
		       }
	    case INT64:{
			  int64_t value_int64_t 
			      = static_cast<int64_t>(std::stoi(dflt_str));
			  this->set(value_int64_t);
			   break;
		       }
	    case UINT64:{
			  uint64_t value_uint64_t 
			      = static_cast<uint64_t>(std::stoi(dflt_str));
			  this->set(value_uint64_t);
			   break;
		       }
	    case FLOAT:{
			  float value_float 
			      = static_cast<float>(std::stof(dflt_str));
			  this->set(value_float);
			  break;
		      }
	    case DOUBLE:{
			  double value_double 
			      = static_cast<double>(std::stod(dflt_str));
			  this->set(value_double);
			  break;
		      }
	    case TEXT:{
			  this->set(dflt_str);
			  break;
		      }
	    case BLOB:{
			  Binary_t value_blob;
			  for(size_t k=0u; k<dflt_str.length(); ++k){
			      value_blob.push_back(
				      static_cast<int8_t>(dflt_str[k]));
			  }
			  this->set(value_blob);
			  break;
		      }
	}
    }


    //########################################################################
    // Fetcher
    // Constructor
    Fetcher::Fetcher(){}

    //-------------------------------------------------------------------
    // Constructor. Open database.
    Fetcher::Fetcher(const std::string& db_name){
       int32_t retval = sqlite3_open(db_name.c_str(), &db_ptr_);
       if(retval != SQLITE_OK){
	   last_err_ = sqlite3_errstr(retval);
       }
       else{
	   is_opened_ = true;
       }
    } 

    //-------------------------------------------------------------------
    // Open database.
    int32_t Fetcher::open(const std::string& db_name, std::string& err_msg,
	    const int32_t& flags, const char* zVfs){
       int32_t retval 
	   = sqlite3_open_v2(db_name.c_str(), &db_ptr_, flags, zVfs);
       if(retval != SQLITE_OK){
	   this->last_err_ = sqlite3_errstr(retval);
       }
       else{
	   this->is_opened_ = true;
       }
       return retval;
    }

    //-------------------------------------------------------------------
    static int execCallback(void *result_ptr, int argc, char **argv, char **col_name){
	ResultElement_t a_res;
        for(int k=0; k<argc; ++k){
	    if(argv[k] == nullptr || argv[k][0] == '\0'){
		a_res[col_name[k]] = "";
	    }
	    else{
		a_res[col_name[k]] = argv[k];
	    }
	}
	reinterpret_cast<ExecResult_t*>(result_ptr)->result.push_back(a_res);
	return 0;
    }

    //-------------------------------------------------------------------
    // Execute SQLite query
    ExecResult_t Fetcher::exec(const std::string& query, std::string& err_msg){
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
    // Execute SQLite query
    std::list<ExecResult_t> Fetcher::execSeparate(const std::string& query, std::string& err_msg){
	std::list<ExecResult_t> ret_list;
	size_t i_begin = 0u;
	size_t i_dlm = 0u;
	while(i_begin < query.size()){
	    i_dlm = query.find(";",i_begin);
	    if(i_dlm == std::string::npos){
		i_dlm=query.size()-1u;
	    }
	    auto a_query = query.substr(i_begin,i_dlm-i_begin);
	    auto a_res = exec(a_query, err_msg);
	    if(!err_msg.empty()){
		break;
	    }
	    else{
		ret_list.push_back(a_res);
	    }
	    i_begin = i_dlm+1u;
	}
	return ret_list;
    }

    //-------------------------------------------------------------------
    // Dump result of exec function into string.
    std::string Fetcher::dump(const ExecResult_t& res) const{
	std::string ret = "{\"Input\":\"" + res.in_sql + "\",\n";
	auto i_res = res.result.begin();
	auto i_res_end = res.result.end();
	ret += "\"results\":[";
	bool is_first1 = false;
	for(;i_res != i_res_end; ++i_res){
	    if(!is_first1){
		ret += ",\n ";
	    }else{
		is_first1 = false;
	    }
	    ret += "{";
	    auto i_elem = i_res->begin();
	    auto i_elem_end = i_res->end();
	    bool is_first = true;
	    for(;i_elem != i_elem_end; ++i_elem){
		if(!is_first){
		    ret += ", ";
		}else{
		    is_first = false;
		}
		ret += "\"" + i_elem->first + "\":\"" + i_elem->second + "\"";
	    }
	    ret += "}";
	}
	ret += "]}";
	return ret;
    }

    //-------------------------------------------------------------------
    //! Dump result of exec function into string.
    std::string Fetcher::dump(const std::list<ExecResult_t>& res_list) const{
	auto i_res_end = res_list.end();
	std::string ret;
	for(auto i_res =res_list.begin(); i_res != i_res_end; ++i_res){
	    ret += dump(*i_res);
	}
	return ret;
    }

    //-------------------------------------------------------------------
    // Fetch column list from result of executed query for SELECT.
    ColumnList_t Fetcher::fetchColumn(const ExecResult_t& res, std::string& err_msg) const{
	ColumnList_t col;
	return col;
    }

    // Get master table.
    /*
     * \param[out] err_list List of errors
     * \retval Table information. This is usefull to create colmuns
     *     corresponded to tables in database.
     */
    TableInfo_t Fetcher::getTableInfo(std::string& err_msg){
	ExecResult_t res = exec("SELECT * FROM sqlite_master;",err_msg);
	TableInfo_t table_info;
	if(!err_msg.empty()){
	    return table_info;
	}
	auto i_res_end = res.result.end();
	for(auto i_res = res.result.begin(); i_res != i_res_end; ++i_res){
	    if(i_res->at("type") == "table"){
		std::string tbl_name = i_res->at("name");
		Column_t a_col = getTableInfo(tbl_name, err_msg);
		if(!err_msg.empty()){
		    break;
		}
		else{
		    table_info[tbl_name] = a_col;
		}
	    }
	}
	return table_info;
    }
    
    Column_t Fetcher::getTableInfo(const std::string table_name, std::string& err_msg){
	ExecResult_t res = exec("PRAGMA table_info(" + table_name + ");", err_msg);
	Column_t table_info;
	if(!err_msg.empty()){
	    return table_info;
	}
	auto i_res_end = res.result.end();
	bool has_dflt = false;
	KeyFlag_t flg = NORMAL;
	for(auto i_res = res.result.begin(); i_res != i_res_end; ++i_res){
	    has_dflt = false;
	    flg = NORMAL;
	    if(i_res->at("dflt_value") != ""){
		has_dflt = true;
	    }
	    if(i_res->at("pk") == "1"){
		flg |= PRIMARY_KEY;
	    }
	    if(i_res->at("notnull") == "1"){
		flg |= NOT_NULL;
	    }

	    if(has_dflt){
		table_info[i_res->at("name")]
		    = Data(i_res->at("dflt_value"), i_res->at("type"),  flg);
	    }
	    else{
		table_info[i_res->at("name")]
		    = Data(i_res->at("type"), flg);
	    }
	}
	return table_info;
    }

    // Generate a query to create table from a column list.
    /* If the column_list doen't contain a data as primary key,
     *  a row with primary key is automatically created.
     * \param[in] name name of table to be created.
     * \param[in] column_list list of columns to be saved in table.
     * \param[out] err_msg Error message.
     * \retval Query message to create table.
     */
    std::string Fetcher::genQueryCreate(const std::string& name,
	    const ColumnList_t& column_list, std::string& err_msg){
	std::string ret;
	return ret;
    }

    // Generate queries to create table from a table info.
    /*
     * \param[in] table_info Table information containing definition of tables.
     * \param[out] err_msg Error message.
     * \retval Query message to create table.
     */
    std::string Fetcher::genQueryCreate(const TableInfo_t& table_info, std::string& err_msg){
	std::string ret;
	return ret;
    }

    // Generate a query to insert a column.
    /*
     * \param[in] name name of a table to be inserted a column into.
     * \param[in] col A column to be inserted into the table.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string Fetcher::genQueryInsert(const std::string& table_name,
	    const Column_t& col, std::string& err_msg){
	std::string ret;
	return ret;
    }

    // Generate a query to update a column.
    /* This is used to update a column which does not contain primary key,
     *  and the user have to point at the target column by input primary hey.
     * \param[in] name name of a table to be updated.
     * \param[in] col An updated column.
     * \param[in] key Primary key of the column.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string Fetcher::genQueryUpdate(const std::string table_name,
	    const Column_t& col, const int64_t& key, std::string& err_msg){
	std::string ret;
	return ret;
    }

    // Generate a query to update a column.
    /* This is used to update a column which contains primary key.
     * \param[in] name name of a table to be updated.
     * \param[in] col An updated column.
     * \param[out] err_msg Error message.
     * \retval Query message to insert the column into the table.
     */
    std::string Fetcher::genQueryUpdate(const std::string& table_name,
	    const Column_t& col, std::string& err_msg){
	std::string ret;
	return ret;
    }
}
