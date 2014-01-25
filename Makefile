README : gen_readme
	./gen_readme.exe | tee README.md | iconv -f UTF-8
gen_readme : gen_readme.cpp
	g++ -std=c++1y -o gen_readme gen_readme.cpp