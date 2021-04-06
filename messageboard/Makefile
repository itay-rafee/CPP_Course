#!make -f

CXX=clang++-9 
CXXFLAGS=-std=c++2a -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Board.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: test
	./$^

test: TestRunner.o StudentTest1.o StudentTest2.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

main: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o main

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

StudentTest1.cpp:  # Shani Shuv
	curl https://raw.githubusercontent.com/ShaniShuv/cppm2/master/Test.cpp > $@

StudentTest2.cpp:  # Reut Maslansky
	curl https://raw.githubusercontent.com/Reut-Maslansky/Ariel-CPP--ex2/master/Test.cpp > $@

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: test
	valgrind --leak-check=full --error-exitcode=99 --tool=memcheck $(VALGRIND_FLAGS) ./test 

clean:
	rm -f *.o test
	rm -f StudentTest*.cpp
