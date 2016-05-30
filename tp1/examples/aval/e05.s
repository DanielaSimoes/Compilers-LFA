; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; invalid use of labels ;;;;;

; - same label used in .text and .data

    .data
x_redef_1:  .word 3
    .text
x_redef_1:  iadd

    .text
y_redef_1:  iadd
    .data
y_redef_1:  .word 2
