; add 10 and 20 and print
.text
        bipush 10
        ipush 20
        iadd
        jsr pHex32
        halt

; print a 32-bits integer as hexadecimal
; value to print should be on top of stack
pHex32:
        ipush 28
L1:     dup2
        iushr
        ipush 0xF
        iand
        jsr pNibble
        dup
        ifeq L2
        ipush 4
        isub
        goto L1
L2:     pop
        ret

; print a 4-bits interger as ascii-hexadecimal
; value to print should be on top of stack
pNibble:
        ipush 0x30
        iadd
        dup
        ipush 0x39
        isub
        ifle L3
        ipush 0x0a
        iadd
L3:     write
        ret
