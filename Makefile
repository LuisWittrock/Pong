all:
	g++ -c src/main.cpp -I/include
	g++ main.o -o game -L/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
	rm main.o