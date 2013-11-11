# Copyright : ETH Zurich
# License   : three-clause BSD license
# Authors   : Witold Wolski
# for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

IF(NOT DEFINED ENABLE_TESTING)
    SET(ENABLE_TESTING "ON")
ENDIF()
SET(ENABLE_TESTING ${ENABLE_TESTING}
    CACHE BOOL "Build with test ?"
    FORCE)
