if [ -z "$1" ]
then
    echo "usage: doit s16_file_name (without extension)"
else
    printf "\n***** Compiling $1.s16 *****\n\n"
    s16c examples/$1.s16 -g -t -o examples/$1.s

    printf "\n***** Assembling *****\n\n"
    lsm-asm examples/$1.s -o examples/$1.bsm

    printf "\n***** Executing binary code *****\n\n"
    lsm-vm examples/$1.bsm
fi
