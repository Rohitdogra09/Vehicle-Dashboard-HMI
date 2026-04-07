cmake_minimum_required(VERSION 3.19)
project(MachineHMI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTORCC ON)


qt_standard_project_setup()

qt_add_executable(MachineHMI
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui


    evscreen.h evscreen.cpp evscreen.ui
    resources.qrc


)

target_link_libraries(MachineHMI
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS MachineHMI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MachineHMI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
