cmake_minimum_required (VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

# projectname is the same as the main-executable
project(SqliteFetcher)

#output compile options for intelli-sence
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
#set configuration Release as default
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
#compile options set according to the configuration
if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
    set(OUT_TARGET_NAME ${PROJECT_NAME})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -O3 -march=native ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    set(OUT_TARGET_NAME ${PROJECT_NAME}_d)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -g3 -O0 -march=native ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g3 -O0 -march=native")
endif()

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   add_definitions(-DCOMPILEDWITHC0X)
   message(STATUS "Using flag -std=c++0x.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#----  set runtime output directory ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
##---- set library output directory ----
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#---- set archive output directory ----
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#------------------------------------------------------------------------
#             Settings depended on Project are from here
#------------------------------------------------------------------------

#-----include directories-------
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    )

if(BUILD_TEST)
    add_definitions(-DTest)
    #------search source files------
    file(GLOB_RECURSE SOURCE_FILES 
	"./src/*.cpp"
	"./test/*.cpp"
	)
    message(STATUS "source: ${SOURCE_FILES}")
    #------set attribute and source files to be built------
    add_executable(${OUT_TARGET_NAME}_test
	${SOURCE_FILES}
	)
    #------Libraries to be linked-------
    target_link_libraries(${OUT_TARGET_NAME}_test
	sqlite3
	)
endif()

#------search source files------
file(GLOB_RECURSE SOURCE_FILES 
    "./src/*.cpp"
    )
message(STATUS "source: ${SOURCE_FILES}")
#------set attribute and source files to be built------
add_library(${OUT_TARGET_NAME} SHARED
    ${SOURCE_FILES}
    )
#------Libraries to be linked-------
target_link_libraries(${OUT_TARGET_NAME}
    sqlite3
    )

##------set attribute and source files to be built------
#add_library(${OUT_TARGET_NAME} STATIC
#    ${SOURCE_FILES}
#)


#-------------------------------------------------------------------------------
#         Install setting
#-------------------------------------------------------------------------------
install(TARGETS ${OUT_TARGET_NAME}
    DESTINATION lib
    PERMISSIONS 
    OWNER_READ OWNER_WRITE OWNER_EXECUTE 
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    )

