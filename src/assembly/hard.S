.section .data
str:
.string "game over"
# comment
.section .text
.globl hard
.type hard, @function
# comment
hard:
    addi sp, sp, -4
    sw ra, 0(sp)
    # LCD_ShowString(40, 24, (u8 *)("Gameover"), GREEN);
    mv t0,a0
    li a0,4
    # comment
    li a0,4    
    beq t0,x0,end
    li a0,6
    # comment
end:
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

