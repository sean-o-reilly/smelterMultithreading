CXX = clang++
CXXFLAGS = -fsanitize=address -g -O1
LDLFLAGS = -fsanitize=address

build_main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LDLFLAGS)

run_main: main
	clang++ -fsanitize=address -g -o main main.cpp
	./main

clean:
	rm -f main

# asan:
# 	clang++ -fsanitize=address -g -o main main.cpp
# 	./main