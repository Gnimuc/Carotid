# Set Public Headers
set(pub_hdrs 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/carotid/LibCarotid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/carotid/Platform.h
)
set_target_properties(Carotid PROPERTIES PUBLIC_HEADER "${pub_hdrs}")

# Install CompilationDatabase
set_target_properties(Carotid PROPERTIES EXPORT_COMPILE_COMMANDS true)
set(ccmds_json ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
if(EXISTS ${ccmds_json})
    message(STATUS "Found CompilationDatabase File: " ${ccmds_json})
    install(FILES ${ccmds_json} DESTINATION share)
endif()

# Install Binaries
install(TARGETS Carotid
        EXPORT CarotidTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        INCLUDES DESTINATION include/carotid
        PUBLIC_HEADER DESTINATION include/carotid)

# Install CMake targets
install(EXPORT CarotidTargets
        NAMESPACE Carotid::
        FILE Carotid-config.cmake
        DESTINATION lib/cmake/Carotid)