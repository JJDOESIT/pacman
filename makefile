CC         :=       g++
CFLAGS     :=       -Iinclude -std=c++20
LIBS       :=       -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR     :=       src

SRCNAMES   :=       main.cpp board.cpp coin.cpp draw_manager.cpp engine.cpp ghost.cpp navigation.cpp occupant_list.cpp occupant.cpp pacman.cpp texture_manager.cpp wall.cpp ai.cpp portal.cpp
SRCS       :=       $(addprefix src/,$(SRCNAMES))

OBJDIR    :=     build
OBJNAMES  :=     $(SRCNAMES:.cpp=.o)
OBJS      :=     $(addprefix $(OBJDIR)/,$(OBJNAMES))

TARGET    :=     pacman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJDIR)/main.o : src/main.cpp 
	$(CC) $(CFLAGS) -c $<  -o $@

$(OBJDIR)/%.o : src/%.cpp include/%.h
	$(CC) $(CFLAGS) -c $<  -o $@


clean:
	$(RM) $(TARGET) $(OBJS)
