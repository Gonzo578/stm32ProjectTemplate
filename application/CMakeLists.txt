# MIT License

# Copyright (c) 2023 Ralf Hochhausen

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
###########################################################################################

ENABLE_LANGUAGE(ASM)

include(utilities)

# Add path to 3rd party SW libraries
add_subdirectory(3rdparty)

# Add path to board support package
add_subdirectory(bsp)

# Add path to component libraries
add_subdirectory(components)

# Add path to MCU platform
add_subdirectory(platform)

# Main project target
add_executable(Hello_Stm32 "")

target_sources( Hello_Stm32
	PRIVATE
		main.cpp
		syscalls.c
     	STM32G4xx/stm32g4xx_it.c
     	STM32G4xx/system_stm32g4xx.c
     	STM32G4xx/startup_stm32g474xx.s
)

target_compile_features(Hello_Stm32 PUBLIC cxx_std_17)

# Target link libraries
target_link_libraries( Hello_Stm32
	PRIVATE
		cmsis_core
		cmsis_device
		mcal_dio
		bsp
)

GET_TARGET_PROPERTY(TARGET_LD_FLAGS ${CMAKE_PROJECT_NAME} LINK_FLAGS)
SET(TARGET_LD_FLAGS "\"-T${CMAKE_CURRENT_SOURCE_DIR}/STM32G4xx/STM32G474RETX_FLASH.ld\"")
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS ${TARGET_LD_FLAGS})

ADD_BIN_TARGETS(${CMAKE_PROJECT_NAME})