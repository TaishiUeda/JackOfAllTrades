/*
 * CppSqlParser.cpp
 * Copyright (C) 2020 uedataishi <uedataishi@Mac-mini.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "CppSqlParser.h"

namespace csp{

    bool Data::get(int32_t& value){}
    bool Data::get(float& value){}
    bool Data::get(std::string& value){}
    bool Data::get(Binary_t& value){}
    bool Data::set(const int32_t& value){}
    bool Data::set(const float& value){}
    bool Data::set(const std::string& value){}
    bool Data::set(const Binary_t& value){}

    std::string Data::str(){
	switch(type_){
	    case NONE:
		return "";
		break;
	    case INTEGER:
		int32_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case REAL:
		float value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case TEXT:
		int32_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	    case BLOB:
		int32_t value = 0;
		this->get(value);
		return std::to_string(value);
		break;
	}
    }

