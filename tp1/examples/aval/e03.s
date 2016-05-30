; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; invalid use of labels ;;;;;

; - .data label used as .text one

    .data
d_redef_2:  .word 1

    .text
        goto d_redef_2

