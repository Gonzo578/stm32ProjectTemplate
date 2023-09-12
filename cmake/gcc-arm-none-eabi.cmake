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


SET(TOOLCHAIN_DIR "/usr/bin/gcc-arm-none-eabi-8-2019-q3-update")
SET(TOOLCHAIN_PREFIX "arm-none-eabi")
SET(TOOLCHAIN_BIN_DIR "${TOOLCHAIN_DIR}/bin")
SET(TOOLCHAIN_INC_DIR "${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}/include")
SET(TOOLCHAIN_LIB_DIR "${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}/lib")

SET(CMAKE_C_COMPILER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-gcc")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-g++")
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-gcc")

SET(CMAKE_OBJCOPY "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-objcopy" CACHE INTERNAL "objcopy tool")
SET(CMAKE_OBJDUMP "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-objdump" CACHE INTERNAL "objdump tool")
SET(CMAKE_SIZE "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-size" CACHE INTERNAL "size tool")
SET(CMAKE_DEBUGGER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-gdb" CACHE INTERNAL "debugger")
SET(CMAKE_CPPFILT "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_PREFIX}-c++filt" CACHE INTERNAL "C++filt")

SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

SET(CMAKE_C_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS} -Wall -fdata-sections -ffunction-sections -fno-builtin" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS} -Wall -fdata-sections -ffunction-sections -fno-builtin -fno-rtti -fno-exceptions" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS} -Wl,--gc-sections" CACHE INTERNAL "executable linker flags")
SET(CMAKE_MODULE_LINKER_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS}" CACHE INTERNAL "module linker flags")
SET(CMAKE_SHARED_LINKER_FLAGS_INIT "${MCPU_FLAGS} ${VFP_FLAGS} ${SPEC_FLAGS}" CACHE INTERNAL "shared linker flags")

SET(CMAKE_C_FLAGS_DEBUG_INIT "-Og -g" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG_INIT "-Og -g" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG_INIT "-g" CACHE INTERNAL "asm compiler flags debug")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT "" CACHE INTERNAL "linker flags debug")

SET(CMAKE_C_FLAGS_RELEASE_INIT "-O3" CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3" CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE_INIT "" CACHE INTERNAL "asm compiler flags release")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT "" CACHE INTERNAL "linker flags release")

SET(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
