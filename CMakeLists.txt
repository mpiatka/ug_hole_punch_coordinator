cmake_minimum_required(VERSION 3.14)

project(hole_punch_coordinator
	LANGUAGES CXX
	VERSION 0.0.1
	)

set(SOURCES
	main.cpp
	hole_punch_coordinator.cpp
	client.cpp
	message.cpp
	room.cpp
	)

add_executable(hole_punch_coordinator main.cpp ${SOURCES})

set_property(TARGET hole_punch_coordinator PROPERTY CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	include(CheckPIESupported)
	check_pie_supported()
	set_target_properties(hole_punch_coordinator PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
	target_compile_definitions(hole_punch_coordinator PRIVATE FORTIFY_SOURCE=2)
	target_compile_options(hole_punch_coordinator PRIVATE -fstack-protector-strong)
	target_compile_options(hole_punch_coordinator PRIVATE -Wall -Wextra -pedantic)
	target_link_options(hole_punch_coordinator PRIVATE "SHELL:-z relro")
	target_link_options(hole_punch_coordinator PRIVATE "SHELL:-z now")
endif()

target_link_libraries(hole_punch_coordinator PRIVATE
	pthread
		)

