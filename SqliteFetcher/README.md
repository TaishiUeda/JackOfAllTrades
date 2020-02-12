
# SqliteFetcher

A minimul C++ STL based API for SQLite. 

Using this, you can create tables, insert columns, and update columns without 
traditional very long queries.
A code to create tables is written like below;

```cpp
/* Open database */
Fetcher sql_fetch("test.db");

//###############################################################
//  Creating table from table_info A
// 
// define the table scheme.
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

//execute query
ExecResult_t res = sql_fetch.exec(str, err_msg);
```

And, below is a code to get certain columns and save it into a ontainer;

```cpp
//Execute a query to "SELECT"
ExecResult_t res = sql_fetch.exec("SELECT city, population FROM area;", err_msg);

//save the result into container
ColumnList_t selected_2 = sql_fetch.fetchColumn(res, err_msg);

//The values in selected column can be gotten with STL function, and
//the type of value is automatically determined.
double pop;
std::string city;
for(auto i_sel2 = selected_2.begin(); i_sel2 != i_sel2_end; ++i_sel2){
    i_sel2->at("population").get(pop); 
    i_sel2->at("city").get(city);
    std::cout << city << ": population = " << pop << std::endl;
}
```

See [test code](test/main.cpp) if you would like to know more examples.

---

## Usuful containers

### 1. Column_t

Column_t has the string name tags and values.

#### Setting data types

```cpp
Column_t col = {
    {"ID", Data(INT64, PRIMARY_KEY)},
    {"First name", Data(TEXT)},
    {"Second name", Data(TEXT)},
    {"Age", Data(INT32)},
    {"Height_cm", Data(REAL)},
    {"Weight_kg", Data(REAL)},
};
```

#### Setting data values and each type is detemined automatically.

```cpp
Column_t col = {
    {"ID", Data(0, PRIMARY_KEY)},
    {"First name", Data("Alina")},
    {"Second name", Data("Rain")},
    {"Age", Data(28)},
    {"Height_cm", Data(168.2)},
    {"Weight_kg", Data(49,3)},
};
```
#### Setting data after constructed.

```cpp
Column_t col;
col["ID"] = Data(0, PRIMARY_KEY);
col["First name"] = Data("Alina");
col["Second name"] = Data("Rain");
col["Age"] = Data(28);
col["Height_cm"] = Data(168.2);
col["Weight_kg"] = Data(49,3);
```

### 2. ColumnList type. This is a vector of column.

### 3. Table_t. This has string name as keys and vectors of column data.

#### Examples for creating a table.

```cpp
Table_t table = {
    {"list1", column_list_1},
    {"list2", column_list_2},
};
```

or,

```cpp
Table_t table
db_1["list1"] = column_list_1;
db_1["list2"] = column_list_2;
```

### 4. TableInfo_t to determin table schema.

#### Exanples for creating a TableInfo_t.

```cpp
TableInfo_t table_info = {
    {"user",{ 
    	    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
    	    {"name", Data(TEXT, NOT_NULL)},
    	    {"sex", Data(TEXT)},
    	    {"age", Data(INT8)},
    	    {"countory", Data(TEXT)},
    	    {"height_cm", Data(FLOAT)},
    	}
    },
    {"area",{ 
    	    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
    	    {"countory", Data("Japan", NOT_NULL | DEFAULT)},
    	    {"prefecture", Data(TEXT)},
    	    {"population", Data(DOUBLE)},
    	}
    }
};
```

or,

```cpp
Column_t user_col ={
    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
    {"name", Data(TEXT, NOT_NULL)},
    {"sex", Data(TEXT)},
    {"age", Data(INT8)},
    {"countory", Data(TEXT)},
    {"height_cm", Data(FLOAT)},
};
Column_t area_col ={
    {"ID", Data(INT64, PRIMARY_KEY | NOT_NULL)},
    {"countory", Data(TEXT, NOT_NULL)},
    {"prefecture", Data(TEXT)},
    {"population", Data(DOUBLE)},
};

TableInfo_t table_info;
table_info["user"] = user_col;
table_info["area"] = area_col;
```


---

## Function to create queries

Several functions to generate query as std::string from STL based containers.

1. sf::Fetcher::genQueryCreate()
    To generate query to create table.
2. sf::Fetcher::genQueryInsert()
    To generate query to insert columns.
3. sf::Fetcher::genQueryUpdate()
    To generate query to update a column.


---

## Function to execute query of SQL.

The main class "Fetcher" has only two function to execute query of SQL.

1. sf::Fetcher::exec()
    To execute queries and returns result in single struct ExecResult_t.
2. sf::Fetcher::execSeparate()
    To execute multiple queries and returns result in list of struct std::list<ExecResult_t>.


---

## Function to fetch selected columns into STL based containers

One functions to save result of "SELECT" query into ColumnList_t container.

1. sf::Fetcher::fetchColumn()
    To fetch and save output from "SELECT" query into container.


---

## Function to utiliry

1. sf::Fetcher::dump()
    Dump results into Json style string.


---

## Others

To know about other functions, see documents.<br />
This project is documented in Doxygen style. If you get documents, simply execute command below after install [Doxygen](http://www.doxygen.nl/i);

```
cd doc
doxygen
```

---

This software is released under the MIT License, see LICENSE.txt.
