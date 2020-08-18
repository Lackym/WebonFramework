project(Webon LANGUAGES CXX)

set(WEBON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Webon/Include)

#create webon target and set options
add_library(Webon SHARED)
target_link_libraries(Webon PRIVATE common_options)
target_compile_definitions(Webon PRIVATE BUILD_WEBON)

#add include dirs to the Webon
target_include_directories(Webon PRIVATE src)
target_include_directories(Webon PUBLIC ${WEBON_INCLUDE_DIR})

#link vendors to the Webon
target_link_libraries(Webon PUBLIC Boost)

#add all headers to the Webon
FILE(GLOB_RECURSE WEBON_HEADERS **.h)
target_sources(Webon PRIVATE ${WEBON_HEADERS})

#add source code to the Webon
FILE(GLOB_RECURSE WEBON_SOURCE **.cpp)
target_sources(Webon PRIVATE ${WEBON_SOURCE})

#install Webon
install(TARGETS Webon
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY ${WEBON_INCLUDE_DIR}/Webon
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
