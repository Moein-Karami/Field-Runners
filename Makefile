rsdl=rsdl.cpp -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
compile=g++ -std=c++11
inc = . #./includes
src = . #./Src

all : FieldRunners.out

FieldRunners.out : Thing.o Tool.o Enemy.o Bullet.o Building.o Graphic.o Game.o Main.o Option.o
	${compile} Thing.o Tool.o Enemy.o Bullet.o Building.o Option.o Graphic.o Game.o Main.o ${rsdl} -o FieldRunners.out

Main.o : ${srs}/Main.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Tool.hpp ${inc}/Enemy.hpp ${inc}/Bullet.hpp ${inc}/Building.hpp ${inc}/Graphic.hpp ${inc}/Game.hpp ${inc}/Option.hpp
	${compile} -c ${srs}/Main.cpp ${rsdl}

Game.o : ${srs}/Game.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Tool.hpp ${inc}/Enemy.hpp ${inc}/Bullet.hpp ${inc}/Building.hpp ${inc}/Graphic.hpp ${inc}/Game.hpp ${inc}/Option.hpp
	${compile} -c ${srs}/Game.cpp ${rsdl}

Graphic.o : ${srs}/Graphic.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Tool.hpp ${inc}/Enemy.hpp ${inc}/Bullet.hpp ${inc}/Building.hpp ${inc}/Graphic.hpp ${inc}/Option.hpp
	${compile} -c ${srs}/Graphic.cpp ${rsdl}

Building.o : ${srs}/Building.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Tool.hpp ${inc}/Enemy.hpp ${inc}/Bullet.hpp ${inc}/Building.hpp
	${compile} -c ${srs}/Building.cpp ${rsdl}

Bullet.o : ${srs}/Bullet.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Tool.hpp ${inc}/Enemy.hpp ${inc}/Bullet.hpp
	${compile} -c ${srs}/Bullet.cpp ${rsdl}

Enemy.o : ${srs}/Enemy.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp ${inc}/Enemy.hpp
	${compile} -c ${srs}/Enemy.cpp ${rsdl}

Option.o : ${srs}/Option.cpp ${inc}/Option.hpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp 
	${compile} -c ${srs}/Option.cpp ${rsdl}

Thing.o : ${srs}/Thing.cpp ${inc}/LibrariesAndDefines.hpp ${inc}/Thing.hpp 
	${compile} -c ${srs}/Thing.cpp ${rsdl}

Tool.o : ${srs}/Tool.cpp ${inc}/LibrariesAndDefines.hpp
	${compile} -c ${srs}/Tool.cpp ${rsdl}

clean :
	rm *.o *.out