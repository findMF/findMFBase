# Copyright : ETH Zurich
# License   : three-clause BSD license
# Authors   : Witold Wolski
# for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#FIND_PACKAGE(Gtest REQUIRED)
#if(Gtest_FOUND)
#  message(STATUS "Gtest found" ${Gtest_INCLUDE_DIR})
#  message(STATUS "Gtest found" ${Gtest_LIBRARY})
#  SET(inc ${inc} ${Gtest_INCLUDE_DIR})
#else()
#  message(STATUS "!!!!!!!!!!!!!!!! Gtest not found !!!!!!!!!!!!!!!! ")
#  return()
#endif()

include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
# Add gtest
ExternalProject_Add(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    SVN_REVISION -r 664
    TIMEOUT 10
    #PATCH_COMMAND svn patch ${CMAKE_SOURCE_DIR}/gtest.patch ${CMAKE_BINARY_DIR}/ThirdParty/src/googletest
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

ExternalProject_Get_Property(googletest binary_dir)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Gtest_LIBRARY ${binary_dir}/DebugLibs)
ELSE(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Gtest_LIBRARY ${binary_dir}/ReleaseLibs)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")


message(STATUS "Gtest_LIBRARY ${Gtest_LIBRARY} <<<<<<<<<<<<<<<<<")

ADD_SUBDIRECTORY(basetest)
ADD_SUBDIRECTORY(filtertest)
ADD_SUBDIRECTORY(resampletest)
ADD_SUBDIRECTORY(statstest)
ADD_SUBDIRECTORY(mstest)
ADD_SUBDIRECTORY(chemistrytest)
ADD_SUBDIRECTORY(utilstest)

