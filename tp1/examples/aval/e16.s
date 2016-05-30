; error situations

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;; errors and warnings on values ;;;;;
    .data

; - wrong list of values
on_values_b:    .word 1,,2
on_values_c:    .byte 3,4,
on_values_d:    .float 1.1, 2,2
on_values_e:    .string "ab1", "ab2"
on_values_f:    .space 1,2

on_values_g:    .word 
on_values_h:    .byte
on_values_i:    .float 
on_values_j:    .string
on_values_k:    .space

on_values_z:    .word 1

