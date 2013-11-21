#Author : Witold Wolski

include_directories(${inc})
link_directories(${Gtest_LIBRARY})

ADD_EXECUTABLE(morphologytest morphologytest.cpp )
TARGET_LINK_LIBRARIES(morphologytest  ${Boost_LIBRARIES}  )

ADD_EXECUTABLE(backgroundsubtracttest backgroundsubtracttest.cpp )
TARGET_LINK_LIBRARIES(backgroundsubtracttest  ${Boost_LIBRARIES} )

ADD_EXECUTABLE(filterutilstest2 filterutilstest2.cpp )
TARGET_LINK_LIBRARIES(filterutilstest2  ${Boost_LIBRARIES})

ADD_EXECUTABLE(gaussfiltertest gaussfiltertest.cpp )
TARGET_LINK_LIBRARIES(gaussfiltertest  ${Boost_LIBRARIES} )


add_test(NAME morphologytest
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
COMMAND ${BinOut}/morphologytest )
set_tests_properties(morphologytest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")

add_test(NAME backgroundsubtracttest
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
COMMAND ${BinOut}/backgroundsubtracttest )
set_tests_properties(backgroundsubtracttest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")

add_test(NAME filterutilstest
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
COMMAND ${BinOut}/filterutilstest )
set_tests_properties(filterutilstest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")

add_test(NAME gaussfiltertest
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
COMMAND ${BinOut}/gaussfiltertest )
set_tests_properties(gaussfiltertest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")


#add_test(NAME mexhatfiltertest
#WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#COMMAND ${BinOut}/mexhatfiltertest )
#set_tests_properties(mexhatfiltertest PROPERTIES ENVIRONMENT "${LD_VARNAME}=${LD_PATH}")
