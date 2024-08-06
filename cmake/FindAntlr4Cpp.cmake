set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/${ANTLR4_TAG}.zip)

if(NOT DEFINED ANTLR4_INCLUDED)
  set(ANTLR4_INCLUDED FALSE)
endif()

if(NOT ANTLR4_INCLUDED)
  set(ANTLR4_WITH_STATIC_CRT OFF)
  add_definitions(-DANTLR4CPP_STATIC)
  include(ExternalAntlr4Cpp)
  set(ANTLR4_STATIC antlr4_static)
  set(ANTLR4_INCLUDED TRUE)
endif()
