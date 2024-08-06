set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/${ANTLR4_TAG}.zip)
set(ANTLR4_RUNTIME antlr4_runtime)
set(ANTLR4_STATIC antlr4_static)

if(NOT TARGET ${ANTLR4_RUNTIME})
  set(ANTLR4_WITH_STATIC_CRT OFF)
  add_definitions(-DANTLR4CPP_STATIC)
  include(ExternalAntlr4Cpp)
  include_directories(${ANTLR4_INCLUDE_DIRS})
  set(ANTLR4_INCLUDED TRUE)
endif()

SET(ANTLR4_STATIC ${ANTLR4_STATIC_LIBRARIES})
