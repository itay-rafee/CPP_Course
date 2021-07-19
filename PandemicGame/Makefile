#!make -f
# This Makefile can handle any set of cpp and hpp files.
# To use it, you should put all your cpp and hpp files in the SOURCE_PATH folder.
# Thanks to Michael Trushkin for the idea!

SOURCE_PATH=sources
OBJECT_PATH=objects
CXX=clang++-9 
CXXVERSION=c++2a
CXXFLAGS=-std=$(CXXVERSION) -Werror -Wsign-conversion -I$(SOURCE_PATH)
TIDY_FLAGS=-extra-arg=-std=$(CXXVERSION) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=*
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=$(wildcard $(SOURCE_PATH)/*.cpp)
HEADERS=$(wildcard $(SOURCE_PATH)/*.hpp)
OBJECTS=$(subst sources/,objects/,$(subst .cpp,.o,$(SOURCES)))

run: test1 test2 test3

test: TestRunner.o Test.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test1: TestRunner.o StudentTest1.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test2: TestRunner.o StudentTest2.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test3: TestRunner.o StudentTest3.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

demo1: Demo1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
demo2: Demo2.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
main: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@


StudentTest1.cpp:  # Alomg Jakov Maatuf
	curl https://raw.githubusercontent.com/AlmogJakov/Pandemic/main/Test.cpp > $@

StudentTest2.cpp:  # Eyal Levi
	curl https://raw.githubusercontent.com/LeviEyal/Pandemic-Game/main/Test.cpp > $@

StudentTest3.cpp:  # Achiya Zigler
	curl https://raw.githubusercontent.com/achiyazigi/Pandemic-Game/main/Test.cpp > $@

tidy:
	clang-tidy $(SOURCES) $(TIDY_FLAGS) --

valgrind: test1 
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test1 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f $(OBJECTS) *.o test* demo*
	rm -f StudentTest*.cpp
