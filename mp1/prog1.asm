;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
;partners: sz31, soohar2
;in this part of the program i am going to print out the historgram in the hex format by first converting the number of each letter appeared in the string wich is already stored in the program, into digits using four loops to load the four digit into a new register (by using shift left, and branch) then convert those into corresbonding ASCII values, and lastly pring the value on the screen loop this whole  process 27 times to pring out @ plus A-Z. Above that is how to print out the historgram value but before that as the mp requires, i worte the progrom to print out the corresponding letter of the historgram, and follows a space to meet the format, by using out command.
;R0  is used as a temempory counter, contain the digital value of the count
;R1  is used as a counter when changing into digital number 
;R2  is used to store the group of four digits what will be change into hex value
;R3  is used to load the histogram
;R4  is a loop counter will end at ( will be 27)
;R5  is used to count 4 time the small loop runs one line of the histogram
;R6  is used as a temportary register that loads the memory of the historgram
;R7	 is used as a temportary register

	LD R3,HIST_ADDR     ; point R3 to the start of the histogram
	AND R4,R4,#0		; clear the register value
	AND R5,R5,#0		; clear the register value
	ADD R4,R4,#-10
	ADD R4,R4,#-10
	ADD R4,R4,#-7		; minus 27 to meet the later requirment

Bigloop
	ADD R4,R4,#10
	ADD R4,R4,#10
	ADD R4,R4,#7		; add 27 to change it's original value before branch
	ADD R5,R5,#4        ; reset the small loop counter
	LDR R6,R3,#0		; load the histogram into R6
	LD	R7,Aminus1
	ADD R0,R4,R7			; load the value of R4 into R0
	OUT
	LD R0,S				; load the space ASCII value into R0
	OUT

Small
	AND R2,R2,#0		; clear destination register R2
	AND R1,R1,#0		; clear bit counter R1
	ADD R1,R1,#4		; initialize bit counter to 4

SmallLoop
	ADD R2,R2,R2		; shift R2 to make space for next bit
	ADD R6,R6,#0		; Observe the highest bit of R6
	BRzp Shift		; if highest bit is 0 skip adding 1 to R2
	ADD R2,R2,#1		; add 1 to R2

Shift
	ADD R6,R6,R6		; shift R6 to get the second bit
	ADD R1,R1,#-1		; decrement bit counter for the small loop
	BRp Smallloop		; if there're still more bits, go back to smallloop

Print
	AND R0,R0,#0		; clear the register value
	ADD R0,R2,#-9		; compare digit with 9
	BRnz Printnum		; if digit is 0-9 print number
	LD R0,A				; otherwise load ASCLL of A
	ADD R0,R0,R2		; add the value of R2 into R0
	ADD R0,R0,#-10		; R0<-R2 + A - 10
	BRnzp Printdone		; use out trap

Printnum
	LD R0,Zero			; Load AscII of 0
	ADD R0,R0,R2		; R0<-R2 + 0

Printdone
	OUT					; out trap print ht evalue in R0
	ADD R5,R5,#-1		; deccrement the bigloop counter
	BRp Small			; branch back to small loop

Newline
	LD R0,Changeline	; change line for new character count
	OUT
	ADD R3,R3,#1		; increment the histogram pointer
	ADD R4,R4,#1		; increment the counter
	ADD R4,R4,#-10
	ADD R4,R4,#-10
	ADD R4,R4,#-7		;minus 27 to check if the loop has finished
	BRz Done			; the progrom halts
	BRn Bigloop			; if R4<0 or R4 =0 countine to print the next line of histogram

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
Zero		.FILL #48	; the ASCII value of 0
A			.FILL #65	; the ASCII value of A
Aminus1		.FILL #64	; the ASCII value of @
S			.Fill #32	; the ASCII value of space
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
Changeline	.FILL x000A	; change lien direction
; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
