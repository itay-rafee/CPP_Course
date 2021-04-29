#!make -f

CXX=clang++-9 
CXXFLAGS=-std=c++2a -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=NumberWithUnits.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: test1 test2 test3

test1: TestRunner.o StudentTest1.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test2: TestRunner.o StudentTest2.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test3: TestRunner.o StudentTest3.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o main

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

StudentTest1.cpp:  # Shlomo Glick
	curl https://raw.githubusercontent.com/shlomog12/ex3_partA/main/Test.cpp > $@

StudentTest2.cpp:  # Yair Raviv
	curl https://raw.githubusercontent.com/yairaviv/NumberWithUnits_a/main/Test.cpp > $@

StudentTest3.cpp:  # Roei Birger
	curl https://raw.githubusercontent.com/roei-birger/CPP_course_p3/master/Test.cpp > $@

tidy:
	clang-tidy $(SOURCES) -extra-arg=-std=c++2a -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory,-readability-isolate-declaration --warnings-as-errors=-* --

valgrind: test1
	valgrind --leak-check=full --error-exitcode=99 --tool=memcheck $(VALGRIND_FLAGS) ./test1 

clean:
	rm -f *.o test*
	rm -f StudentTest*.cpp
