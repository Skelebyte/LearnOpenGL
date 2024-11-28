# output:
#     g++ main.cpp src/*.cpp libs/glad/glad.c -o Program.x86_64 -lglfw -lm
# src/*.cpp

compile:
	g++ -o Program.x86_64 main.cpp libs/glad/glad.c -lglfw -lm


run: compile
	./Program.x86_64
