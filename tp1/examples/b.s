; ...
.data
var0:   .word 10
var1:   .word 0x11, 0x12, 0x13141516, -1, 2
bss1:   .space 12
var2:   .word 1, 2, 3
bss2:   .space 10
bss3:   .space 4
var4:   .float 1.0

.text
L0:     ipush 20
        load var2
        store bss2
L1:     iadd ; Must give a runtime error. Data stack with only an element.
        halt
L2:
