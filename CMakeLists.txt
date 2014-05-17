project(gitManager)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(gitManager_SRCS gitManager.cpp main.cpp)
qt4_automoc(${gitManager_SRCS})
add_executable(gitManager ${gitManager_SRCS})
target_link_libraries(gitManager ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS gitManager RUNTIME DESTINATION bin)
