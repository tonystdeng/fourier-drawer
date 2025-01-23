g++ -c ./src/svglib.cpp ./src/compile.cpp ./src/main.cpp ./src/view.cpp 
g++ ./svglib.o ./compile.o ./main.o ./view.o -o fourierDrawer -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2
rm ./svglib.o ./compile.o ./main.o ./view.o
./fourierDrawer c ./svgs/eighthNote.svg
#python ./src/compile.py
./fourierDrawer o ./svgs/eighthNote.svg.dc