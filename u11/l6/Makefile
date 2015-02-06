#FLAGS=-std=c++11 -D_DBG_MODE_ -g
FLAGS=-std=c++11 -g

big_int: big_int.o BI_Impl.o main.o
	clang++ $(FLAGS) big_int.o BI_Impl.o main.o	-o big_int

big_int.o: big_int.h big_int.cpp
	clang++ $(FLAGS) -c big_int.cpp

BI_Impl.o: BI_Impl.h BI_Impl.cpp big_int.h
	clang++ $(FLAGS) -c BI_Impl.cpp

main.o: main.cpp big_int.h
	clang++ $(FLAGS) -c main.cpp

clean:
	rm -rf *.o
