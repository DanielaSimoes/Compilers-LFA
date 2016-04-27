; Add 10.0 and 20.0, previously placed in memory.
.data
var0:   .float 10
var1:   .float 20

.text
    load var0
    load var1
    fadd
    halt
