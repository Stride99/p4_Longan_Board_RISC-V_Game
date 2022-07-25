.section .data
str:
.string "game over"
# comment
.section .text
.globl fill
.type fill, @function
# comment
fill:
    addi sp, sp, -4
    sw ra, 0(sp)
    # LCD_ShowString(40, 24, (u8 *)("Gameover"), GREEN);
    mv t0, a0
    mv t1, a1
    # comment
    mv t2, a2
    # comment
    mv t3, a3
    mv t4, a4
    # comment
    # comment
    # jal LCD_ShowString
    # LCD_ShowNum(68,10,cscore,1,GRAY);
    mv a0, t0
    mv a1, t1
    # comment
    mv a2, t2
    mv a3, t3
    # comment
    mv a4, t4
    jal LCD_Fill
    # comment
    mv a1, t1
    # comment
    mv a2, t2
    mv a3, t3
    # comment
    mv a4, t4
    jal LCD_Fill
    # comment
    lw ra, 0(sp)
    addi sp, sp, 4
    ret