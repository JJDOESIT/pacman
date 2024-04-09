LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src

SRCNAMES = main.cpp board.cpp coin.cpp draw_manager.cpp engine.cpp ghost.cpp navigation.cpp occupant_list.cpp occupant.cpp pacman.cpp texture_manager.cpp wall.cpp ai.cpp portal.cpp clock.cpp points.cpp text_manager.cpp life_manager.cpp state_manager.cpp
SRCS = $(addprefix src/,$(SRCNAMES))

OBJNAMES = $(SRCNAMES:.cpp=.o)
OBJS = $(addprefix build/,$(OBJNAMES))

TARGET = pacman

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -I include -o $(TARGET) $(OBJS) $(LIBS)

build/main.o : main.cpp 
	g++ -I include -c main.cpp -o $@

build/%.o : src/%.cpp include/%.h
	g++ -I include -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
