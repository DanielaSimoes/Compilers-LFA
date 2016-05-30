; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; invalid use of labels ;;;;;

; - undefined label

    .text
        goto t_undef_1
        store d_undef_1

