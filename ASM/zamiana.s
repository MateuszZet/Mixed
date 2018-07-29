SYSCALL32 = 0x80
WRITE = 4
STDOUT = 1
EXIT = 1
READ = 3
STDIN = 0

.data
BUFW: .space 128
BUFW_SIZE= .- BUFW

BUF: .ascii "          \n"
BUF_LEN=  .-BUF

.equ PODSTAWA, 10
.equ NUMB_LEN, 10
.text
.globl _start

_start:

call wpisz
addl $4, %esp #czyści parametr który był włożony na stos

call wypisz
addl $4, %esp #czyści parametr który był włożony na stos

movl $EXIT, %eax 
int $SYSCALL32

.type wpisz, @function
wpisz:
	pushl %ebp 
	movl %esp, %ebp #Jest to dlatego, że nie chcemy zmieniać wskaźnika stosu, więc używamy %ebp.

	movl $BUFW_SIZE, %edx 
	movl $BUFW, %ecx 
	movl $STDIN, %ebx 
	movl $READ, %eax 
	int $SYSCALL32

	movl $0, %edi
	movl $0, %ebx
	
	my_loop:
	xor %eax, %eax
	movb BUFW(,%edi,1), %al
	cmp $0xA, %eax
	je exit_loop

	sub $'0', %al
	push %eax
	movl %ebx, %eax
	movl $10, %ecx
	mul %ecx
	pop %ebx
	add %eax, %ebx
	incl %edi
	jmp my_loop

	exit_loop:
	mov %ebx, %eax #przenosze zawartość do eax bo następna funkja będzie mielić na eax
	movl %ebp, %esp #standardowe wyjście z funkcji - musimy przestawić %ebp i %esp
	popl %ebp #tam gdzie były przed zapoczątkowaniem funkcji
	ret

.type wypisz, @function
wypisz:

	pushl %ebp 
	movl %esp, %ebp #Jest to dlatego, że nie chcemy zmieniać wskaźnika stosu, więc używamy %ebp.
	movl $PODSTAWA, %ebx
	movl $NUMB_LEN-1, %edi

	loop:
	movl $0, %edx
	div %ebx
	orb $'0', %dl
	movb %dl, BUF(,%edi,1)
	decl %edi
	andl %eax, %eax #jak jest 0 to nie skaczemy
	jnz loop
	
	movl $BUF_LEN, %edx 
	movl $BUF, %ecx 
	movl $STDOUT, %ebx 
	movl $WRITE, %eax 
	int $SYSCALL32

	movl %ebp, %esp #standardowe wyjście z funkcji - musimy przestawić %ebp i %esp
	popl %ebp #tam gdzie były przed zapoczątkowaniem funkcji

	ret
