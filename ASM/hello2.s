SYSCALL32 = 0x80
EXIT = 1
WRITE = 4
STDOUT = 1
READ = 3
BUFF = 254
STDIN = 0

.data
BUFOR: .space BUFF
.text
.globl _start
 
_start:
 
movl $BUFF, %edx 
movl $BUFOR, %ecx 
movl $STDIN, %ebx 
movl $READ, %eax 

int $SYSCALL32
movl $BUFF, %edx 
movl $BUFOR, %ecx 
movl $STDOUT, %ebx 
movl $WRITE, %eax 
int $SYSCALL32
 
movl $EXIT, %eax 
int $SYSCALL32

