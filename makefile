# output:
#     g++ main.cpp src/*.cpp libs/glad/glad.c -o Program.x86_64 -lglfw -lm
compile:
	g++ -o Program.x86_64 main.cpp src/*.cpp libs/glad/glad.c -lglfw -lm


run: compile
	./Program.x86_64
