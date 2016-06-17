cmake_minimum_required(VERSION 3.0.0)
cmake_policy(VERSION 3.0.0)

project(dungeon-game)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fvisibility=hidden -march=native")
	if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat-pedantic -Wno-padded")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	endif()
endif()

find_path(ASIO_INCLUDE_DIR asio.hpp)
if(ASIO_INCLUDE_DIR)
	add_definitions(-DASIO_STANDALONE)
	if(WIN32 AND NOT MSVC)
		set(ASIO_LIBRARIES ws2_32 wsock32)
		add_definitions(-D_WIN32_WINNT=0x0600) # from vista/server2008
	elseif(UNIX)
		set(ASIO_LIBRARIES -pthread)
	endif()
else()
	message(FATAL_ERROR "Could not find Asio")
endif()

set(SRC_LIST
	Command
	CommandFactory
	commands/ExitCommand
	ConsoleController
	Controller
	global
	main
	PlayerController
	Server)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR} ${ASIO_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ASIO_LIBRARIES})
