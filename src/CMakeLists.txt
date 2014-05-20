project(gitManager)


set(gitManager_SRCS 
    repositorymodel.cpp 
    repositorynode.cpp 
    sessionmanager.cpp
    qrepo.cpp 
    gitcore.cpp 

    gitManager.cpp
    globalsettings.cpp
    main.cpp
    
    docks/dockprojects.cpp
    about/aboutdialog.cpp
    )

set(gitManager_UIS 
    main.ui
    docks/dockprojects.ui
    about/aboutdialog.ui
    )

set ( gitManager_RSCS
	resource/resource.qrc
	)
QT5_WRAP_UI (UIS ${gitManager_UIS}) 
QT5_add_resources( RSCS ${gitManager_RSCS} )

add_executable(gitManager ${gitManager_SRCS} ${UIS} ${RSCS})
qt5_use_modules(gitManager Gui Widgets PrintSupport )

target_link_libraries(gitManager
		      -lgit2
		      )
install(TARGETS gitManager RUNTIME DESTINATION bin)

