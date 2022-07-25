.section .data
str:
# comment_
.string "Dino"
str1:
# comment_
.string "Play  Setting(0)"
.section .text
# comment_
.globl play_setting
.type play_setting, @function
# comment_
play_setting:
    addi sp, sp, -4
    sw ra, 0(sp)
    # LCD_Clear(BLACK);
    li a0, 0x0000
    jal LCD_Clear
    # LCD_ShowString(40, 24, (u8 *)("Dino"), GREEN);
    li a0, 35
    li a1, 20
    la a2, str
    # comment_
    li a0, 35
    li a1, 20  
    # comment_   
    li a3, 0x07E0
    jal LCD_ShowString
    # comment_
    # LCD_ShowString(30, 40, (u8 *)("play_setting(0)"), GREEN);
    li a0, 10
    li a1, 40
    la a2, str1
    # comment_
    li a0, 10
    li a1, 40   
    li a3, 0x07E0
    jal LCD_ShowString
    # comment_
    lw ra, 0(sp)
    addi sp, sp, 4
    ret
    # comment_
