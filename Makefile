build:
		rm -rf ./bin
		mkdir ./bin
		g++ -std=c++20 -o ./bin/main ./src/main.cpp
		chmod +x ./bin/main

ad_demo:
		rm -rf ./bin
		mkdir ./bin
		g++ -std=c++20 -o ./bin/ad_demo ./tests/ad_test.cpp
		chmod +x ./bin/ad_demo
		./bin/ad_demo

matrix_demo:
		rm -rf ./bin
		mkdir ./bin
		g++ -std=c++20 -o ./bin/matrix_demo ./tests/matrix_test.cpp
		chmod +x ./bin/matrix_demo
		./bin/matrix_demo

vector_demo:
		rm -rf ./bin
		mkdir ./bin
		g++ -std=c++20 -o ./bin/vector_demo ./tests/vector_test.cpp
		chmod +x ./bin/vector_demo
		./bin/vector_demo

run:
		./bin/main

clean:
		rm -rf ./bin
