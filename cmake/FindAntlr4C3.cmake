include(FetchContent)

FetchContent_Declare(
    antlr4-c3
    GIT_REPOSITORY https://github.com/vityaman/antlr4-c3
    GIT_TAG 138-port-cpp-distribute
    SOURCE_SUBDIR ports/cpp
)

FetchContent_MakeAvailable(antlr4-c3)

set(ANTLR4C3_STATIC antlr4-c3)
