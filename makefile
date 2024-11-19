compile:
	g++ main.cpp src/*.cpp libs/glad/*.c -o Program.x86_64 -lglfw -lm

run: compile
	./Program.x86_64
