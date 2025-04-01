add_executable(citra_room_launcher
    citra_room_launcher.c
)

set_target_properties(citra_room_launcher PROPERTIES OUTPUT_NAME "azahar-room")

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(citra_room_launcher PRIVATE -Wno-incompatible-pointer-types)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS citra_room_launcher RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
