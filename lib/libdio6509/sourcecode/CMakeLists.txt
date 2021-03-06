cmake_minimum_required(VERSION 2.8)

project(libdio6509 CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DkLittleEndian=1 -DkGNU=1 -DkBAR0Only=1 -g") 

set(HEADERS 
	dataHelper.h
	devices.h
	eepromHelper.h
	iRegAccessor.h
	osiBus.h
	osiTypes.h
	rtsiResetHelper.h
	tCHInCh.cpp
	tCHInCh.h
	tCHInChValues.h
	tChpServices.cpp
	tChpServices.h
	tChpServicesValues.h
	tDioPorts.h
	tDioPortsValues.h
	tDioRegAccessor.h
	tPCIe6509.h
	tPCIe6509Values.h
	tPfiPorts.h
	tPfiPortsValues.h
	tPfiRegAccessor.h
	tPortHelperFactory.h
	tPortHelper.h
	tStaticDio.h
	tStaticDioValues.h
	tCHInCh.ipp
	tChpServices.ipp
	tDioPorts.ipp
	tPCIe6509.ipp
	tPfiPorts.ipp
	tStaticDio.ipp
	dio6509.h

)
set(SOURCES 
	dataHelper.cpp
	devices.cpp
	eepromHelper.cpp
	rtsiResetHelper.cpp
	tCHInCh.cpp
	tChpServices.cpp
	tDioPorts.cpp
	tDioRegAccessor.cpp
	tPCIe6509.cpp
	tPfiPorts.cpp
	tPfiRegAccessor.cpp
	tPortHelper.cpp
	tPortHelperFactory.cpp
	tStaticDio.cpp
	osiBus.cpp
	dio6509.cpp
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(dio6509 SHARED ${SOURCES})

install (TARGETS dio6509 DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)
