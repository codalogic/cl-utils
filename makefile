SRCFILES = \
    src/cl-utils/str-args.cpp

TESTFILES = \
	test/test-command-line-args.cpp \
	test/test-history-buffer.cpp \
	test/test-iterator-range.cpp \
	test/test-main.cpp \
	test/test-ptr-vector.cpp \
	test/test-str-args.cpp \
	test/test-str-convert.cpp \
	test/test-str-trim.cpp

CXXFLAGS = -I include

EXE = test/cl-utils-test

all:
	g++ -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)

492:
	g++-492 -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)

540:
	g++-540 -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)

630:
	g++-630 -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)

710:
	g++-710 -o $(EXE) $(CXXFLAGS) $(SRCFILES) $(TESTFILES)
