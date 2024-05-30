LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src

SRCNAMES = main.cpp board.cpp coin.cpp draw_manager.cpp engine.cpp ghost.cpp navigation.cpp occupant_list.cpp occupant.cpp pacman.cpp texture_manager.cpp wall.cpp ai.cpp portal.cpp clock.cpp points.cpp text_manager.cpp life_manager.cpp state_manager.cpp power.cpp speed_manager.cpp map_editor.cpp tile.cpp json.cpp config.cpp button.cpp buttons.cpp inputs.cpp input.cpp alert.cpp
SRCS = $(addprefix src/,$(SRCNAMES))

OBJNAMES = $(SRCNAMES:.cpp=.o)
DNAMES = $(SRCNAMES:.cpp=.d)
OBJS = $(addprefix build/,$(OBJNAMES))
DFILES = $(addprefix build/,$(DNAMES))

TARGET = pacman.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -I include -I lib/rapidjson/include -o $(TARGET) $(OBJS) $(LIBS)

-include $(DFILES)
build/main.o : main.cpp 
	g++ -I include -I lib/rapidjson/include -MMD -c main.cpp -o $@

-include $(DFILES)
build/%.o : src/%.cpp include/%.h
	g++ -I include -I lib/rapidjson/include -MMD -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS) $(DFILES)
