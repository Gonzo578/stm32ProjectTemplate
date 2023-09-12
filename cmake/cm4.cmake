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
###################################################################################################

###################################################################################################
# This is the master toolchain file for cortex-m4 cross compilation
###################################################################################################

# Define basic system
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(MCPU_FLAGS "-mthumb -mcpu=cortex-m4")				# Basic core related flags
set(VFP_FLAGS "-mfpu=fpv4-sp-d16 -mfloat-abi=hard")		# Floating point configuration
set(SPEC_FLAGS "")										# e.g. "--specs=nosys.specs" or "--specs=newlib.nano"

include(${CMAKE_CURRENT_LIST_DIR}/gcc-arm-none-eabi.cmake)