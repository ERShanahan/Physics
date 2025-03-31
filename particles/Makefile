# Compiler
CXX = g++

# C++ Standard and include path for SFML headers.
CXXFLAGS = -std=c++17 -I"C:/msys64/mingw64/include" -DSFML_STATIC

# Linker flags: point to the SFML libraries and link against the necessary SFML modules.
LDFLAGS = -L"C:/msys64/mingw64/lib" \
          -lsfml-graphics-s -lsfml-window-s -lsfml-system-s \
          -lopengl32 -lfreetype -lwinmm -lgdi32 -lws2_32

# Name of the executable.
TARGET = sim

SRCS = main.cpp particle.cpp
OBJS = $(SRCS:.cpp=.o)

# Default rule: compile the executable.
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@	

# Clean up build files.
clean:
	rm -f *.o $(TARGET)
