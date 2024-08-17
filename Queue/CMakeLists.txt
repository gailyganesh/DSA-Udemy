project(Queue)

add_executable(${PROJECT_NAME} queue.cpp queue.h)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER ${PROJECT_NAME} # folder name
    )

target_link_libraries(${PROJECT_NAME} PRIVATE LinkedListNode)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
