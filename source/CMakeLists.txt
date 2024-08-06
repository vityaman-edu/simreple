get_filename_component(SIMREPLE_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(SIMREPLE_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

add_executable(
    ${PROJECT_NAME} 
    ${SIMREPLE_SOURCE_PATH}/Main.cpp
    ${SIMREPLE_SOURCE_PATH}/Shell.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${SIMREPLE_INCLUDE_PATH}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${REPLXX_STATIC}
    ${ANTLR4_STATIC}
)
