

#
# Add the executable target
#
FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_BIN ${PROJECT_NAME}-UnitTests)
ADD_EXECUTABLE (${test_BIN} ${test_SRCS})


#
# Add definition for compiling the test version of code
#
TARGET_COMPILE_DEFINITIONS (${test_BIN} PUBLIC ${TEST})


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
TARGET_LINK_LIBRARIES (${test_BIN} ${rex_LIB}-${TEST})

