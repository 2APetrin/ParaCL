# ParaCL
Emil Galimov and Anton Petrin</br>
MIPT DREC second year students

## Description
ParaCL (Para C language) is a study c++ project, which contains our expirience and habits of c++ programming. Project imitates work of a real compiler and interpreter of a real C language.

Some of the goals were to learn about final-state machines, explore gnu flex and bison potential of generating LALR(1) parsers and write our version of grammar. Using all above we've wrote ParaCL.

This project consists of two parts:</br>
"frontend" - flex and bison part, where executes parsing and ast tree is created.</br>
"interpreter" - execution of created tree.

> [!NOTE]
> To debug tree faster we used graphviz dumping.

## Frontend

## Build
Cloning
```
git clone https://github.com/2APetrin/ParaCL.git
cd ParaCL
```
Making
```
cmake -B build
cd build
make
```
If graphviz is installed on your computer use `cmake -B build -DCMAKE_CXX_FLAGS="-DDUMP"` to have ast tree graphviz dump in ast/logs/images.

Using
```
./ParaCL [-s] [-p] *code path*
```
-s and -p to generate parser and scanner debug traces respectively

Example
```
./ParaCL ../test/work_examples/factorial.prcl
```