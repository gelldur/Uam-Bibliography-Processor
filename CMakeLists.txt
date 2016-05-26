CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(Bibliography_Processor)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES main.cpp
		src/parser/BibParser.cpp src/parser/BibParser.h
		src/parser/model/KeyValue.cpp src/parser/model/KeyValue.h
		src/parser/model/Bib.cpp src/parser/model/Bib.h
		)
SET(TEST_SOURCE_FILES
		test/BibParserTest.cpp
		)
ADD_EXECUTABLE(Bibliography_Processor ${SOURCE_FILES} ${TEST_SOURCE_FILES})


ADD_SUBDIRECTORY("lib/googletest/")

INCLUDE_DIRECTORIES(
		"src/"
		${gtest_SOURCE_DIR}/include
		${gtest_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} gtest gtest_main)

