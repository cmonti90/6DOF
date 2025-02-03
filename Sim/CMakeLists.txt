
# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


## Add subdirectories for Sim targets
add_subdirectory(Environment)
add_subdirectory(Hardware)
add_subdirectory(Runner)
add_subdirectory(World)


# Create symlinks to the bin and lib directories during the build phase
add_custom_target(
    create_symlinks ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/bin ${CMAKE_CURRENT_SOURCE_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib
    COMMENT "Creating symlinks to the bin and lib directories"
)