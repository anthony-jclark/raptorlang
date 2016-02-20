

FILE (GLOB rar_SRCS *.cpp *.cxx *.cc)

ADD_COMPILE_OPTIONS (-fno-exceptions)


ADD_EXECUTABLE (rar_test ${rar_SRCS})


SET (LLVM_DIR "/usr/local/Cellar/llvm/3.6.2/share/llvm/cmake/")
FIND_PACKAGE (LLVM REQUIRED CONFIG)

MESSAGE (STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE (STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

TARGET_INCLUDE_DIRECTORIES (rar_test SYSTEM PUBLIC ${LLVM_INCLUDE_DIRS})
TARGET_COMPILE_DEFINITIONS (rar_test PUBLIC ${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM components
# that we wish to use
LLVM_MAP_COMPONENTS_TO_LIBNAMES (llvm_libs support core irreader)

# Link against LLVM libraries
TARGET_LINK_LIBRARIES (rar_test PUBLIC ${llvm_libs})

TARGET_LINK_LIBRARIES (rar_test PUBLIC "z" "pthread" "ffi" "m")
TARGET_LINK_LIBRARIES (rar_test PUBLIC ${rex_LIB}-${TEST})


IF (DEFINE_DEBUGGING)
    TARGET_COMPILE_DEFINITIONS (rar_test PUBLIC ${DEBUGGING})
ENDIF ()





# TARGET_INCLUDE_DIRECTORIES (
#     rar_test SYSTEM PUBLIC ${SUPPORT_PATH}/easyloggingpp/src/
# )
# TARGET_LINK_LIBRARIES (rar_test ${rex_LIB})



# LDFLAGS:  -L/usr/local/opt/llvm/lib
# CPPFLAGS: -I/usr/local/opt/llvm/include


# #
# # Create the "normal" version of the library
# #
# ADD_LIBRARY (${rar_LIB} STATIC ${rar_SRCS} ${TOKEN_HEADER} ${TOKEN_IMPLEM})
# TARGET_INCLUDE_DIRECTORIES (
#     ${rar_LIB} SYSTEM PUBLIC ${SUPPORT_PATH}/easyloggingpp/src/
# )

# #
# # Create a "testing" version of the library
# #
# ADD_LIBRARY (
#     ${rar_LIB}-${TEST} STATIC ${rar_SRCS} ${TOKEN_HEADER} ${TOKEN_IMPLEM}
# )

# TARGET_COMPILE_DEFINITIONS (
#     ${rar_LIB}-${TEST} PUBLIC "${TEST}"
#     # "DEBUGGING"
# )
