include(ExternalProject)

ExternalProject_Add(
    replxx
    GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
    GIT_TAG master
    PREFIX ${CMAKE_BINARY_DIR}/replxx
    INSTALL_DIR ${CMAKE_BINARY_DIR}/replxx/install
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    TEST_COMMAND ""
)

set(REPLXX_INSTALLATION ${CMAKE_BINARY_DIR}/replxx/install)
set(REPLXX_INCLUDE_DIRS ${REPLXX_INSTALLATION}/include)
set(REPLXX_STATIC ${REPLXX_INSTALLATION}/lib/libreplxx.a)

include_directories(${REPLXX_INCLUDE_DIRS})
