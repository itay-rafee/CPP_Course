#!make -f

CXX=clang++-9 
CXXVERSION=c++2a
SOURCE_PATH=sources
OBJECT_PATH=objects
CXXFLAGS=-std=$(CXXVERSION) -Werror -Wsign-conversion -I$(SOURCE_PATH)
TIDY_FLAGS=-extra-arg=-std=$(CXXVERSION) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=*
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=$(wildcard $(SOURCE_PATH)/*.cpp)
HEADERS=$(wildcard $(SOURCE_PATH)/*.hpp)
OBJECTS=$(subst sources/,objects/,$(subst .cpp,.o,$(SOURCES)))

run: test1 test2 test3

test1: TestRunner.o StudentTest1.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test2: TestRunner.o StudentTest2.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test3: TestRunner.o StudentTest3.o  $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

demo: Demo.o $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $^ -o $@


StudentTest1.cpp:  # Michael Trushkin
	curl https://raw.githubusercontent.com/miko-t/binaryTreeCpp/main/Test.cpp > $@

StudentTest2.cpp:  # Yuval Moshe
	curl https://raw.githubusercontent.com/Yuval-Moshe/CPP-binarytree-a/master/Test.cpp > $@

StudentTest3.cpp:  # Asahel Cohen
	curl https://raw.githubusercontent.com/asahelcohen/BinaryTree-tamplate-cpp/main/Test.cpp > $@


tidy:
	clang-tidy sources/BinaryTree.hpp $(TIDY_FLAGS) --

valgrind: test1
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test1 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f $(OBJECTS) *.o test* demo*
	rm -f StudentTest*.cpp
