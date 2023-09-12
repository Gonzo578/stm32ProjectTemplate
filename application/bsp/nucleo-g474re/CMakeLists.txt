# Component is compiled into a library
add_library(bsp "")

target_sources(bsp
	PRIVATE
		src/BSP_setup.c
)

target_compile_definitions(bsp
	PRIVATE
		STM32				# MCU type
		STM32G4				
		STM32G474RETx
		STM32G474xx
)

target_link_libraries(bsp
    PRIVATE
		cmsis_core
        cmsis_device
		mcal_dio
)

# Component include pathes
target_include_directories(bsp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/inc
)