all: clean compile run

compile: main.cpp piece.cpp board.cpp
	
	 g++ -std=c++11 -o chess main.cpp piece.cpp board.cpp
run:
	
	@./chess
	
clean:
	
	@rm -f *.o
	@rm -f chess
