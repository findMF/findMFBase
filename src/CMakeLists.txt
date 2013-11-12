# Copyright : ETH Zurich
# License   : three-clause BSD license
# Authors   : Witold Wolski
# for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

SET(BOOST_MIN_VERSION "1.46.0")
find_package( Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS filesystem system iostreams thread regex program_options unit_test_framework)
if(Boost_FOUND)
  SET( inc ${inc} ${Boost_INCLUDE_DIRS} )
  SET( ${boostlib} ${Boost_LIBRARIES} )
else()
  message(STATUS ">>>>> Couldn't find Boost <<<<< ")
endif()
message( STATUS "lib ${lib}" )
message( STATUS "inc boost ${inc}" )
message( STATUS ">>>> ${Boost_LIBRARIES} <<<<" )

include(ExternalProject)
include(externalgoogletest)
set(inc ${inc} ${Gtest_SourceDir})
message(STATUS "Gtest_LIBRARY ${Gtest_LIBRARY}")
message(STATUS "inc ${inc}")


ENABLE_TESTING()

ADD_SUBDIRECTORY(base)


