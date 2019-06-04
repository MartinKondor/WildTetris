# Can also be compiled with the "-static-libstdc++" flag
# plus with the "libgcc_s_sjlj-1.dll" file

CC=g++
SOURCE=src/wildtetris.cpp
FLAGS= -std=c++17 -I"headers" -static-libstdc++
EXE=bin/wildtetris.exe

build:
	@$(CC) $(SOURCE) $(FLAGS) -o $(EXE)
	
runtest:
	@$(CC) $(SOURCE) $(FLAGS) -o $(EXE)
	@$(EXE)
