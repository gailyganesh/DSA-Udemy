project(DoublyLinkedList)

add_executable(${PROJECT_NAME} doubly_linked_list.cpp doubly_linked_list.h)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER ${PROJECT_NAME} # folder name
    )

target_link_libraries(${PROJECT_NAME} PRIVATE DoublyLinkedListNode)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
