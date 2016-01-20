
#
# Compile the lexer and parser into object files
#
ADD_SUBDIRECTORY (rex)

# ADD_SUBDIRECTORY (rar)

#
# Add the executable target
#
FILE (GLOB project_SRCS *.cpp *.cxx *.cc)
SET (project_BIN ${PROJECT_NAME})
ADD_EXECUTABLE (${project_BIN} ${project_SRCS})


#
# Link the target with support files (header only libraries).
#
TARGET_INCLUDE_DIRECTORIES (
    ${project_BIN} SYSTEM PUBLIC ${SUPPORT_PATH}/cxxopts/src/
)
TARGET_INCLUDE_DIRECTORIES (
    ${project_BIN} SYSTEM PUBLIC ${SUPPORT_PATH}/easyloggingpp/src/
)

#
# Link the target with libraries
#
TARGET_LINK_LIBRARIES (${project_BIN} ${rex_LIB})


#
# Add a version property to the target name
#
SET_TARGET_PROPERTIES (
    ${project_BIN} PROPERTIES
    VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}"
    OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1
)


#
# Add a target for running the program without arguments
#
ADD_CUSTOM_TARGET (
    run "${BIN_PATH}/${project_BIN}" DEPENDS ${project_BIN}
    COMMENT "Running program..." VERBATIM SOURCES ${project_SRCS}
)

