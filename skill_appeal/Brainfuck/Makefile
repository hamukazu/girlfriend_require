FTMP_DIR=../../../FTMP/include
all : C C++ TMP Haskell
C : C.c
	gcc -std=c11 -g -o C C.c -Wall -Wextra -Werror
C++ : C++.cpp
	g++ -std=c++1y -g -o C++ C++.cpp -Wall -Wextra -Werror
TMP : TMP.cpp
	g++ -std=c++1y -g -o TMP TMP.cpp -Wall -Wextra -Werror -I$(FTMP_DIR)
Haskell : Haskell.hs
	ghc Haskell
