; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; invalid use of labels ;;;;;

; - redefined label

    .text
t_redef_1:
t_redef_1:
        goto t_redef_1

    .data
d_redef_1:  .byte 1
d_redef_1:  .word 2

