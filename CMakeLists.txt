cmake_minimum_required(VERSION 3.5)

project(CCSMTR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets SerialPort Xml REQUIRED)

set(SOURCES
        src/main.cpp
        src/mainWindow/mainWindow.cpp
        src/mainWindow/mainWindow.h
        src/station_controll/stationControll.cpp
        src/station_controll/stationControll.h
        src/tabFolder/connectionTab/DCC-EX/dccEx.cpp
        src/tabFolder/connectionTab/DCC-EX/dccEx.h
        src/tabFolder/connectionTab/Intelibox_I/intelibox_I.cpp
        src/tabFolder/connectionTab/Intelibox_I/intelibox_I.h
        src/tabFolder/ToolsTab/Throttle/ThrottleWindow.cpp
        src/tabFolder/ToolsTab/Throttle/ThrottleWindow.h
        src/tabFolder/connectionTab/Power/PowerWindow.cpp
        src/tabFolder/connectionTab/Power/PowerWindow.h
        src/station_controll/Rails/Rails.cpp
        src/station_controll/Rails/Rails.h
        src/station_controll/Actions/RailsAction.h
        src/station_controll/Actions/RailsAction.cpp
        src/station_controll/RightClick/RightClick.cpp
        src/station_controll/RightClick/RightClick.h


)
set(FORMS
        src/mainWindow/ui_mainwindow.ui
        src/tabFolder/connectionTab/DCC-EX/ui_dccEx.ui
        src/tabFolder/connectionTab/Intelibox_I/ui_intelibox_I.ui
        src/tabFolder/ToolsTab/Throttle/ui_ThrottleWindow.ui
        src/tabFolder/connectionTab/Power/ui_PowerWindow.ui
        src/station_controll/ui_stationControll.ui
        src/station_controll/RightClick/ui_RightClick.ui

)
execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/mainWindow/ui_mainwindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/mainWindow/ui_mainwindow.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for mainWindow failed with error: ${output}")
else()
    message(STATUS "uic command for mainWindow succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/DCC-EX/ui_dccEx.h ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/DCC-EX/ui_dccEx.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for DCC-EX failed with error: ${output}")
else()
    message(STATUS "uic command for DCC-EX succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/Intelibox_I/ui_intelibox_I.h ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/Intelibox_I/ui_intelibox_I.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for Intelibox_I failed with error: ${output}")
else()
    message(STATUS "uic command for Intelibox_I succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/ToolsTab/Throttle/ui_ThrottleWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/ToolsTab/Throttle/ui_ThrottleWindow.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for Throttle failed with error: ${output}")
else()
    message(STATUS "uic command for Throttle succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/Power/ui_PowerWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/tabFolder/connectionTab/Power/ui_PowerWindow.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for Power failed with error: ${output}")
else()
    message(STATUS "uic command for Power succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/station_controll/ui_stationControll.h ${CMAKE_CURRENT_SOURCE_DIR}/src/station_controll/ui_stationControll.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for station_controll failed with error: ${output}")
else()
    message(STATUS "uic command for station_controll succeeded: ${output}")
endif()

execute_process(
        COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/station_controll/RightClick/ui_RightClick.h ${CMAKE_CURRENT_SOURCE_DIR}/src/station_controll/RightClick/ui_RightClick.ui
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
)
if(result)
    message(WARNING "uic command for RightClick failed with error: ${output}")
else()
    message(STATUS "uic command for RightClick succeeded: ${output}")
endif()


qt6_wrap_ui(FORMS_HEADERS ${FORMS})


qt6_add_executable(CCSMTR MANUAL_FINALIZATION ${SOURCES} ${FORMS_HEADERS})

target_link_libraries(CCSMTR PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SerialPort Qt6::Xml)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/app)

qt_finalize_executable(CCSMTR)


