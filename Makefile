.PHONY: t1
t1: t1.cpp
	g++ -Wall -std=c++11 -pthread t1.cpp -o t1

t2: t2.cpp
	g++ -Wall -std=c++11 -pthread t2.cpp -o t2

t3: t3.cpp
	g++ -Wall -std=c++11 -pthread t3.cpp -o t3

t3a: t3a.cpp
	g++ -Wall -std=c++11 -pthread t3a.cpp -o t3a

t4: t4.cpp
	g++ -Wall -std=c++11 -pthread t4.cpp -o t4

