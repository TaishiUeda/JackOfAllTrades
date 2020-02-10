#ifndef CPPSQLPARSER_HPP
#define CPPSQLPARSER_HPP
#include <sqlite3.h>
#include <string>
#include <vector>
#include <list>
#include <map>

namespace sf{

    //! Types of data
    enum Type_t{
	NONE,
	INT8,
	INT16,
	INT32,
	INT64,
	UINT64,
	FLOAT,
	DOUBLE,
	BOOL,
	TEXT,
	BLOB
    };

    using Binary_t = std::vector<int8_t>;

    using KeyFlag_t = uint8_t;
    const KeyFlag_t NORMAL = 0u;
    const KeyFlag_t PRIMARY_KEY = 0b00000001;
    const KeyFlag_t AUTO_INCREMENT = 0b00000010;
    const KeyFlag_t NOT_NULL = 0b00000100;
    
    namespace sql_types{
	using TypeStr_t = std::string;
	const TypeStr_t INT = "INT";
	const TypeStr_t INTEGER = "INTEGER";
	const TypeStr_t TYNYINT = "TYNYINT";
	const TypeStr_t SMALLINT = "SMALLINT";
	const TypeStr_t MEDIUMINT = "MEDIUMINT";
	const TypeStr_t BIGINT = "BIGINT";
	const TypeStr_t UINT64 = "UINT64";
	const TypeStr_t INT2 = "INT2";
	const TypeStr_t INT4 = "INT4";
	const TypeStr_t INT8 = "INT8";
	const TypeStr_t CHAR= "CHAR";
	const TypeStr_t CHARACTER = "CHARACTER";
	const TypeStr_t VARCHAR = "VARCHAR";
	const TypeStr_t VARYING_CHARACTER = "VARYING CHARACTER";
	const TypeStr_t NCHAR = "NCHAR";
	const TypeStr_t TEXT = "TEXT";
	const TypeStr_t CLOB = "CLOB";
	const TypeStr_t BLOB = "BLOB";
	const TypeStr_t REAL = "REAL";
	const TypeStr_t DOUBLE = "DOUBLE";
	const TypeStr_t DOUBLE_PRECISION = "DOUBLE PRECISION";
	const TypeStr_t FLOAT = "FLOAT";
	const TypeStr_t NUMERIC = "NUMERIC";
	const TypeStr_t DECIMAL = "DECIMAL";
	const TypeStr_t BOOLEAN = "BOOLEAN";
	const TypeStr_t DATE = "DATE";
	const TypeStr_t DATETIME = "DATETIME";
    }

    const std::map<sql_types::TypeStr_t, Type_t> TypeDef{
	{sql_types::INT, INT32},
	    {sql_types::INTEGER, INT32},
	    {sql_types::TYNYINT, INT8},
	    {sql_types::SMALLINT, INT16},
	    {sql_types::MEDIUMINT, INT32},
	    {sql_types::BIGINT, INT64},
	    {sql_types::UINT64, UINT64},
	    {sql_types::INT2, INT16},
	    {sql_types::INT4, INT32},
	    {sql_types::INT8, INT64},
            {sql_types::CHAR, TEXT},
            {sql_types::CHARACTER, TEXT},
	    {sql_types::VARCHAR, TEXT},
	    {sql_types::VARYING_CHARACTER, TEXT},
	    {sql_types::NCHAR, TEXT},
	    {sql_types::TEXT, TEXT},
	    {sql_types::CLOB, TEXT},
	    {sql_types::BLOB, BLOB},
	    {sql_types::REAL, DOUBLE},
	    {sql_types::DOUBLE, DOUBLE},
	    {sql_types::DOUBLE_PRECISION, DOUBLE},
	    {sql_types::FLOAT, FLOAT},
	    {sql_types::NUMERIC, INT64},
	    {sql_types::DECIMAL, DOUBLE},
	    {sql_types::BOOLEAN, BOOL},
	    {sql_types::DATE, INT64},
	    {sql_types::DATETIME, INT64}
    };
	

    //! Data container class
    class Data{
	public:
	    Data();
	    /*!
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    explicit Data(const KeyFlag_t& flg);
	    /*! Set the data type in initializing.
	     * \param[in] type Type of data
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    Data(sql_types::TypeStr_t type, const KeyFlag_t& flg=NORMAL);
	    /*! Set the data type in initializing.
	     * \param[in] type Type of data
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    Data(const std::string& dflt_str, sql_types::TypeStr_t type, 
		    const KeyFlag_t& flg=NORMAL);
	    /*! Set the data type in initializing.
	     * \param[in] type Type of data
	     * \param[in] is_key If true, this data is to be used as key.
	     *    Only integer type data can be key.
	     */
	    template<typename T_VALUE>
		inline Data(const T_VALUE& dflt_value, const KeyFlag_t& flg=NORMAL):
		    key_flg_(flg){
		    this->set(dflt_value);
		}

	    /*! Put value as a string. This is convenient when create query. */
	    std::string str();

	    const sql_types::TypeStr_t& type() const;

	    /*! Get value.
	     * \param[out] value output value.
	     * \retval true success
	     * \retval false type of value and that of Data are different.
	     */
	    template<typename T_OUT>
		bool get(T_OUT& value) const;
	    /*! Set value
	     * \param[in] value to set.
	     */
	    template<typename T_IN>
		void set(T_IN value);

	    void set(const Type_t& type, const std::string& value);
	    /*! Change value. If a value of different type from Data, it returns false.
	     * \param[in] value to set.
	     * \retval true success
	     * \retval false type of value and that of Data are different.
	     */
	    template<typename T_IN>
		bool change(const T_IN& value);
	private:
	    void setType(sql_types::TypeStr_t type);
	    bool get(void* value_ptr, const Type_t& type) const;
	    void set(void* value_ptr, const Type_t& type, const uint32_t& size);
	    bool change(void* value_ptr, const Type_t& type, const uint32_t& size);
	    KeyFlag_t key_flg_{NORMAL};
	    bool is_auto_{false};
	    Binary_t data_;
	    sql_types::TypeStr_t type_str_;    
	    Type_t type_{NONE};
    };

    //! Column type.
    /*! 
     * # Column type has the string name tags and values.
     * 
     * ## Construct
     *
     * ### Detemine data types
     * ```cpp
     * Column_t col = {
     *     {"ID", Data(INT64, true)},
     *     {"First name", Data(TEXT)},
     *     {"Second name", Data(TEXT)},
     *     {"Age", Data(INT32)},
     *     {"Height_cm", Data(REAL)},
     *     {"Weight_kg", Data(REAL)},
     * };
     *
     * ### Detemine data value and each type is detemined automatically.
     * ```cpp
     * Column_t col = {
     *     {"ID", Data(INT64, true)},
     *     {"First name", Data(TEXT)},
     *     {"Second name", Data(TEXT)},
     *     {"Age", Data(INT32)},
     *     {"Height_cm", Data(REAL)},
     *     {"Weight_kg", Data(REAL)},
     * };
     *
     *
     * // Set values
     * col["ID"].change(0);
     * col["First name"].change("Alina");
     * col["Second name"].change("Rain");
     * col["Age"].change(28)}]
     * col["Height_cm"].change(165.7);
     * col["Weight_kg"].change(49.3);
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
    using ColumnList_t  = std::list<Column_t>;

    //! Database type containing multiple tables.
    /*! An example of creating a table.
     *
     * ```cpp
     * DataBase_t db_1 = {
     *     {"Table_1", column_list_1},
     *     {"Table_2", column_list_2},
     * };
     * ```
     *
     * or,
     *
     * ```cpp
     * DataBase_t db_1;
     * db_1["Table_1"] = column_list_1;
     * db_1["Table_2"] = column_list_2;
     * ```
     */
    using TableInfo_t  = std::map<std::string, Column_t>;
    using ResultElement_t = std::map<std::string,std::string>;
    using Result_t = std::vector<ResultElement_t>;
    struct ExecResult_t{
	std::string in_sql;
	Result_t result;
    };

    class Fetcher{
	public:

	    Fetcher();

	    //! Constructor. Open database.
	    /*!
	     * This constructor opens the database. 
	     * The database is opened for reading and writing,
	     * and is created if it does not already exist.
	     * \param[in] db_name name of a database to be opened.
	     */
	    Fetcher(const std::string& db_name); 

	    //! Open database.
	    /*!
	      \param[in] db_name name of a database to be opened.
	      \param[out] err_msg error message.
	      \param[in] flags Optional flags detemine the way of open. 
	          See [here](https://www.sqlite.org/c3ref/c_open_autoproxy.html) for the detail.
              \param[in] zVfs the name of the sqlite3_vfs object that defines 
	          the operating system interface that the new database connection should use.
		  See [here](https://www.sqlite.org/c3ref/vfs.html) for the detail.
	      \retval SQLITE_OK Successfully open the database.
	      \retval others Some errors occured. See [here](https://www.sqlite.org/rescode.html)
	          for the detail.
            */
	    int32_t open(const std::string& db_name,
		    std::string& err_msg,
		    const int32_t& flags= (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE), 
		    const char* zVfs=nullptr);

	    //! Execute SQLite query
	    /*!
	     * \param[in] query SQLite query to be executed
	     * \param[out] err_msg error message
	     * \retval result of the input query.
	     */
	    ExecResult_t exec(const std::string& query, std::string& err_msg);

	    //! Execute SQLite query
	    /*!
	     * \param[in] query SQLite query to be executed
	     * \param[out] err_msg error message
	     * \retval result of the input query.
	     */
	    std::list<ExecResult_t> execSeparate(const std::string& query, std::string& err_msg);

	    //! Dump result of exec function into string.
	    /*!
	     * \param[in] res Result of exec function.
	     * \retval string formed result.
	     */
	    std::string dump(const ExecResult_t& res) const;
	    
	    //! Dump result of exec function into string.
	    /*!
	     * \param[in] res Result of exec function.
	     * \retval string formed result.
	     */
	    std::string dump(const std::list<ExecResult_t>& res_list) const;

	    //! Fetch column list from result of executed query for SELECT.
	    /*!
	     * \param[in] res Result output by exec function with SELECT queries.
	     * \param[out] err_msg Error message. In case of fething successfully, this becomes empty.
	     * \retval list of columns selected by queries.
	     */
	    ColumnList_t fetchColumn(const ExecResult_t& res, std::string& err_msg) const;

	    //! Fetch column list from result of executed query for SELECT.
	    /*!
	     * \param[in] res Result output by exec function with SELECT queries.
	     * \param[out] err_msg Error message. In case of fething successfully, this becomes empty.
	     * \retval list of columns selected by queries.
	     */
	    Column_t fetchColumn(const ExecResult_t& res, const size_t& id, std::string& err_msg) const;
	    
	    //! Get master table.
	    /*!
	     * \param[out] err_msg error message
	     * \retval Table information. This is usefull to create colmuns
	     *     corresponded to tables in database.
	     */
	    TableInfo_t getTableInfo(std::string& err_msg);
	    
	    //! Get master table.
	    /*!
	     * \param[out] table_name name of target table
	     * \param[out] err_msg error message
	     * \retval Table information. This is usefull to create colmuns
	     *     corresponded to tables in database.
	     */
	    Column_t getTableInfo(const std::string table_name, std::string& err_msg);

	    //! Generate a query to create table from a column list.
	    /*! If the column_list doen't contain a data as primary key,
	     *  a row with primary key is automatically created.
	     * \param[in] name name of table to be created.
	     * \param[in] column_list list of columns to be saved in table.
	     * \param[out] err_msg Error message.
	     * \retval Query message to create table.
	     */
	    std::string genQueryCreate(const std::string& name,
		    const ColumnList_t& column_list, std::string& err_msg);

	    //! Generate queries to create table from a table info.
	    /*!
	     * \param[in] table_info Table information containing definition of tables.
	     * \param[out] err_msg Error message.
	     * \retval Query message to create table.
	     */
	    std::string genQueryCreate(const TableInfo_t& table_info, std::string& err_msg);

	    //! Generate a query to insert a column.
	    /*!
	     * \param[in] name name of a table to be inserted a column into.
	     * \param[in] col A column to be inserted into the table.
	     * \param[out] err_msg Error message.
	     * \retval Query message to insert the column into the table.
	     */
	    std::string genQueryInsert(const std::string& table_name,
		    const Column_t& col, std::string& err_msg);

	    //! Generate a query to update a column.
	    /*! This is used to update a column which does not contain primary key,
	     *  and the user have to point at the target column by input primary hey.
	     * \param[in] name name of a table to be updated.
	     * \param[in] col An updated column.
	     * \param[in] key Primary key of the column.
	     * \param[out] err_msg Error message.
	     * \retval Query message to insert the column into the table.
	     */
	    std::string genQueryUpdate(const std::string table_name,
		    const Column_t& col, const int64_t& key, std::string& err_msg);

	    //! Generate a query to update a column.
	    /*! This is used to update a column which contains primary key.
	     * \param[in] name name of a table to be updated.
	     * \param[in] col An updated column.
	     * \param[out] err_msg Error message.
	     * \retval Query message to insert the column into the table.
	     */
	    std::string genQueryUpdate(const std::string& table_name,
		    const Column_t& col, std::string& err_msg);

	private:
	    ExecResult_t last_exec_result_;
	    TableInfo_t last_table_info_;
	    std::string last_err_;

	    bool is_opened_{false};
	    sqlite3* db_ptr_{nullptr};


	    
    };
    
}
#endif
