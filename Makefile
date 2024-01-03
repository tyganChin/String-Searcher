#########################################################
#                PROJECT 4: gerp Makefile     	     	#
#   Authors: Tygan Chin (tchin02) and Emily Ye (ye02)	#
#########################################################

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# program executable
gerp: main.o WordHash.o fileHash.o Word.o FSTree.o DirNode.o Gerp.o
	${CXX} ${LDFLAGS} -o gerp main.o WordHash.o fileHash.o Word.o FSTree.o \
	DirNode.o Gerp.o

## main
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# gerp class
Gerp.o: WordHash.o fileHash.o Word.o FSTree.o DirNode.o Gerp.h Gerp.cpp
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

## Hash class
WordHash.o: WordHash.h WordHash.cpp Word.o
	$(CXX) $(CXXFLAGS) -c WordHash.cpp

## File hash class
fileHash.o: fileHash.h fileHash.cpp FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -c fileHash.cpp

## Word class
Word.o: Word.h Word.cpp
	$(CXX) $(CXXFLAGS) -c Word.cpp

## testing framework
unit_test: unit_test_driver.o Word.o WordHash.o fileHash.o FSTree.o DirNode.o \
	Gerp.o
	$(CXX) $(CXXFLAGS) $^

# tests Word class
testWord:  testWordMain.cpp Word.o fileHash.o
	${CXX} ${LDFLAGS} -o testWord testWordMain.cpp Word.o fileHash.o

# tests WordHash class
testWordHash: testWordHashMain.cpp WordHash.o Word.o fileHash.o
	${CXX} ${LDFLAGS} -o testWordHash testWordHashMain.cpp Word.o WordHash.o \
	fileHash.o

# tests FileHash class
testFileHash: testFileHashMain.cpp fileHash.o Word.o
	${CXX} ${LDFLAGS} -o testFileHash testFileHashMain.cpp fileHash.o  Word.o

# tests print functions in Word, WordHash, and FileHash
testGerpMain: Gerp.o testGerpMain.cpp WordHash.o fileHash.o Word.o FSTree.o \
		DirNode.o
	${CXX} ${LDFLAGS} -o testGerpMain Gerp.o testGerpMain.cpp WordHash.o \
		fileHash.o Word.o FSTree.o DirNode.o

## provide command
provide: 
	provide comp15 proj4_gerp main.cpp Gerp.h Gerp.cpp fileHash.h \
		Makefile README fileHash.cpp WordHash.h \
		WordHash.cpp unit_tests.h Word.h Word.cpp testWordMain.cpp \
		testFileHashMain.cpp testWordHashMain.cpp testGerpMain.cpp \
		stringProcessing.h stringProcessing.cpp parseMain.cpp \
		FSTreeTraversal.cpp Tcasestrings.txt Tdoubleswitch.txt \
		Tempty.txt Temptyquit.txt Tendswitch.txt \
		Thalfwayswitch.txt Tinstantswitch.txt Tquit.txt Tstrings.txt \
		x.txt y.txt z.txt a.txt b.txt c.txt

## clean				
clean: 
	rm Word.o WordHash.o fileHash.o Gerp.o main.o