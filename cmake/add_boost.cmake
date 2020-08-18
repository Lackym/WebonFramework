#configuration
set(BOOST_ROOT "C:\\Program Files\\boost\\boost_1_74_0")
set(Boost_USE_STATIC_LIBS ON)

#require components
find_package(Boost 1.74.0 REQUIRED COMPONENTS
	date_time
	regex
	system
	thread
)

add_library(Boost INTERFACE)
target_include_directories(Boost INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(Boost INTERFACE ${Boost_LIBRARIES})