import re


def parse_memory_section(line):
    # 从节头行解析出节名、地址和大小
    parts = line.split()
    name = parts[1]
    addr = int(parts[3], 16)
    size = int(parts[5], 16)
    return name, addr, size


def is_in_range(addr, start, end):
    # 检查地址是否在给定的范围内
    return start <= addr < end


def calculate_size(file_name):
    # 定义FLASH和RAM的起始地址和长度
    flash_start = 0x8000000
    flash_end = flash_start + 32 * 1024
    ram_start = 0x20000000
    ram_end = ram_start + 10 * 1024

    # 初始化FLASH和RAM的大小
    flash_size = 0
    ram_size = 0

    # 打开并读取文件
    with open(file_name, "r") as file:
        lines = file.readlines()

    # 遍历每一行
    for line in lines:
        # 使用正则表达式匹配节头行
        if re.match(r"\[\s*\d+\]", line):
            # 解析节头行
            name, addr, size = parse_memory_section(line)
            # 检查节是否在FLASH或RAM中
            if is_in_range(addr, flash_start, flash_end):
                flash_size += size
            elif is_in_range(addr, ram_start, ram_end):
                ram_size += size

    return flash_size, ram_size


# 使用文件名调用函数
flash_size, ram_size = calculate_size("build/size.txt")
print(f"FLASH size: {flash_size} bytes")
print(f"RAM size: {ram_size} bytes")
