./compiler/cstickman < $1 > ./compiled/compiled.c
gcc -o stickman.st compiled/compiled.c compiler/helpers/lib.c
