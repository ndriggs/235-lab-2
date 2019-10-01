all:
	
	g++ -std=c++11 testmain.cpp ExpressionManager.cpp -o executable
	
clean: 

	rm -f executable