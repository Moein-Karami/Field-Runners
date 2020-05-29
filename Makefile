rsdl=rsdl.cpp -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
compile=g++ -std=c++11

all : FieldRunners.out

FieldRunners.out : Thing.o Tool.o Enemy.o Bullet.o Building.o Graphic.o Game.o Main.o Option.o
	${compile} Thing.o Tool.o Enemy.o Bullet.o Building.o Option.o Graphic.o Game.o Main.o ${rsdl} -o FieldRunners.out

Main.o : Main.cpp LibrariesAndDefines.hpp Thing.hpp Tool.hpp Enemy.hpp Bullet.hpp Building.hpp Graphic.hpp Game.hpp Option.hpp
	${compile} -c Main.cpp ${rsdl}

Game.o : Game.cpp LibrariesAndDefines.hpp Thing.hpp Tool.hpp Enemy.hpp Bullet.hpp Building.hpp Graphic.hpp Game.hpp Option.hpp
	${compile} -c Game.cpp ${rsdl}

Graphic.o : Graphic.cpp LibrariesAndDefines.hpp Thing.hpp Tool.hpp Enemy.hpp Bullet.hpp Building.hpp Graphic.hpp Option.hpp
	${compile} -c Graphic.cpp ${rsdl}

Building.o : Building.cpp LibrariesAndDefines.hpp Thing.hpp Tool.hpp Enemy.hpp Bullet.hpp Building.hpp
	${compile} -c Building.cpp ${rsdl}

Bullet.o : Bullet.cpp LibrariesAndDefines.hpp Thing.hpp Tool.hpp Enemy.hpp Bullet.hpp
	${compile} -c Bullet.cpp ${rsdl}

Enemy.o : Enemy.cpp LibrariesAndDefines.hpp Thing.hpp Enemy.hpp
	${compile} -c Enemy.cpp ${rsdl}

Option.o : Option.cpp Option.hpp LibrariesAndDefines.hpp Thing.hpp 
	${compile} -c Option.cpp ${rsdl}

Thing.o : Thing.cpp LibrariesAndDefines.hpp Thing.hpp 
	${compile} -c Thing.cpp ${rsdl}

Tool.o : Tool.cpp LibrariesAndDefines.hpp
	${compile} -c Tool.cpp ${rsdl}

clean : 
	rm *.o *.out