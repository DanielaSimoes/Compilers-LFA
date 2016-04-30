.data
arrayint:   .word   1, 2, 3, 4, 5
arrayint2:  .word   1, 2, 3, 4, 5
arrayfloat: .float  1.0, 2.0, 3.0, 4.0, 5.0

.text                   ; stack from top to bottom
la      arrayint        ; &arrayint
ipush   0               ; 0, &arrayint
iaload                  ; arrayint[0]=1
la      arrayint2       ; &arrayint2, 1
ipush   3               ; 3, $arrayint2, 1
baload                  ; arrayint2[3]=4, 1
la      arrayfloat      ; $arrayfloat, 4, 1
ipush   2               ; 2, &arrayfloat, 4, 1
faload                  ; arrayfloat[2]=3.0 (0x40400000), 4, 1
f2i                     ; 3, 4, 1
iadd                    ; 7, 1
iadd                    ; 8
ipush 80                ; 80, 8
iadd                    ; 88
write                   ; 'X'
halt
