/* Entry Point */
/* 程序入口——程序将从Reset Handler开始执行，而该函数定义在stm32fxxx.s启动文件中。
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
/* end of stack 堆栈末尾 = RAM起始地址 + RAM空间大小 */
_estack = ORIGIN(RAM) + LENGTH(RAM);	/* end of "RAM" Ram type memory */

/* 程序所必须的堆、栈空间大小定义 */
_Min_Heap_Size = 0x200 ;	/* required amount of heap  */
_Min_Stack_Size = 0x400 ;	/* required amount of stack */

/* Memories definition */
/* 单片机内部存储空间 RAM FLASH起始位置和大小的声明 */
MEMORY
{
  RAM	(xrw)	: ORIGIN = 0x20000000,	LENGTH = 20K
  FLASH	(rx)	: ORIGIN = 0x8000000,	LENGTH = 64K
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  /* 中断向量表定义于 .s启动文件中，应位于Flash的最前端，也就是从0x8000000的位置开始 */
  .isr_vector :
  {
  /* 字对齐 */
    . = ALIGN(4);
    /* 将中断向量的内容链接到该地址 */
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  /* .text对应程序的可执行代码 */
  .text :
  {
  /* 字对齐 */
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)
    
	/* KEEP() 的作用是当启用连接器的--gc-sections垃圾回收选项时，这部分不能被回收  
	参考链接 https://blog.csdn.net/wangbinyantai/article/details/79001303 */
    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    /* _etext是链接器的预定义变量，代表程序正文段结束的第一个地址 */
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  /* .rodata代表程序中使用的常量表格数据等 */
  .rodata :
  {
  /* 前后字对齐 */
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH
  
/* ？如果有朋友清楚下面这段定义的含义请评论告诉我，多谢！*/
  .ARM.extab   : { 
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH
  
/* .preinit_array和.init_array部分包含指向将在初始化时调用的函数的指针数组。
参考链接：https://stackoverflow.com/questions/40532180/understanding-the-linkerscript-for-an-arm-cortex-m-microcontroller */

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH
  
  .fini_array :
  {
    . = ALIGN(4);
    
    /* PROVIDE_HIDDEN 表示 ：Similar to PROVIDE. For ELF targeted ports, 
    the symbol will be hidden and won’t be exported. 
    表示符号在目标文件中被定义但不会被导出 */
    
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  /* 以变量_sidata存储.data块的起始地址，.data对应初始化了的全局变量 */
  
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  /* .data对应初始化了的全局变量，编译后将位于可执行文件中，由启动代码负责加载到数据区中（在单片机中这部分数据会存于flash中，需要由启动代码把这部分内容拷贝到ram中）*/
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    
    /* edata的地址是初始化数据区后面的第1个地址 */
    _edata = .;        /* define a global symbol at data end */
    
  } >RAM AT> FLASH

  /* Uninitialized data section into "RAM" Ram type memory */
  . = ALIGN(4);
  
  /* .bss段是没有初始值的全局变量，由启动代码把这部分内容全初始化为0 */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    /* COMMON数据段仅在.o文件中存在，当代码中的全局变量没有赋初值时存储在该数据段中 */
    https://stackoverflow.com/questions/16835716/bss-vs-common-what-goes-where */
    
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    
    /* 同PROVIDE_HIDDEN的作用类似，定义内部变量而不导出 */
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
