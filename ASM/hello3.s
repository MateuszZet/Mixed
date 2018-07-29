SYSCALL32 = 0x80
EXIT = 1
WRITE = 4
STDOUT = 1
READ = 3
BUF_SIZE = 254
STDIN = 0
#ZAMIANA = 32 #roznica miedzy znakiem malej a duzej litery w ASCII to 32

.data
BUFOR: .space BUF_SIZE
TEXT_SIZE: .long 0
.text
.globl _start
 
_start:
 
movl $BUF_SIZE, %edx 
movl $BUFOR, %ecx 
movl $STDIN, %ebx 
movl $READ, %eax 
int $SYSCALL32

decl %eax #'/n' na koncu
movl %eax, TEXT_SIZE # w %eax zwraca liczbe wczytanych znakow

call zamienianie #wywolanie funkcji

decl %edi
movb $'\n', BUFOR(,%edi,1)
incl TEXT_SIZE
movl TEXT_SIZE, %edx #faktyczna liczba znakow w bajtach do %edx
movl $BUFOR, %ecx 
movl $STDOUT, %ebx 
movl $WRITE, %eax
int $SYSCALL32
 
movl $EXIT, %eax 
int $SYSCALL32

.type zamienianie @function
zamienianie:
	movl $0, %edi #przesuwamy (kopiujemy 0) do rejestru indeksowego
	loop:
		movb  BUFOR(,%edi,1), %al #pierwszy znak do %al
		#cmpb $'Z', %al #sprawdzamy czy duza
		#jbe dalej
		cmp $0x20, %al #sprawdzamy czy spacja
		je dalej		#je¿eli mamy spacje to skaczemy do dalej,
						#spacja nie zostanie przetworzona
		and  $0b11011111, %al #11011111 B 
						# bit na którym jest 0 odpowiada wielkoœci litery
						# 0 = Du¿a, 1 = ma³a
		
		dalej:
		movb	%al, BUFOR(,%edi,1)
		incl	%edi #zwiekszamy indeks
		cmpl	TEXT_SIZE, %edi #porownujemy wartosc w edi z TEXT_SIZE
		jbe	loop #skok jezeli mniejsze lub rowne (bez znaku)
	ret

