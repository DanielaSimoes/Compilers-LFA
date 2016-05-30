; 
    .text
        bipush 10
        ipush 20
        iadd
        ipush 20
        isub
        ipush 20
        imul
        ipush 20
        idiv
        ipush 20
        irem
        ineg
        ipush 20
        iand
        ipush 20
        ior
        ipush 20
        ixor
        ipush 20
        ishl
        ipush 20
        ishr
        ipush 20
        iushr
        jsr pHex32
        halt

    .text
        fpush 1.1
        fpush 1.2
        fadd
        fpush 1.2
        fsub
        fpush 1.2
        fmul
        fpush 1.2
        fdiv
        fpush 1.2
        frem
        fneg
        f2i
        i2f

    .text
        goto label
        bipush 1
        ifeq label
        bipush 1
        ifne label
        bipush 1
        iflt label
        bipush 1
        ifge label
        bipush 1
        ifgt label
        bipush 1
        ifle label

    .text
        dup
        pop
        dup_x1
        dup2
        swap

    .text
        bipush 1
        bipush 1
        baload
        bipush 1
        bipush 1
        bastore

        bipush 1
        bipush 1
        iaload
        bipush 1
        bipush 1
        iastore
        
        bipush 1
        bipush 1
        faload
        bipush 1
        bipush 1
        fastore
        
    .text
label:
        nop
        read
        write
        halt
    
    .text
        bipush 10
        ipush 20
        iadd
        ipush 0x10
        isub
        ipush -1
        imul
        ipush -0x2
        idiv
        ipush 'a'
        irem
        ineg
        ipush -'a'
        iand
        ipush '\n'
        ior
        ipush 07
        ixor
        ipush 20
        ishl
        ipush 20
        ishr
        ipush 20
        iushr
        jsr pHex32
        halt

