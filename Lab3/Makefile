CC      = g++
CFLAGS  = -Wall -g -std=c++0x
LDFLAGS = 

BUILDDIR = build
SOURCEDIR = src
HEADERDIR = include 

SOURCES 	= $(shell find $(SOURCEDIR) -name '*.cpp')
HEADERS 	= $(shell find $(HEADERDIR) -name '*.h *.hpp')
OBJECTS 	= $(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
MODULES 	= $(shell find $(SOURCEDIR) -type d)
MODULESDIRS	= $(patsubst $(SOURCEDIR)%, $(BUILDDIR)%, $(MODULES))

EXECUTABLE = $(BUILDDIR)/Lab3

#==============================================================================================
all: create_dirs $(EXECUTABLE)

# Required in order to build .o in those folders
create_dirs: 
	clear
	mkdir -p build $(MODULESDIRS)

# Linking of all the .o files
$(EXECUTABLE): $(BUILDDIR)/$(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -I $(HEADERDIR) $(OBJECTS) -o $(EXECUTABLE) 

#Building of all the .o files
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -I $(HEADERDIR) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(MODULESDIRS)
