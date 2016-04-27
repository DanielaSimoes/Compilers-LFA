; Add 10 and 20, previously placed in memory.
.data
var0:   .word 10
var1:   .word 20
vvv:    .space 0x100

.text
    load var0
    load var1
    iadd
    halt
