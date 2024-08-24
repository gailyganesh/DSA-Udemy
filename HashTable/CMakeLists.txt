project(HashTable)

add_executable(${PROJECT_NAME} hash_table.cpp hash_table.h)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER ${PROJECT_NAME} # folder name
    )

target_link_libraries(${PROJECT_NAME} PRIVATE HashTableLLNode)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
