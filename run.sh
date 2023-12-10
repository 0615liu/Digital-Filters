#!/bin/bash
# mkdir scp

gcc -o simple_filter simple_filter.c -lm  
#lm for math.h
#draw M=1024 for 4pdf
./simple_filter 1024 hL.txt hR.txt YL.txt YR.txt blue_giant_fragment.wav output3.wav
python3 show_data.py hLM1024.pdf hRM1024.pdf YLM1024.pdf YRM1024.pdf 
#draw M=32 for 4pdf
./simple_filter 32 hL.txt hR.txt YL.txt YR.txt blue_giant_fragment.wav output2.wav
python3 show_data.py hLM32.pdf hRM32.pdf YLM32.pdf YRM32.pdf 
#draw M=8 for 4pdf
./simple_filter 8 hL.txt hR.txt YL.txt YR.txt blue_giant_fragment.wav output1.wav
python3 show_data.py hLM8.pdf hRM8.pdf YLM8.pdf YRM8.pdf 