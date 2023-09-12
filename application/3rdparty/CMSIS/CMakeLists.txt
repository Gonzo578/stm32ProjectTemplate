project(cmsis)

# Define cmsis as header only library target
add_library(cmsis_core INTERFACE)

# Component include pathes
target_include_directories(cmsis_core
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
)

add_library(cmsis_device INTERFACE)

target_include_directories(cmsis_device
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Device/STM32G4xx/Include
)