get_filename_component(SIMREPLE_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(SIMREPLE_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

antlr_generate(
    ${SIMREPLE_SOURCE_PATH}/antlr/SimpLa.g4 
    ${CMAKE_CURRENT_BINARY_DIR}/antlr
)

add_executable(
    ${PROJECT_NAME} 
    ${SIMREPLE_SOURCE_PATH}/Main.cpp
    ${SIMREPLE_SOURCE_PATH}/Shell.cpp
    ${SIMREPLE_SOURCE_PATH}/Machine.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaBaseListener.cpp  
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaLexer.cpp     
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaBaseVisitor.cpp   
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaListener.cpp  
    ${CMAKE_CURRENT_BINARY_DIR}/antlr/SimpLaVisitor.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${SIMREPLE_INCLUDE_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${REPLXX_STATIC}
    ${ANTLR4_STATIC}
)
