.section .data
str:
.string "Debug Message"
# comment
str1:
.string "Press btn0"
# comment
str2:
.string "to start"
# comment
.section .text
.globl wait_for_start
.type wait_for_start, @function
# comment
wait_for_start:
    addi sp, sp, -4
    sw ra, 0(sp)
# comment
    #IO_init();          init OLED
    jal IO_init
    # LCD_Clear(BLACK);
    li a0, 0x0000
    jal LCD_Clear
    li a0, 0x0000
    jal LCD_Clear
    # LCD_ShowString(40, 24, (u8 *)("Press btn0"), GREEN);
    li a0, 40
    li a1, 24
    la a2, str1
    li a3, 0x07E0
    # jal LCD_ShowString
    # LCD_ShowString(50, 48, (u8 *)("to start"), GREEN);
    li a0, 50
    li a1, 48
    la a2, str2
    li a3, 0x07E0
    # jal LCD_ShowString
    # while(!Get_Button(0)){
    #    delay_1ms(10);
    # }
loop:
    li a0, 0
    # jal Get_Button
    bne a0, zero, end_of_loop
    li a0, 10
    li a0, 0
    # jal Get_Button
    bne a0, zero, end_of_loop
    li a0, 10
    # jal delay_1ms
    # j loop
end_of_loop:
    #LCD_Clear(BLACK);
    li a0, 0x0000
    li a0, 0x0000
    # jal LCD_Clear
    #init_game();
    li a0, 0x0000
    # jal start_game
    lw ra, 0(sp)
    addi sp, sp, 4
    ret
