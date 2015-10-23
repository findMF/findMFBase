#Author : Witold Wolski

PROJECT(findMFBase)

#############################################################################
# cmake setup
#############################################################################
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

#############################################################################
# Versioning
#############################################################################
INCLUDE(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC MSTK_VERSION)


#############################################################################
# build type
#############################################################################

include(findmfDefaults)
include(BuildType)
message(STATUS "CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")

IF(MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS )
ELSE(MSVC)
    ADD_DEFINITIONS(-DWall)
    SET(CMAKE_CXX_FLAGS_RELENABLEDEBINFO "-O3 -g -std=c++0x")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -std=c++0x")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -std=c++0x")
    SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -Wall -ggdb3 -std=c++0x")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-value")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")
    IF(ENABLE_COVERAGE)
        IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
            SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
        ELSE(CMAKE_BUILD_TYPE STREQUAL "Debug")
            MESSAGE(FATAL_ERROR "Coverage analysis requires a DEBUG build")
        ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    ENDIF(ENABLE_COVERAGE)
ENDIF(MSVC)
# build static or shared libraries
# OPTION(BUILD_SHARED_LIBS "Build MSTK and helper libraries as shared libs (default=OFF)." OFF)

add_definitions("-DCMAKE_VERBOSE_MAKEFILE=ON")

#############################################################################
##define output location
#############################################################################
set(BinOut ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}out/${} )
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BinOut} )
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BinOut} )
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BinOut} )

#############################################################################
# header locations
#############################################################################

SET(inc ${inc} ${CMAKE_SOURCE_DIR})
SET(inc ${inc} ${CMAKE_SOURCE_DIR}/include)

#############################################################################
# QT tweak so that it sees headers
#############################################################################
file(GLOB Demo_HEADERS "sql/*.sql" "include/*.h" "include/**/*.h" "include/**/**/*.h"
 "include/**/**/**/*.h" "src/**/*.h" "src/**/**/*.h" ".travis.yml")
add_library(headers SHARED ${Demo_HEADERS} Dummy.cpp)


#############################################################################
# regression tests
#############################################################################

IF (ENABLE_TESTING)
    INCLUDE(CTest)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(src)
ENDIF(ENABLE_TESTING)


#############################################################################
# documentation
#############################################################################
CONFIGURE_FILE(${findMFBase_SOURCE_DIR}/doc/Doxyfile.cmake
    ${findMFBase_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
)
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    # add w/ the ALL option to make sure the docs are built for the install
     ADD_CUSTOM_TARGET(doc ALL
        COMMAND ${DOXYGEN} ${findMFBase_BINARY_DIR}/doc/Doxyfile)
     INSTALL(DIRECTORY ${findMFBase_BINARY_DIR}/doc/html
        DESTINATION doc
        COMPONENT doc
    )
ENDIF(DOXYGEN_FOUND)

#############################################################################
# installation
#############################################################################
# location, location, location
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX
      "/usr/local" CACHE PATH "findMFBase install prefix" FORCE
     )
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# headers
  INSTALL(DIRECTORY ${findMFBase_SOURCE_DIR}/include/
      DESTINATION include
      COMPONENT headers)

# documentation
  INSTALL(DIRECTORY ${findMFBase_BINARY_DIR}/doc
      DESTINATION doc
      COMPONENT documentation
      PATTERN "Doxyfile" EXCLUDE)


#############################################################################
# summary
#############################################################################
MESSAGE(STATUS)
MESSAGE(STATUS "-----------------------------------------")
MESSAGE(STATUS "System version: ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}")
MESSAGE(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
MESSAGE(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "MSTK Version: ${MSTK_VERSION}")
MESSAGE(STATUS "Global logging level: ${LOGGING_LEVEL}")
MESSAGE(STATUS "Regression tests: ${ENABLE_TESTING}")
MESSAGE(STATUS "Coverage analysis: ${ENABLE_COVERAGE}")
MESSAGE(STATUS "Boost version: ${Boost_VERSION}=${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost.SUBMINOR_VERSION}")
MESSAGE(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Boost library dir:  ${Boost_LIBRARY_DIRS}")
MESSAGE(STATUS "-----------------------------------------")
MESSAGE(STATUS)




