; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; invalid use of labels ;;;;;

; - .text label used as .data one

    .text
t_redef_2:  iadd
        store t_redef_2

