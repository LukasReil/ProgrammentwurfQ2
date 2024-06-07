cmake_minimum_required(VERSION 3.20)

project(API VERSION 1.0)

add_library(API STATIC
	${PROJECT_SOURCE_DIR}/Consumer.cpp
	${PROJECT_SOURCE_DIR}/Consumer.h
	${PROJECT_SOURCE_DIR}/Producer.cpp
	${PROJECT_SOURCE_DIR}/Producer.h
	${PROJECT_SOURCE_DIR}/Dispatcher.cpp
	${PROJECT_SOURCE_DIR}/Dispatcher.h
	${PROJECT_SOURCE_DIR}/Umwelt.cpp
	${PROJECT_SOURCE_DIR}/Umwelt.h
)