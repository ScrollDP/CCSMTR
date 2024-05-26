cmake_minimum_required(VERSION 3.5)

project(CCSMTR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets SerialPort REQUIRED)

set(SOURCES
        src/main.cpp
        src/mainWindow/mainWindow.cpp
        src/mainWindow/mainWindow.h
        "src/station_controll/stationControll.cpp"
        "src/station_controll/stationControll.h"
        src/connection/DCC-EX/dccEx.cpp
        src/connection/DCC-EX/dccEx.h
        src/connection/Intelibox_I/intelibox_I.cpp
        src/connection/Intelibox_I/intelibox_I.h
)
set(FORMS
        src/mainWindow/ui_mainwindow.ui
        src/connection/DCC-EX/ui_dccEx.ui
        src/connection/Intelibox_I/ui_intelibox_I.ui
)
execute_process(
        COMMAND uic -o src/mainWindow/ui_mainwindow.h src/mainWindow/ui_mainwindow.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for mainWindow failed with error: ${output}")
else()
    message(STATUS "uic command for mainWindow succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o src/connection/DCC-EX/ui_dccEx.h src/connection/DCC-EX/ui_dccEx.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for DCC-EX failed with error: ${output}")
else()
    message(STATUS "uic command for DCC-EX succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o src/connection/Intelibox_I/ui_intelibox_I.h src/connection/Intelibox_I/ui_intelibox_I.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for Intelibox_I failed with error: ${output}")
else()
    message(STATUS "uic command for Intelibox_I succeeded: ${output}")
endif()


qt6_wrap_ui(FORMS_HEADERS ${FORMS})


qt6_add_executable(CCSMTR MANUAL_FINALIZATION ${SOURCES} ${FORMS_HEADERS})

target_link_libraries(CCSMTR PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SerialPort)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/app)

qt_finalize_executable(CCSMTR)


