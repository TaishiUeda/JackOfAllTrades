#include <sqlite.h>
#include <string>
#include <list>
#include <map>

namespace csp{

    enum Type_t{
	NONE,
	INTEGER,
	REAL,
	TEXT,
	BLOB
    };

    using Binary_t = std::vector<int8_t>;

    class Data{
	public:
	    std::string str();
	    template<T_OUT>
		bool get(T_OUT& value);
	    template<T_IN>
		bool set(const T_IN& value);
	private:
	    Binary_t data_;
	    Type_t type_;
    };

    using Column_t = std::map<std::string, Data_t>
    using Table_t  = std::list<Column_t>;
    using DataBase_t  = std::map<std::string, Table_t>;

    class CppSqlPerser{


    };

}
