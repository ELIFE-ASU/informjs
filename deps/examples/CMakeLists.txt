link_libraries(${PROJECT_NAME}_static)
if (UNIX)
    link_libraries(m)
endif()

add_subdirectory(dist)
add_subdirectory(shannon)
add_subdirectory(timeseries)
add_subdirectory(utilities)
