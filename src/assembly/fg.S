.section .data
    # comment
str1:
.string "You win"
    # comment
str2:
.string "GAME OVER"
    # comment
.section .text
.globl fg
.type fg, @function
    # comment
fg:
    addi sp, sp, -4
    sw ra, 0(sp)
    # comment
    mv t2,a0
    mv t3,a1
    # LCD_ShowNum(68,10,cscore,1,GRAY);
    li a0, 120
    li a1, 10
    # comment
    mv a2, t2
    mv a3, t3
    # comment
    li a4, 0X8430
    jal LCD_ShowNum
    # comment
    li a0, 120
    li a1, 10
    # comment
    mv a2, t2
    mv a3, t3
    # comment
    li a4, 0X8430
    jal LCD_ShowNum
    # LCD_ShowString(50, 24, (u8 *)("You lose"), RED); 
    li a0, 50
    li a1, 24
    la a2, str2
    # comment
    li a3, 0xF800
    jal LCD_ShowString
    li a0, 50
    # comment
    li a1, 24
    la a2, str2
    li a3, 0xF800
    jal LCD_ShowString
    # comment
    lw ra, 0(sp)
    addi sp, sp, 4
    ret
