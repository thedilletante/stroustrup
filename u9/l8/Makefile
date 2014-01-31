calc: main.o driver.o parser.o lexer.o ariphmetic.o
	clang++ -o calc main.o driver.o parser.o lexer.o ariphmetic.o

main.o: main.cpp lexer.h calc_driver.h
	clang++ -c main.cpp

driver.o: calc_driver.cpp calc_driver.h lexer.h parser.h
	clang++ -c calc_driver.cpp -o driver.o

parser.o: parser.cpp parser.h lexer.h ariphmetic.h
	clang++ -c parser.cpp

lexer.o: lexer.cpp lexer.h
	clang++ -c lexer.cpp

ariphmetic.o: ariphmetic.cpp ariphmetic.h
	clang++ -c ariphmetic.cpp

clean:
	rm -f calc *.o