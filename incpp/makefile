all: compile link

compile: 
	g++ -c main.cpp -I"C:\src\SFML-2.6.0\include" -DSFML_STATIC -std=c++17

link:
	g++ main.o -o main -L"C:\src\SFML-2.6.0\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	del *.o
	del main.exe