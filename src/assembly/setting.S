.section .data
str:
# comment_
.string "Setting"
str1:
# comment_
.string "east(0)  hard(1)"
.section .text
# comment_
.globl setting
.type setting, @function
# comment_
setting:
    addi sp, sp, -4
    sw ra, 0(sp)
    # LCD_Clear(BLACK);
    li a0, 0x0000
    jal LCD_Clear
    # LCD_ShowString(40, 24, (u8 *)("Setting"), GREEN);
    li a0, 40
    li a1, 24
    la a2, str
    # comment_
    li a3, 0x07E0
    li a0, 40
    li a1, 24
    la a2, str
    # comment_
    li a3, 0x07E0
    jal LCD_ShowString
    # comment_
    # LCD_ShowString(30, 40, (u8 *)("easy hard"), GREEN);
    li a0, 16
    li a1, 48
    la a2, str1
    # comment_
    li a3, 0x07E0
    li a1, 48
    # comment_
    la a2, str1   
    jal LCD_ShowString
    # comment_
    li a0, 16
    li a1, 48
    la a2, str1
    # comment_
    li a3, 0x07E0
    li a1, 48
    # comment_
    la a2, str1   
    jal LCD_ShowString
    lw ra, 0(sp)
    addi sp, sp, 4
    ret
    # comment_
