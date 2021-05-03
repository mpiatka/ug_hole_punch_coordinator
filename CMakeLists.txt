cmake_minimum_required(VERSION 3.5)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

target_link_libraries(hole_punch_coordinator PRIVATE
	pthread
		)

