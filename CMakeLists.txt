cmake_minimum_required(VERSION 3.5)

project(CCSMTR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml SvgWidgets SerialPort)

set(SOURCES
        src/main.cpp
        src/MainScreen/MainWindow/MainWindow.cpp
        src/MainScreen/MainWindow/MainWindow.h
        src/MainScreen/StationControl/StationControl.cpp
        src/MainScreen/StationControl/StationControl.h
        src/MainScreen/TabFolder/ConnectionTab/DCC-EX/DccEx.cpp
        src/MainScreen/TabFolder/ConnectionTab/DCC-EX/DccEx.h
        src/MainScreen/TabFolder/ToolsTab/Throttle/ThrottleWindow.cpp
        src/MainScreen/TabFolder/ToolsTab/Throttle/ThrottleWindow.h
        src/MainScreen/TabFolder/ConnectionTab/Power/PowerWindow.cpp
        src/MainScreen/TabFolder/ConnectionTab/Power/PowerWindow.h
        src/LogicInstance/StationControlLogic/RightClick/RightClick.cpp
        src/LogicInstance/StationControlLogic/RightClick/RightClick.h
        src/MainScreen/TabFolder/ConnectionTab/DCC-EX/CommandQueue.h
        src/MainScreen/StationControl/SVGHandleEvent/SVGHandleEvent.cpp
        src/MainScreen/StationControl/SVGHandleEvent/SVGHandleEvent.h


)
set(FORMS
        src/MainScreen/MainWindow/ui_MainWindow.ui
        src/MainScreen/TabFolder/ConnectionTab/DCC-EX/ui_DccEx.ui
        src/MainScreen/TabFolder/ToolsTab/Throttle/ui_ThrottleWindow.ui
        src/MainScreen/TabFolder/ConnectionTab/Power/ui_PowerWindow.ui
        src/MainScreen/StationControl/ui_StationControl.ui
        src/LogicInstance/StationControlLogic/RightClick/ui_RightClick.ui

)
if (WIN32)
    execute_process(
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/MainWindow/ui_MainWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/MainWindow/ui_MainWindow.ui
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/LogicInstance/StationControlLogic/RightClick/ui_RightClick.h ${CMAKE_CURRENT_SOURCE_DIR}/src/LogicInstance/StationControlLogic/RightClick/ui_RightClick.ui
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/DCC-EX/ui_DccEx.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/DCC-EX/ui_DccEx.ui
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ToolsTab/Throttle/ui_ThrottleWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ToolsTab/Throttle/ui_ThrottleWindow.ui
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/Power/ui_PowerWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/Power/ui_PowerWindow.ui
            COMMAND uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/StationControl/ui_stationControl.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/StationControl/ui_StationControl.ui
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
    )
else()
    execute_process(
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/MainWindow/ui_MainWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/MainWindow/ui_MainWindow.ui
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/LogicInstance/StationControlLogic/RightClick/ui_RightClick.h ${CMAKE_CURRENT_SOURCE_DIR}/src/LogicInstance/StationControlLogic/RightClick/ui_RightClick.ui
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/DCC-EX/ui_DccEx.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/DCC-EX/ui_DccEx.ui
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ToolsTab/Throttle/ui_ThrottleWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ToolsTab/Throttle/ui_ThrottleWindow.ui
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/Power/ui_PowerWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/TabFolder/ConnectionTab/Power/ui_PowerWindow.ui
            COMMAND /usr/lib/qt6/uic -o ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/StationControl/ui_stationControl.h ${CMAKE_CURRENT_SOURCE_DIR}/src/MainScreen/StationControl/ui_StationControl.ui
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
    )
endif()
if(result)
    message(WARNING "uic command failed with error: ${output}")
else()
    message(STATUS "uic command succeeded: ${output}")
endif()


qt6_wrap_ui(FORMS_HEADERS ${FORMS})


qt6_add_executable(CCSMTR MANUAL_FINALIZATION ${SOURCES} ${FORMS_HEADERS})

target_link_libraries(CCSMTR PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Xml Qt6::SvgWidgets Qt6::SerialPort)
if (WIN32)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/bin)
    target_compile_definitions(CCSMTR PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_link_libraries(CCSMTR PRIVATE ws2_32)

    #if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    #    target_link_options(CCSMTR PRIVATE -Wl,--subsystem,windows)
    #else()
    #    target_link_options(CCSMTR PRIVATE /SUBSYSTEM:WINDOWS)
    #endif()
    set(CMAKE_GENERATOR_PLATFORM x64)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/bin)
endif()

qt_finalize_executable(CCSMTR)


