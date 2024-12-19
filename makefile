flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: a.exe
	a.exe Code.txt Tree.dot

a.exe: main.o ReadData.o LexicalAnalysis.o RecursiveDescent.o DrawTree.o
	g++ main.o ReadData.o LexicalAnalysis.o RecursiveDescent.o DrawTree.o

main.o: main.cpp
	g++ -c $(flags) main.cpp

ReadData.o: ReadData.cpp
	g++ -c $(flags) ReadData.cpp

LexicalAnalysis.o: LexicalAnalysis.cpp
	g++ -c $(flags) LexicalAnalysis.cpp

RecursiveDescent.o: RecursiveDescent.cpp
	g++ -c $(flags) RecursiveDescent.cpp

DrawTree.o: DrawTree.cpp
	g++ -c $(flags) DrawTree.cpp

clean:
	rm -rf *.o *.exe
