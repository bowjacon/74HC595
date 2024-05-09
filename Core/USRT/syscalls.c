#if !defined(__CROSSWORKS_ARM) && defined(__GNUC__)
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

int writeBuffer(const char *ptr, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    // 等待USART1数据寄存器为空
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    // 将数据发送到USART1数据寄存器
    USART_SendData(USART1, (uint16_t)ptr[i]);
  }
  return len;
}

int readBuffer(char *ptr, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    // 等待USART1数据寄存器不为空
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    // 从USART1数据寄存器读取数据
    ptr[i] = (char)USART_ReceiveData(USART1);
  }
  return len;
}
#include <sys/stat.h>
#include <stddef.h>
 
 
int _close(int file);
void _exit(int status);
int _fstat(int file, struct stat *st);
int _getpid(void);
int _isatty(int file);
int _kill(int pid, int sig);
int _lseek(int file, int ptr, int dir);
int _read(int file, char *ptr, int len);
int _write(int file, const char *ptr, int len);
 
/**************************************************************************//**
 * Close a file.
 *
 * @param[in] file  File you want to close.
 *
 * @return  Returns 0 when the file is closed.
 *****************************************************************************/
int _close(int file)
{
  (void) file;
  return 0;
}
 
/**************************************************************************//**
 * Exit the program.
 *
 * @param[in] status The value to return to the parent process as the
 *            exit status (not used).
 *****************************************************************************/
void _exit(int status)
{
  (void) status;
  while (1) {
  }                 // Hang here forever...
}
 
/**************************************************************************//**
 * Status of an open file.
 *
 * @param[in] file  Check status for this file.
 *
 * @param[in] st    Status information.
 *
 * @return  Returns 0 when st_mode is set to character special.
 *****************************************************************************/
int _fstat(int file, struct stat *st)
{
  (void) file;
  st->st_mode = S_IFCHR;
  return 0;
}
 
/**************************************************************************//**
 * Get process ID.
 *
 * @return  Return 1 when not implemented.
 *****************************************************************************/
int _getpid(void)
{
  return 1;
}
 
/**************************************************************************//**
 * Query whether output stream is a terminal.
 *
 * @param[in] file  Descriptor for the file.
 *
 * @return  Returns 1 when query is done.
 *****************************************************************************/
int _isatty(int file)
{
  (void) file;
  return 1;
}
 
/**************************************************************************//**
 * Send signal to process.
 *
 * @param[in] pid Process id (not used).
 *
 * @param[in] sig Signal to send (not used).
 *****************************************************************************/
int _kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  return -1;
}
 
/**************************************************************************//**
 * Set position in a file.
 *
 * @param[in] file  Descriptor for the file.
 *
 * @param[in] ptr   Poiter to the argument offset.
 *
 * @param[in] dir   Directory whence.
 *
 * @return  Returns 0 when position is set.
 *****************************************************************************/
int _lseek(int file, int ptr, int dir)
{
  (void) file;
  (void) ptr;
  (void) dir;
  return 0;
}
 
/**************************************************************************//**
 * Read from a file.
 *
 * @param[in] file  Descriptor for the file you want to read from.
 *
 * @param[in] ptr   Pointer to the chacaters that are beeing read.
 *
 * @param[in] len   Number of characters to be read.
 *
 * @return  Number of characters that have been read.
 *****************************************************************************/
int _read(int file, char *ptr, int len)
{
  (void)file;
 
  return readBuffer(ptr, len);
}
 
/**************************************************************************//**
 * Write to a file.
 *
 * @param[in] file  Descriptor for the file you want to write to.
 *
 * @param[in] ptr   Pointer to the text you want to write
 *
 * @param[in] len   Number of characters to be written.
 *
 * @return  Number of characters that have been written.
 *****************************************************************************/
int _write(int file, const char *ptr, int len)
{
  (void)file;
 
  return writeBuffer(ptr, len);
}
 
#endif /* !defined( __CROSSWORKS_ARM ) && defined( __GNUC__ ) */