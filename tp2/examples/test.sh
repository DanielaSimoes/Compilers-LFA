#!/usr/bin/env bash

FILES=$(ls examples/*.s.expected)

# colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[1;34m'
NC='\033[0m' # No Color

for f in $FILES; do
  f=$(echo $f | sed -e 's/.s.expected//g')
  printf "${BLUE}${f}${NC}\n"

  ./s16c -g -o $f.s -t $f.s16 > /dev/null 2>&1

  diff $f.s $f.s.expected

  if [[ $? == 0 ]]; then
    printf "${GREEN}PASSED${NC}\n"
  else
    printf "${RED}FAIL${NC}\n"
  fi

  # assembling
  # lsm-asm examples/$f.s -o examples/$f.bsm
  #executing binary code
  # lsm-vm examples/$f.bsm
done
