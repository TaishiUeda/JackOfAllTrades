/*
 * CppSqlParser.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "CppSqlParser.h"

namespace csp{

    //##############################################################
    // Data
    //---------------------------------------------------------
    Data::Data(){}
    //---------------------------------------------------------
    Data::Data(const bool& is_key=false)
	:is_key_(is_key){}
    //---------------------------------------------------------
    Data::Data(Type_t type, const bool& is_key=false)
	:is_key_(is_key), type_(type){}

    //---------------------------------------------------------
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
    bool Data::get(int16_t& value){
	if(this->type_ == INT16){
	    for(size_t k=0u; k<data_.size(); ++k){
		(reinterpret_cast<int8_t*>&value)[k] = data_[k]
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    bool Data::get(int32_t& value){
	if(this->type_ == INT32){
	    for(size_t k=0u; k<data_.size(); ++k){
		(reinterpret_cast<int8_t*>&value)[k] = data_[k]
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    bool Data::get(int64_t& value){
	if(this->type_ == INT64){
	    for(size_t k=0u; k<data_.size(); ++k){
		(reinterpret_cast<int8_t*>&value)[k] = data_[k]
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    bool Data::get(double& value){
	if(this->type_ == REAL){
	    for(size_t k=0u; k<data_.size(); ++k){
		(reinterpret_cast<int8_t*>&value)[k] = data_[k]
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
    bool Data::get(std::string& value){
	if(this->type_ == TEXT){
	    for(size_t k=0u; k<this->data_.size(); ++k){
		value[k] = static_cast<char>(this->data[k]);
	    }
	    return true;
	}
	else{
	    return false;
	}
    }
    //---------------------------------------------------------
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
    void Data::set(const int8_t& value){
	this->data_.resize(1);
	this->data_[0] = value;
	this->type_ = INT8;
    }
    //---------------------------------------------------------
    void Data::set(const int16_t& value){
	this->data_.resize(2);
	for(size_t k=0u; k<2u; ++k){
	    this->data_[k] = (reinterpret_cast<int8_t*>&value)[k];
	}
	this->type_ = INT16;
    }
    //---------------------------------------------------------
    void Data::set(const int32_t& value){
	this->data_.resize(4);
	for(size_t k=0u; k<4u; ++k){
	    this->data_[k] = (reinterpret_cast<int8_t*>&value)[k];
	}
	this->type_ = INT32;
    }
    //---------------------------------------------------------
    void Data::set(const int64_t& value){
	this->data_.resize(8u);
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = (reinterpret_cast<int8_t*>&value)[k];
	}
	this->type_ = INT64;
    }
    //---------------------------------------------------------
    void Data::set(const double& value){
	this->data_.resize(8u);
	for(size_t k=0u; k<8u; ++k){
	    this->data_[k] = (reinterpret_cast<int8_t*>&value)[k];
	}
	this->type_ = REAL;
    }
    //---------------------------------------------------------
    void Data::set(const std::string& value){
	this->data_.clear();
	for(size_t k=0u; k<value.size(); ++k){
	    this->data_.push_back(static_cast<uint8_t>(value[k]));
	}
	this->type_ = TEXT;
    }
    //---------------------------------------------------------
    void Data::set(const Binary_t& value){
	this->data_ = value;
	this->type_ = BLOB;
    }
    //---------------------------------------------------------
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
	switch(type_){
	    case NONE:
		return "";
		break;
	    case INT8:
		int8_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case INT16:
		int16_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case INT32:
		int32_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case INT64:
		int64_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case REAL:
		double value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case TEXT:
		std::string value;
		this->get(value);
		return std::to_string(value);
		break;
	    case BLOB:
		Binary_t value;
		this->get(value);
		return std::to_string(value);
		break;
	}
    }

