#!/bin/bash
gcc -I../ test_shape_1.c ../shape.c ../point.c -o bin/test_shape_1 -lm
./bin/test_shape_1
