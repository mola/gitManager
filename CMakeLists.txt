cmake_minimum_required(VERSION 2.6)
SET ( CMAKE_BUILD_TYPE Debug )
SET(CMAKE_INSTALL_PREFIX, "/usr")

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(QT_USE_QTGUI TRUE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)


include_directories (
	${CMAKE_SOURCE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}
	${Qt5Widgets_INCLUDES}
	 /usr/include/qt5/QtNetwork
	 /usr/include/qt5/QtCore
	 /usr/include/qt5/QtConcurrent
	 /usr/include/qt5/QtOpenGL
	)
	
add_definitions(${Qt5Widgets_DEFINITIONS})

add_subdirectory(src)