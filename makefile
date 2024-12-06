# output:
#     g++ main.cpp src/*.cpp libs/glad/glad.c -o Program.x86_64 -lglfw -lm
# src/*.cpp
#
# if compile with imgui it fucks the compile time. its really bad.

compile:
	g++ -o Program.x86_64 main.cpp Hazrd/libs/glad/glad.c -lglfw -lm


run: compile
	./Program.x86_64
