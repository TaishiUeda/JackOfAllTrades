cmake_minimum_required (VERSION 2.8)
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

# projectname is the same as the main-executable
project(CppSqlPerserTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  add_definitions('-g')
  add_definitions('-Wall')
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
  add_definitions('-O3')
endif()

# For executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(${PROJECT_NAME}
    ../src/CppSqlParser.cpp
    main.cpp
)
target_include_directories(${PROJECT_NAME}
PRIVATE ../src
PRIVATE ./
)
target_link_libraries(${PROJECT_NAME}
    sqlite3
    )
# For static library
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
#add_library(${PROJECT_NAME} STATIC 
#  ${PROJECT_NAME}.cpp
#)

# For shared library
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
#add_library(${PROJECT_NAME} SHARED 
#  ${PROJECT_NAME}.cpp
#)

#add_custom_target(${PROJECT_NAME}-symlink ALL ln --force -s ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
