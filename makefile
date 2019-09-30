all:
	
	g++ -std=c++11 main.cpp ExpressionManager.cpp -o executable
	
clean: 

	rm -f executable