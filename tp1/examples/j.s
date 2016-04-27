; Save a constant to the allocated space and load it again.
.data
bss:    .space 12
var:   .word 1, 2, 3

.text
L0:     ipush 20
        load var
        store bss
	load bss
L1:     iadd
        halt
L2:
