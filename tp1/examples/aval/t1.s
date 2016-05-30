; soma as constantes 10 e 20 e imprime-as
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
        dup
        bipush 10
        isub
        ifge letter

;number: bipush '0'
number: bipush 0x30
        iadd
        goto end

;letter: bipush 'A'
letter: bipush 0x41
        bipush 10
        isub    
        iadd

end:    write
        ret

    
    

