
#
# Add definition for compiling the test version of code
#
ADD_DEFINITIONS (-DTESTING)
#
# Add the executable target
#
FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_BIN ${PROJECT_NAME}-UnitTests)
ADD_EXECUTABLE (${test_BIN} ${test_SRCS})


#
# Link the target with support files (header only libraries).
#
TARGET_INCLUDE_DIRECTORIES (
    ${test_BIN} SYSTEM PUBLIC ${SUPPORT_PATH}/Catch/single_include/
)
TARGET_INCLUDE_DIRECTORIES (${test_BIN} SYSTEM PUBLIC ${SRC_PATH})


#
# Link the target with libraries
#
TARGET_LINK_LIBRARIES (${test_BIN} ${rex_LIB}-TESTING)


#
# Add a target for running the tests from the command line
#
ADD_CUSTOM_TARGET(
    check "${BIN_PATH}/${test_BIN}" DEPENDS ${test_BIN}
    COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS}
)

# ADD_CUSTOM_TARGET(
#     list "${BIN_PATH}/${test_BIN}" "--list-tests" DEPENDS ${test_BIN}
#     COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS}
# )

# ADD_CUSTOM_TARGET(
#     tags "${BIN_PATH}/${test_BIN}" "--list-tags" DEPENDS ${test_BIN}
#     COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS}
# )

# ADD_CUSTOM_TARGET(
#     time "${BIN_PATH}/${test_BIN}" "-sd yes" DEPENDS ${test_BIN}
#     COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS}
# )
