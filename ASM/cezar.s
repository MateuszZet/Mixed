SYSCALL32 = 0x80
EXIT = 1
WRITE = 4
STDOUT = 1
READ = 3
BUF_SIZE = 254
BUF_SIZE2 = 1
STDIN = 0
WYROWNANIE = 'z' - 'a' + 1

.data
BUFOR: .space BUF_SIZE
BUFOR2: .space BUF_SIZE2
TEXT_SIZE: .long 0
KOMUNIKAT: .ascii "Wpisz liczbe (0-9):"
rozmiar = .- KOMUNIKAT
.text
.globl _start
 
_start:
#podanie ciagu znakow duze -szyfruj male -deszyfruj 
movl $BUF_SIZE, %edx 
movl $BUFOR, %ecx 
movl $STDIN, %ebx 
movl $READ, %eax 
int $SYSCALL32

decl %eax #zmniejszam aby nie było znaku entera na koncu
movl %eax, TEXT_SIZE # w %eax zwraca liczbe wczytanych znakow

#komunikat o podaniu przesuniecia
movl $WRITE, %eax
movl $STDOUT, %ebx
movl $KOMUNIKAT, %ecx
movl $rozmiar, %edx
int $SYSCALL32

#podanie przesuniecia
movl $READ, %eax
movl $STDIN, %ebx
movl $BUFOR2, %ecx
movl $BUF_SIZE2, %edx
int $SYSCALL32

call cezar  #wywolanie funkcji

#wypisanie na ekran
decl %edi
movb $'\n', BUFOR(,%edi,1) #dodanie znaku nowej linni
incl TEXT_SIZE
movl TEXT_SIZE, %edx #faktyczna liczba znakow w bajtach do %edx
movl $BUFOR, %ecx 
movl $STDOUT, %ebx 
movl $WRITE, %eax
int $SYSCALL32
 
movl $EXIT, %eax 
int $SYSCALL32

.type cezar @function
cezar:
	movl $0, %edi #przesuwamy (kopiujemy 0) do rejestru indeksowego
	movb BUFOR2(,%edi,1),  %bl #pierwszy znak z bufora2 do %bl
	subb $'0', %bl #odejmuje wartosc 0 w ascii
			# aby miec wartosc podanej liczby
	loop:
		movb  BUFOR(,%edi,1), %al #pierwszy znak do %al
		cmpb $'Z', %al #sprawdzamy czy duza
		jbe mamy_duza
		
		subb %bl, %al #odejmujemy podana wartosc przesuniecia
		cmpb $'a', %al #porownujemu
		jae dalej #skok jezeli wieksze badz rowne
		addb $WYROWNANIE, %al #zwiekszamy o 26 
		jmp dalej
		
		mamy_duza:
		addb %bl, %al #dodajemy podana wartosc przesuniecia
		cmpb $'Z', %al
		jbe dalej #skok jezeli mniejsze badz rowne
		subb  $WYROWNANIE, %al #zmniejszamy o 26 (liczbe liter alfabetu)
			
		dalej:
		xor	$0x20, %al #zamieniam duze na male i male na duze
		movb	%al, BUFOR(,%edi,1)
		incl	%edi #zwiekszamy indeks
		cmpl	TEXT_SIZE, %edi #porownujemy wartosc w edi z TEXT_SIZE
		jbe	loop #skok jezeli mniejsze lub rowne (bez znaku)
		
	ret
