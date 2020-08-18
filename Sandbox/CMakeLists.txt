project(Sandbox)

add_executable(Sandbox main.cpp)

target_link_libraries(Sandbox PRIVATE common_options)
target_link_libraries(Sandbox PRIVATE Webon)
