SRCFILES = 

TESTFILES = \
	test/test-main.cpp \
	test/test-ptr-vector.cpp

CXXFLAGS = -I include

EXE = cl-utils-test

all:
	g++ -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)

492:
	g++-492 -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)
