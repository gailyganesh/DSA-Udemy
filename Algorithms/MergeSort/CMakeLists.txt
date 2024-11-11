project(MergeSort)

add_executable(${PROJECT_NAME}exe merge_sort.cpp merge_sort.h)

set_target_properties(${PROJECT_NAME}exe
    PROPERTIES
        FOLDER "Algorithms/${PROJECT_NAME}" # folder name
    )

install(TARGETS ${PROJECT_NAME}exe DESTINATION ${CMAKE_INSTALL_PREFIX})

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
