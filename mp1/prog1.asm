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
; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;At this point of the program, we will have 27 histogram data in the memory
;which are just numbers. My approach is to create a loop (n=27) for
;printing each histogram data. Then, at each step of the loop, I will start printing with
;corresponding character of the histogram which is just ASCII addition
;to character '@'. After that I need to print a space. Later, I will
;start printing the histogram data. I need to print them on the screen as
;4 characters to represent hexadecimal numbers. I will create a loop (n=4)
;for each character. My algorithm is to slide the bits to the left by
;multiplying 2 or adding the number itself. Afterwards, I will check if
;the number negative. If so algorithm will add harcoded value (8, 4, 2 or 1)
;to the output character based on binary significance at the process. If
;number is positive or zero, it will skip the specific binary significance.
;By sliding the number 4 times, I will be able to obtain hexadecimal value.
;Later, I will substract 9 from the output character. If result is zero or negative,
;I will use original output to add to the ASCII value of character zero '0'.
;If not, I will add the result of subtraction to ASCII value of character '@'
;and then, I will print the resulting character. I will loop this four times
;to get complete hexadecimal representation. I will finish the printing with
;printing new line and looping back to beginning for next histogram char an value.

;For my algorithm, I added ASCII values of new line, space and zero at the end.
;Registers are classified as follows:
;	R0 char to be printed
;	R1 ASCII value of char '@'
;	R2 holds a pointer to loop number
;	R3 ASCII value of space
;	R4 counts printed hexadecimal character up to 4
;	R5 holds pointer to the histogram address and then value itself
;	R6 temporary register

	AND R2,R2,#0	; CLEARS THE REGISTER AND LOOP STARTS WITH N=0
	AND R1,R1,#0	; CLEARS THE REGISTER
	LD R1,ASC_AT	; SET REGISTER AS ASCII @

	AND R3,R3,#0	; INITIALIZE THE REGISTER
	LD R3,ASC_SPACE	; REGISTER BECOME SPACE CHAR

START_LINE

	AND R0,R0,#0	; CLEAR REGISTER
	ADD R0,R2,R1	; R0 BECOME CORRESPONDING CHARACTER IN THE LOOP
	OUT	; PRINT FIRST CHARACTER

	ADD R0,R3,#0	; MAKE OUTPUT CHARACTER SPACE 
	OUT	; PRINT SPACE

	AND R5,R5,#0	; CLEAR THE REGISTER
	LD R5,HIST_ADDR	; PULL HISTOGRAM STARTING ADDRESS
	ADD R5,R5,R2	; CURRENT STEP ADDED TO THE HISTOGRAM ADDRESS
	AND R6,R6,#0	; CLEAR R6
	LDR R6,R5,#0	; PULL HISTOGRAM VALUE
	ADD R5,R6,#0	; COPY HISTOGRAM VALUE TO R5

	AND R4,R4,#0	; CLEAR THE REGISTER
	ADD R4,R4,#4	; STORE NUMBER 4 TO COUNT PRINTED HEXADECIMAL CHAR

	

GET_HEX
	AND R0,R0,#0	; CLEAR THE CHAR OUTPUT REGISTER	
	ADD R5,R5,#0	; MAKE SURE R5 IS THE RECENT REGISTER
	BRzp ADD_DECFOUR	; IF BIT IS ZERO, SLIDE LEFT
	ADD R0,R0,#8	; IF BIT IS ONE, ADD 8 TO THE OUTPUT


ADD_DECFOUR
	ADD R5,R5,R5	; SLIDE BITS TO THE LEFT
	BRzp ADD_DECTWO	; IF BIT IS ZERO, SLIDE LEFT
	ADD R0,R0,#4	; IF BIT IS ONE, ADD 4 TO THE OUTPUT


ADD_DECTWO
	ADD R5,R5,R5	; SLIDE BITS TO THE LEFT
	BRzp ADD_DECONE	; IF BIT IS ZERO, SLIDE LEFT
	ADD R0,R0,#2	; IF BIT IS ONE, ADD 2 TO THE OUTPUT


ADD_DECONE
	ADD R5,R5,R5	; SLIDE BITS TO THE LEFT
	BRzp PRINT_HEX	; IF BIT IS ZERO, START PRINTING AND SLIDE LEFT
	ADD R0,R0,#1	; IF BIT IS ONE, ADD 1 TO THE OUTPUT


PRINT_HEX
	ADD R5,R5,R5	; SLIDE BITS TO THE LEFT
	AND R6,R6,#0	; CLEAR THE REGISTER
	ADD R6,R0,#-9	; CHECK IF OUTPUT IS BIGGER THAN 9
	BRp PRINT_ATLEASTA	; IF OUTPUT IS BIGGER THAN 1, MOVE ON TO PRINT CHAR
	LD R6,ASC_ZERO	; LOAD ASCII VALUE OF ZERO
	ADD R0,R0,R6	; TURN OUTPUT TO ASCII VALUE OF THAT NUMBER
	OUT	; PRINT HEXADECIMAL CHARATER
	BRnzp LOOP_CHECK	; MOVE ON TO SEE IF I PRINTED 4 CHARS FOR HISTOGRAM VALUE

PRINT_ATLEASTA
	ADD R0,R6,R1	; ASSIGN ASCII VALUR FOR NUMBER BIGGER THAN 9
	OUT	; PRINT THE CHAR

LOOP_CHECK
	ADD R4,R4,#-1	; DECREMENT R4 i.e. ONE MORE CHAR PRINTED FOR HISTOGRAM VALUE
	BRp GET_HEX	; IF NOT 4 CHARS PRINTED, KEEP GOING

	AND R0,R0,#0	; CLEAR R0
	LD R6,ASC_NLINE	; MAKE R6 CHAR NEW LINE
	ADD R0,R6,#0	; COPY R6 TO R0
	OUT	; PRINT NEW LINE

	ADD R2,R2,#1	; INCREMENT R2 i.e. ONE MORE LINE PRINTED
	LD R6,NUM_BINS	; I WANT TO SUBTRACT -27 FROM R2 BUT INSTRUCTION BITS ARE TOO SMALL
	NOT R6,R6	; INVERSE
	ADD R6,R6,#1	; MAKE R6=-27
	ADD R6,R2,R6	; SUBSTRACT R6 FROM R2
	BRn START_LINE	; IF NOT 27 LINE PRINTED, PRINT NEXT HISTOGRAM VALUE

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

ASC_AT		.FILL x0040 ; DECIMAL ASCII VALUE OF AT
ASC_SPACE	.FILL x0020 ; DECIMAL ASCII VALUE OF SPACE
ASC_ZERO	.FILL x0030 ; DECIMAL ASCII VALUE OF ZERO
ASC_NLINE 	.FILL x000A ; DECIMAL ASCII VALUE OF NEW LINE

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
