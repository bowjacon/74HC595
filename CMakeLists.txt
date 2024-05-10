# 设置构建项目适用通用的操作系统
set(CMAKE_SYSTEM_NAME Generic)

# 设置构建项目的版本号
set(CMAKE_SYSTEM_VERSION 1)

# 设置构建项目所支持的最低CMake版本
cmake_minimum_required(VERSION 3.13)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}") # CMake 3.9+
endif()
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)

# 设置CMake的二进制文件复制工具和反汇编工具
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)

# 设置CMake的大小统计工具
set(SIZE arm-none-eabi-size)

# 设置编译的目标类型为静态库
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
get_filename_component(TOP_LEVEL_DIR ${CMAKE_SOURCE_DIR} NAME)
set(CURRENT_TOP_LEVEL_DIR ${TOP_LEVEL_DIR} CACHE INTERNAL "")

# 设置项目名称和支持的语言
project(${CURRENT_TOP_LEVEL_DIR} C CXX ASM)

# 设置CMake使用的C++语言标准和C语言标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# 指定了目标处理器为 ARM Cortex-M3
# 启用了 Thumb 指令集和 Thumb 与 ARM 指令集之间的互操作
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)  # NOLINT

# -ffunction-sections 和 -fdata-sections 将函数和数据分别放入它们自己的节（section）
# -fno-common 防止生成公共符号netstat -tlnp | grep
# -fmessage-length=0 禁用错误信息的行数限制
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# 设置优化的级别
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
    # 设置 striped 可以去除符号表
    # set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s") 
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()
# target_link_libraries(Example  m)
add_compile_definitions(ARM_MATH_CM3;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
# 设置头文件搜索路径
# include_directories(Core/Inc Core/I2C Drivers/Inc Core/Mpu6050 Core/eMPL Core/DSP/Inc Core/CMSIS/Include)
macro(FIND_INCLUDE_DIR result curdir)									#定义函数,2个参数:存放结果result；指定路径curdir；
	file(GLOB_RECURSE children "${curdir}/*.hpp" "${curdir}/*.h" )		#遍历获取{curdir}中*.hpp和*.h文件列表
	set(dirlist "")														#定义dirlist中间变量，并初始化
	foreach(child ${children})											#for循环
		string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})			#字符串替换,用/前的字符替换/*h
		if(IS_DIRECTORY ${LIB_NAME})									#判断是否为路径
			list (FIND dirlist ${LIB_NAME} list_index)					#去重，查找dirlist中是否有${LIB_NAME}指定的值，可以区分字符串相同数子后缀不同的路径：例如/app/test_1和/app/test_2
			if(${list_index} LESS 0)									#若没找到则代表列表中没有该路径
				LIST(APPEND dirlist ${LIB_NAME})						#将合法的路径加入dirlist变量中  
			endif()														#结束判断
		endif()															
	endforeach()														#结束for循环
	set(${result} ${dirlist})											#dirlist结果放入result变量中
endmacro()
FIND_INCLUDE_DIR(ALL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR})					#调用函数，获取所有头文件路径
include_directories(${ALL_INCLUDE_DIRS})								#添加所有头文件路径
include_directories("Core/Source/Include Core/Source/Include/dsp")
# 先添加cortexm3的头文件路径
# include_directories(${CMAKE_SOURCE_DIR}/path_to_cortexm3_include)
#
# 然后添加cmsis_gcc的头文件路径
# include_directories(${CMAKE_SOURCE_DIR}/path_to_cmsis_gcc_include)
# 预定义宏
add_definitions(
    -DDEBUG 
    -DSTM32F10X_MD 
    -DUSE_STDPERIPH_DRIVER  
    # -DARM_MATH_CM3
# -DVECT_TAB_SRAM
)
if(GCC_VERSION VERSION_GREATER 12.2 OR GCC_VERSION VERSION_EQUAL 12.2)
    add_link_options(-Wl,--no-warn-rwx-segments)
endif()
# add_link_options(--no-warn-rwx-segments)

# add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)
# 获取项目的所有源文件
file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*" )
# 获取Core/Source目录下的所有源文件
# file(GLOB_RECURSE  SRC_LIST "Drivers/Src/*.c")
# include_directories(${PROJECT_SOURCE_DIR}/include)
# file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 设置动态库生成路径
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# add_library(stm32f10x  SHARED ${SRC_LIST})
# 设置动态库/静态库生成路径
# 生成静态库

# 设置变量值,即链接脚本路径
# set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103C6TX_FLASH.ld)

# add_compile_definitions(ARM_MATH_CM3;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING;ARMCM3ARMCM3)
# add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
# add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_compile_options(-mfloat-abi=soft)
# -Wl 用来传递选项给链接器的。
# -gc-sections 告诉链接器丢弃未使用的代码和数据段，帮助减小生成的二进制文件的大小。
# --print-memory-usage 让链接器在链接完成后打印内存使用情况，这可以帮助我们了解程序使用了多少 RAM 和 Flash。
# -Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map 让链接器生成一个 map 文件,包含了生成的二进制文件的详细信息
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
# set(CMAKE_C_LINK_FLAGS "${TARGET_FLAGS}")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${CMAKE_SOURCE_DIR}/STM32F103RCTx_FLASH.ld\"")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")
# add_compile_options(-lm)
# 如上编译选项,为链接器设置目标处理器以及指令集
# add_link_options(-specs=nano.specs)使用精简库
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork -specs=nosys.specs -specs=nano.specs) # NOLINT
# set(COMMON_FLAGS "")
# add_link_options(-lc)
# add_compile_options("-fno-math-errno")
# 为链接器设置链接脚本
add_link_options(-T ${LINKER_SCRIPT})
# link_directories(Core/DSP/Lib)
# link_libraries(libarm_cortexM3l_math.a)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

# link_libraries("${CMAKE_CURRENT_SOURCE_DIR}/Core/DSP/Lib/libarm_math.a")
# link_libraries("${CMAKE_CURRENT_SOURCE_DIR}/Lib/libstm32f10x.a")
# link_directories("Lib")
# #添加静态库目录
# LINK_DIRECTORIES(Core/DSP/Lib/)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=rdimon.specs -specs=nosys.specs")
# target_link_libraries(Example m)
# 构建可执行文件,分别为可执行文件名称、所需的源文件、链接脚本
# add_compile_options(-mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mthumb -mcpu=cortex-m4 -mlittle-endian -mthumb-interwork -specs=nano.specs -specs=nosys.specs )
# add_link_options(-mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mthumb -mcpu=cortex-m4 -mlittle-endian -mthumb-interwork -specs=nano.specs -specs=nosys.specs )
file(GLOB LIBRARIES "Lib/*.a")

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

foreach(LIBRARY ${LIBRARIES})
    target_link_libraries(${PROJECT_NAME}.elf ${LIBRARY})
endforeach()
# target_link_libraries(${PROJECT_NAME}.elf libstm32f10x) 
# set(TARGET "algorithm_shared_dll")
# add_library(${TARGET} SHARED ${SRC_LIST})
# add_library(mpu6050 STATIC ${SRC_LIST})
# # 设置二进制文件的输出路径
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

# # 生成二进制文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}"
        COMMENT "Building ${HEX_FILE}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
