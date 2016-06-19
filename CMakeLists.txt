CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(Bibliography_Processor)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES main.cpp
		src/parser/BibParser.cpp src/parser/BibParser.h
		src/parser/model/KeyValue.cpp src/parser/model/KeyValue.h
		src/parser/model/Bib.cpp src/parser/model/Bib.h
		src/doi/Crossref.cpp src/doi/Crossref.h
		src/NameValidator.cpp src/NameValidator.h
		src/api/UrlBuilder.cpp src/api/UrlBuilder.h
		src/StringUtils.cpp src/StringUtils.h
		src/api/Request.cpp src/api/Request.h
		src/Config.cpp src/Config.h
		)

SET(TEST_SOURCE_FILES
		test/BibParserTest.cpp
		)
ADD_EXECUTABLE(Bibliography_Processor ${SOURCE_FILES} ${TEST_SOURCE_FILES})

ADD_SUBDIRECTORY("lib/jsoncpp/")

ADD_SUBDIRECTORY("lib/googletest/")

SET(ENABLE_XML OFF CACHE BOOL "Enable the XML" FORCE)
SET(ENABLE_JSON OFF CACHE BOOL "Enable the JSON" FORCE)
SET(ENABLE_MONGODB OFF CACHE BOOL "Enable MongoDB" FORCE)
SET(ENABLE_NETSSL OFF CACHE BOOL "Enable NetSSL" FORCE)
SET(ENABLE_CRYPTO OFF CACHE BOOL "Enable Crypto" FORCE)
SET(ENABLE_DATA OFF CACHE BOOL "Enable Data" FORCE)
SET(ENABLE_DATA_SQLITE OFF CACHE BOOL "Enable Data SQlite" FORCE)
SET(ENABLE_DATA_MYSQL OFF CACHE BOOL "Enable Data MySQL" FORCE)
SET(ENABLE_DATA_ODBC OFF CACHE BOOL "Enable Data ODBC" FORCE)
SET(ENABLE_ZIP OFF CACHE BOOL "Enable Zip" FORCE)
SET(ENABLE_PAGECOMPILER OFF CACHE BOOL "Enable PageCompiler" FORCE)
SET(ENABLE_PAGECOMPILER_FILE2PAGE OFF CACHE BOOL "Enable File2Page" FORCE)


ADD_SUBDIRECTORY("lib/poco")

INCLUDE_DIRECTORIES(
		"src/"
		${gtest_SOURCE_DIR}/include
		${gtest_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
		gtest gtest_main
		PocoNet PocoUtil
		jsoncpp_lib_static)
