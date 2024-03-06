LIBS=-lsfml-graphics -lsfml-window -lsfml-system

pacman: main.o engine.o board.o coin.o occupant_list.o occupant.o wall.o pacman.o draw_manager.o texture_manager.o navigation.o
	g++ -o pacman main.o engine.o board.o coin.o occupant_list.o occupant.o wall.o pacman.o draw_manager.o texture_manager.o navigation.o $(LIBS)

main.o: main.cpp
	g++ -c main.cpp 

engine.o: engine.cpp engine.h board.h wall.h pacman.h wall_type.h moves.h
	g++ -c engine.cpp

board.o: board.h board.cpp occupant_list.h coin.h
	g++ -c board.cpp

coin.o: coin.cpp coin.h
	g++ -c coin.cpp

occupant_list.o: occupant_list.cpp occupant_list.h occupant.h
	g++ -c occupant_list.cpp

occupant.o: occupant.cpp occupant.h
	g++ -c occupant.cpp

wall.o: wall.cpp wall.h
	g++ -c wall.cpp

pacman.o: pacman.cpp pacman.h
	g++ -c pacman.cpp

draw_manager.o: draw_manager.cpp draw_manager.h texture_manager.h occupant_list.h wall.h pacman.h wall_type.h moves.h
	g++ -c draw_manager.cpp

texture_manager.o: texture_manager.cpp texture_manager.h
	g++ -c texture_manager.cpp

navigation.o: navigation.cpp navigation.h occupant.h
	g++ -c navigation.cpp



