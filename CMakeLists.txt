project(gitManager)
cmake_minimum_required(VERSION 2.6)
SET ( CMAKE_BUILD_TYPE Debug )
SET(CMAKE_INSTALL_PREFIX, "/usr")

set(CMAKE_AUTOMOC ON)
  
set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

set(gitManager_SRCS 
    gitManager.cpp
    main.cpp
    )

set(gitManager_UIS 
    main.ui
    )

QT5_WRAP_UI (UIS ${gitManager_UIS}) 

add_executable(gitManager ${gitManager_SRCS})
qt5_use_modules(gitManager Gui Widgets PrintSupport )

target_link_libraries(gitManager)
install(TARGETS gitManager RUNTIME DESTINATION bin)
