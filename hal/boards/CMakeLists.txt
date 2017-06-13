if(BOARD)
    message(STATUS "Use HAL board: ${BOARD}")

    set(NAME hal_board)
    add_library(${NAME} INTERFACE)
    target_sources(${NAME} INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/${BOARD}/hal/board.h
    )

    target_include_directories(${NAME} INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/${BOARD}
    )
else()
    message(STATUS "Not using HAL bsp, make sure to provide one!")
    set(HAL_MCU "" CACHE STRING "")
    set(AVRDUDE_TOOL "" CACHE STRING "")
    set(AVRDUDE_OPTIONS "" CACHE STRING "")
endif(BOARD)