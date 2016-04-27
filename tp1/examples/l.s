; Program with an invalid label and a nonexistent label. Must give 2 errors.
.data
var: .word 323

.text
jsr var
jsr labelnotdeclared
