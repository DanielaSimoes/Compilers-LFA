; soma duas variaveis

    .data
var0:   .word 10
var1:   .word 20


    .text
ini:
    load var0
    load var1
    iadd

    .data
var2:   .space 4

    .text
    store var2
    halt
