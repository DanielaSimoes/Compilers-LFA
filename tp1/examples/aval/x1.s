; soma duas variaveis

    .data
var0:   .word 10
var1:   .word 20
var2:   .space 4


    .text
ini:
    load var0
    load var1
    iadd
    store var2
    halt
