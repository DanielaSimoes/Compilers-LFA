; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; errors on instructions ;;;;;

    .text

; - extra or invalid argument in instruction

    ipush   11.1
    bipush  11.1
    ipush   "abs"
    ifeq 1111
    goto 222222222
    jsr 33333
L1: fpush L1
L2: ipush L2
L3: bipush L3
    load 6666
    store 44444444444444
    ret 11
    ret L3
    write 11

