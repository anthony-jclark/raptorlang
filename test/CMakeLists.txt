
FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_BIN ${PROJECT_NAME}-UnitTests)

ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_INCLUDE_DIRECTORIES (${test_BIN} SYSTEM PUBLIC ${MAINFOLDER}/support/Catch/single_include/)

# configure unit tests via CTest
ENABLE_TESTING ()
ADD_TEST (run ${MAINFOLDER}/bin/${test_BIN})

ADD_TEST (list ${test_BIN} --list-tests)
SET_TESTS_PROPERTIES (list PROPERTIES PASS_REGULAR_EXPRESSION "[0-9]+ test cases")

ADD_TEST (tags ${test_BIN} --list-tags)
SET_TESTS_PROPERTIES (tags PROPERTIES PASS_REGULAR_EXPRESSION "[0-9]+ tags")
