FTMP_DIR=../../../FTMP/include
all : C++ TMP Haskell
C++ : C++.cpp
	g++ -std=c++1y -g -o C++ C++.cpp -Wall -Wextra -Werror
TMP : TMP.cpp
	g++ -std=c++1y -g -o TMP TMP.cpp -Wall -Wextra -Werror -I$(FTMP_DIR)
Haskell : Haskell.hs
	ghc Haskell