CXX = icpx
CXXFLAGS = -fsycl  -O3 -g  $(shell sdl2-config --cflags)  $(shell pkg-config --libs SDL2_image)  -I include
LDFLAGS = -fsycl $(shell sdl2-config --libs)  $(shell pkg-config --libs SDL2_image)  -lm

SRCDIR = src
INCDIR = include
BINDIR = bin
IMGDIR = images

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))
TARGET = gameOfLife

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)  $(IMGDIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(IMGDIR):
	mkdir -p $(IMGDIR)

# Dependencies
$(BINDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/sdl_utils.hpp
$(BINDIR)/sdl_utils.o: $(SRCDIR)/sdl_utils.cpp $(INCDIR)/sdl_utils.hpp
$(BINDIR)/game_of_life.o: $(SRCDIR)/game_of_life.cpp $(INCDIR)/game_of_life.hpp

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BINDIR)
	rm -rf $(IMGDIR)

.PHONY: all clean
