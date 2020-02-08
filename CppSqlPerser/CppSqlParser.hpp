#ifndef CPPSQLPARSER_HPP
#define CPPSQLPARSER_HPP
#include <sqlite.h>
#include <string>
#include <list>
#include <map>

namespace csp{

    //! Types of data
    enum Type_t{
	NONE,
	INT8,
	INT16,
	INT32,
	INT64,
	REAL,
	TEXT,
	BLOB
    };

    using Binary_t = std::vector<int8_t>;

    //! Data container class
    class Data{
	public:
	    Data();
	    /*!
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    explicit Data(const bool& is_key=false);
	    /*! Set the data type in initializing.
	     * \param[in] type Type of data
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    Data(const Type_t& type, const bool& is_key=false);

	    /*! Put value as a string. This is convenient when create query. */
	    std::string str();

	    /*! Get value.
	     * \param[out] value output value.
	     * \retval true success
	     * \retval false type of value and that of Data are different.
	     */
	    template<T_OUT>
		bool get(T_OUT& value);
	    /*! Set value
	     * \param[in] value to set.
	     */
	    template<T_IN>
		void set(const T_IN& value);
	    /*! Change value. If a value of different type from Data, it returns false.
	     * \param[in] value to set.
	     * \retval true success
	     * \retval false type of value and that of Data are different.
	     */
	    template<T_IN>
		bool change(const T_IN& value);
	private:
	    bool is_key_{false};
	    Binary_t data_;
	    Type_t type_{NONE};
    };

    //! Column type.
    /*! An example of creating a column.
     *
     * ```cpp
     * //Determine data types
     * Column_t col = {
     *     {"ID", Data(INT64, true)},
     *     {"First name", Data(TEXT)},
     *     {"Second name", Data(TEXT)},
     *     {"Age", Data(INT32)},
     *     {"Height_cm", Data(REAL)},
     *     {"Weight_kg", Data(REAL)},
     * };
     *
     * // Set values
     * col["ID"].set(0);
     * col["First name"].set("Alina");
     * col["Second name"].set("Rain");
     * col["Age"].set(28)}]
     * col["Height_cm"].set(165.7);
     * col["Weight_kg"].set(49.3);
     * ```
     */
    using Column_t = std::map<std::string, Data>;

    //! Column type. This is a list of column.
    /*! An example of creating a table.
     *
     * ```cpp
     * Table_t table_1 = {col_1, col_2};
     * ```
     *
     * or,
     *
     * ```cpp
     * Table_t table_1;
     * table_1.push_back(col_1);
     * table_1.push_back(col_2);
     * ```
     *
     * In case of creating only header.
     *
     * ```
     *
     */
    using Table_t  = std::list<Column_t>;

    //! Database type containing multiple tables.
    /*! An example of creating a table.
     *
     * ```cpp
     * DataBase_t db_1 = {
     *     {"Table_1", table_1},
     *     {"Table_2", table_2},
     * };
     * ```
     *
     * or,
     *
     * ```cpp
     * DataBase_t db_1;
     * db_1["Table_1"] = table_1;
     * db_1["Table_2"] = table_2;
     * ```
     */
    using DataBase_t  = std::map<std::string, Table_t>;

    std::string create(const Table_t& obj, std::string& err_msg);
    std::string update(const Column_t& col, const int64_t& key, std::string& err_msg);
    std::string update(const Column_t& col, std::string& err_msg);
    std::string insert(const Column_t& col, std::string& err_msg);

    using ErrList_t = std::list<std::string>;
    ErrList_t exec(const std::string& query);
    Table_t select(const std::string& query);

    };
}
#endif
