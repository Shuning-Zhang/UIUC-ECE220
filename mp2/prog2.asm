;Partners: sz31, soohar2 
;In this program,first we need to read the value from the screen to the program to do that we use GETC, and than we check if the character is =, if it is we print out the answer if not we check what character it is. after that we check if the character is an operator or a number. if it is a number than push it into the stack, if it is a operator pop twice and push it. If it neither a operator nor a number than print the error message. And than use the according subroutine to operate the operator. After those are done start reading the next character.
;
.ORIG x3000
	
;your code goes here
;R0 echo the character from the screen
;R1 a temportary register for testing
;R3 first operand
;R4 second operand
;R6 - current numerical output
;R5 final result
GETCHAR
	GETC   			 ;read the value
    OUT

	LD R1, NEGEQUAL		;load the number NEGEQUAL into R1, ready for comparison
	ADD R1,R0,R1		;compare the number in R0 and in R1
	BRz Print_HEX		;jump to Print_Hex subroutine

	LD R1, NEGSPACE		;load the number NEGSPACE into R1, ready for comparison
	ADD R1,R0,R1		;compare R0 and R1
	BRZ GETCHAR			;if R0 is a space, ignore it and read the next char

	JSR EVALUATE		;jumpt to evaluate subroutine
	BR GETCHAR			;after evaluate load the next character








;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	JSR POP				;get the answer
	ADD R5,R5,#0		;check if underflow
	BRp Invalid			;if underflow ends the program

	LD R2,STACK_START		;load the stack begin value in R2
	LD R4,STACK_TOP		;load the stack top
	NOT R4,R4
	ADD R4,R4,#1		;change to the negative value
	ADD R2,R4,R2		;compare the two number
	BRnp Invalid		;if more than one value left it's invalid
	ADD R5,R0,#0		;load the final answer into R5
	ADD R3,R0,#0		;load the answer into R3 ready to print
	ST R5,Finalanswer	;save the value in R5

	LD R0,X				;load the value of x 
	OUT
	
	AND R5,R5,#0		; clear the register value
	ADD R5,R5,#4        ; reset the small loop counter

Small
	AND R2,R2,#0		; clear destination register R2
	AND R1,R1,#0		; clear bit counter R1
	ADD R1,R1,#4		; initialize bit counter to 4

SmallLoop
	ADD R2,R2,R2		; shift R2 to make space for next bit
	ADD R3,R3,#0		; Observe the highest bit of R3
	BRzp Shift			; if highest bit is 0 skip adding 1 to R2
	ADD R2,R2,#1		; add 1 to R2

Shift
	ADD R3,R3,R3		; shift R3 to get the second bit
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
	OUT					; out trap print the value in R0
	ADD R5,R5,#-1		; deccrement the bigloop counter
	BRp Small			; branch back to small loop
	LD R5,Finalanswer	;restore the value in R5
	HALT				; done


; the data needed by the program

Zero	.FILL #48		; the ASCII value of 0
A		.FILL #65		; the ASCII value of A
X		.FILL #120		; the ASCII value of x
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

 
	ST R7,EVASAVER7     ;safe the value in R7
	ST R0,EVASAVER0		;safe the value in R0
	AND R6,R6,#0		;Setup R6

	LD R1,NEGPLUS		;load the negative value of "+"
	ADD R1,R0,R1		;check if the char is "+"
	BRz GoPlus			;jump to get the value of R3&R4	

	LD R1,NEGMINUS      ;load the negative value of "-"
    ADD R1,R0,R1        ;check if the char is "-"
    BRz GoMin         ;jump to get the value of R3&R4	

	LD R1,NEGMULTI      ;load the negative value of "*"
    ADD R1,R0,R1        ;check if the char is "*"
    BRz GoMul         ; jump to get the value of R3&R4

	LD R1,NEGDIV        ;load the negative value of "/"
    ADD R1,R0,R1        ;check if the char is "/"
    BRz GoDiv         ; jump to get the value of R3&R4

	LD R1,NEGEX         ;load the negative value of "^"
    ADD R1,R0,R1    	;check if the char is "^"
    BRz GoExp     	; jump to get the value of R3&R4
	
	LD R1,NEGZERO		;load the negative value of 0
	ADD R0,R0,R1		;compare the two number
	BRn Invalid			;it's not a number
	ADD R0,R0,#-10		;check if it's 0-9
	BRzp Invalid		;not a number
	ADD R0,R0,#10		;change the number back
	JSR PUSH
	LD R7,EVASAVER7		;load the value of R7
	RET 
GoPlus
	JSR GETR3R4		;jump to get R3R4
	JSR PLUS		;go do plus
	BR GETCHAR		;branch back
GoMin
	JSR GETR3R4             ;jump to get R3R4
        JSR MIN                ;go do minus
        BR GETCHAR              ;branch back
GoMul
	JSR GETR3R4             ;jump to get R3R4
        JSR MUL                 ;go do multi
        BR GETCHAR              ;branch back
GoDiv
	JSR GETR3R4             ;jump to get R3R4
        JSR DIV                ;go do divide
        BR GETCHAR              ;branch back
GoExp
	JSR GETR3R4             ;jump to get R3R4
        JSR EXP                ;go do exp
        BR GETCHAR              ;branch back
GETR3R4

	ST R7,GetSaveR7		;safe the value og r7 for later
	JSR POP				;load the second number
	ADD R5,R5,#0		;check if underflow
	BRp Invalid			;positive means underflow go to invalid
	ADD R4,R0,#0		;load the number into R4
	JSR POP				;load the first number
	ADD R5,R5,#0        ;check if underflow
    BRp Invalid         ;positive means underflow go to invalid
    ADD R3,R0,#0        ;load the number into R3
	LD R7,GetSaveR7		;load the pc value back to R7
	RET

Invalid
	LEA R0,INVALIDST	;load the string into R0, ready to print
	PUTS				;Print
	HALT				;program ends



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS
	ST R7,PlusSave		;store the pc number
	AND R0,R0,#0		;clear the value in R0	
	ADD R0,R3,R4		;add the two number together

	ADD R6,R0,#0		;load the current answer into R6
	JSR PUSH			;push the anser back to stack
	
	LD R7,PlusSave		;restore the value in R7
	RET					;jump back to evaluate subroutine
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	ST R7,MinSave		;store the pc number
	AND R0,R0,#0        ;clear the value in R0
	NOT R4,R4
	ADD R4,R4,#1		;change R4 to its negative value
	ADD R0,R4,R3		;minus the two number

	ADD R6,R0,#0        ;load the current answer into R6
    JSR PUSH            ;push the anser back to stack 

	LD R7,MinSave		;restore the number in R7
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	ST R7,MulSave		;store the pc number
	AND R0,R0,#0		;clear the value in R0,ready to store the result
ADDM	
	ADD R0,R3,R0		;start the multi process
	ADD R4,R4,#-1		;decrease the loop
	BRp ADDM			;if R4 is postive continue the add

	ADD R6,R0,#0        ;load the current answer into R6
    JSR PUSH            ;push the anser back to stack 

	LD R7,MulSave		;restore the value in R7
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
	ST R7,DivSave		;store the pc number
	AND R0,R0,#0        ;clear the value in R0
	NOT R4,R4
	ADD R4,R4,#1		;change the value in R4 to negative
SUB
	ADD R0,R0,#1		;add one to R0
	ADD R3,R3,R4		;minus first operand from first operand
	BRzp SUB
	ADD R0,R0,#-1		;minus the extra loop did

	ADD R6,R0,#0        ;load the current answer into R6
    JSR PUSH            ;push the anser back to stack 
	
	LD R7,DivSave		;restore the value in R7
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;temp register R1
EXP
	ST R7,ExpSave		;store the pc number
	AND R0,R0,#0		;clear the vlaue in R0
	AND R1,R1,#0		;clear the value in R1
	ADD R1,R3,#0		;set R1 to R3 ready for the loop 
Multiloop
	ADD R4,R4,#-1		;decrease the loop
	BRnz EXPdone		;if number is negative than the calculation is finished
EXPADD
	ADD R0,R3,R0		;start the process
	ADD R1,R1,#-1		;decrease the counter
	BRp EXPADD		    ;loop back
	BRz Multiloop		;if one cycle done loop back to multiloop
	
EXPdone
	ADD R6,R0,#0       	;load the current answer into R6
    JSR PUSH            ;push the anser back to stack 

	LD R7,ExpSave		;restore the value in R7
	RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
Finalanswer	.BLKW #1	;place to store the final answer
NEGZERO		.FILL #-48	;the value of negative "0" in ascii
NEGEQUAL 	.FILL #-61	;the value of negative "=" in ascii
NEGSPACE	.FILL #-32	;the value of negative " " in ascii 
NEGPLUS		.FILL #-43	;the value of negative "+" in ascii
NEGMINUS	.FILL #-45	;the value of negative "-" in ascii
NEGMULTI	.FILL #-42	;the value of negative "*" in ascii
NEGDIV		.FILL #-47	;the value of negative "/" in ascii
NEGEX		.FILL #-94	;the value of negative "^" in ascii
GetSaveR7	.BLKW #1	;place where R7 will be safed
EVASAVER0	.BLKW #1	;safe R0
EVASAVER7	.BLKW #1	;safe R7
PlusSave    .BLKW #1    ;safe R7
MinSave     .BLKW #1    ;safe R7
MulSave		.BLKW #1	;safe R7
DivSave		.BLKW #1	;safe R7
;SaveR4		.BLKW #1	;safe R4
ExpSave		.BLKW #1	;safe R7
INVALIDST	.STRINGZ "Invalid Expression"


PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
