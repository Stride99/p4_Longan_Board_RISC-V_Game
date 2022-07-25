.section .data
str:
.string "game over"
.section .text
.globl update
.type update, @function
update:
    addi sp, sp, -4
    sw ra, 0(sp)
    #t0 = cscore
    mv t0, a0
    mv t1, a1
    mv t2,a2
    beq t2,x0,f1
    #LCD_ShowString(40, 24, (u8 *)("Gameover"), GREEN);
    li a0, 40
    li a1, 24
    li a0, 40
    li a1, 24
    la a2, str
    li a3, 0x07E0
    jal LCD_ShowString 
f1: 
   # LCD_ShowNum(68,10,cscore,1,GRAY);
    li a0, 120
    li a1, 10
    li a0, 120
    li a1, 10    
    mv a2, t0
    mv a3, t1
    li a4, 0X8430
    jal LCD_ShowNum
    lw ra, 0(sp)
    addi sp, sp, 4
    ret
