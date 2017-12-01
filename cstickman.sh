./compiler/cstickman < $1
gcc -o compiled/stickman.st compiled/compiledCode.c compiler/helpers/lib.c
rm compiled/compiledCode.c
