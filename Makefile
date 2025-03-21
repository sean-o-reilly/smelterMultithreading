CXX = clang++
CXXFLAGS = -fsanitize=address -g -O1
LDLFLAGS = -fsanitize=address

build_main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LDLFLAGS)

run_main: main run.sh
	clang++ -fsanitize=address -g -o main main.cpp
	./main

sh: main run.sh
	chmod +x run.sh
	./run.sh

clean:
	rm -f main
