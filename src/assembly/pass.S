.section .data
str:
.string "game over"
# comment
.section .text
.globl pass
.type pass, @function
# comment
gameover:
    addi sp, sp, -4
    sw ra, 0(sp)
    # LCD_ShowString(40, 24, (u8 *)("Gameover"), GREEN);
    li a0, 40
    li a1, 24
    # comment
    li a0, 40
    li a1, 24
    # comment
    la a2, str
    # comment
    li a3, 0x07E0
    jal LCD_ShowString
    # comment
    li a0, 40
    li a1, 24
    # comment
    la a2, str
    # comment
    li a3, 0x07E0
    jal LCD_ShowString
    # comment
    li a0, 40
    li a1, 24
    # comment
    la a2, str
    # comment
    li a3, 0x07E0
    jal LCD_ShowString
    # LCD_ShowNum(68,10,cscore,1,GRAY);
    li a0, 68
    li a1, 10
    # comment
    li a2, 78
    li a3, 20
    # comment
    # comment
    li a4,0x0000
    jal LCD_Fill
    # comment
    li a0, 68
    li a1, 10
    # comment
    li a2, 78
    li a3, 20
    # comment
    li a4,0x0000
    jal LCD_Fill
    # comment
    lw ra, 0(sp)
    addi sp, sp, 4
    ret