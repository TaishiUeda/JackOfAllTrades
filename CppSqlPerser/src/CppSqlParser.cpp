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
    Data::Data(const bool& is_key)
	:is_key_(is_key){}
    //---------------------------------------------------------
    Data::Data(const Type_t& type, const bool& is_key)
	:is_key_(is_key), type_(type){}

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
	for(size_t k=0u; k<2u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value)[k];
	}
	this->type_ = INT16;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const int32_t& value){
	this->data_.resize(4);
	for(size_t k=0u; k<4u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value)[k];
	}
	this->type_ = INT32;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const int64_t& value){
	this->data_.resize(8u);
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value)[k];
	}
	this->type_ = INT64;
    }
    //---------------------------------------------------------
    template<>
    void Data::set(const double& value){
	this->data_.resize(8u);
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = reinterpret_cast<int8_t*>(&value)[k];
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

    //############################################################
    //
    std::string create(const Table_t& obj, std::string& err_msg){}
    std::string update(const Column_t& col, const int64_t& key, std::string& err_msg){}
    std::string update(const Column_t& col, std::string& err_msg){}
    std::string insert(const Column_t& col, std::string& err_msg){}
    ErrList_t exec(const std::string& query){}
    Table_t select(const std::string& query){}
}
