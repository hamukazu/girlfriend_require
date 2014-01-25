all :
	+cd skill_appeal && make
	+make README
README : gen_readme
	./gen_readme.exe | tee README.md | iconv -f UTF-8
gen_readme : gen_readme.cpp
	g++ -std=c++1y -Wall -Wextra -Werror -o gen_readme gen_readme.cpp
commit : README
	+git commit -a
	+git push origin master