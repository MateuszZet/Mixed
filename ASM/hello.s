SYSCALL32 = 0x80
EXIT = 1
WRITE = 4
STDOUT = 1

.data		#sekcja danych
komunikat: .ascii "Hello!\n"
rozmiar = . - komunikat

.text
.globl _start
 
_start:
					 #przekazanie parametrów do rejestrów
movl $rozmiar, %edx 
movl $komunikat, %ecx 
movl $STDOUT, %ebx 
movl $WRITE, %eax 
int $SYSCALL32
 
movl $EXIT, %eax 
int $SYSCALL32

