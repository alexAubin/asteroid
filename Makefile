ObjSuf        = o
SrcSuf        = c

SDLCFLAGS    = $(shell sdl-config --cflags)
SDLLIBS      = $(shell sdl-config --libs) -lSDL_image -lSDL_ttf

DEFINES       = 

CXX           = g++
CXXFLAGS      = -O -Wall -fPIC $(DEFINES) -Wno-unused-result
CXXFLAGS      += $(SDLCFLAGS) -I./

LD            = g++ 
LDFLAGS       = -g -O -Wall -fPIC -Wl,--no-undefined 
LDFLAGS       += $(SDLLIBS) -lm

SOFLAGS       = -shared
LIBS          = 

# Uncomment this line if you want to use a script to parse & colorize gcc output
# (You can also export this variable from your bashrc)
#GCCPARSER     = 2>&1 | python ~/littleScripts/colorGcc.py

#------------------------------------------------------------------------------
SOURCES       = $(wildcard *.$(SrcSuf))
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
EXECUTABLES   = $(SOURCES:.$(SrcSuf)=)
#------------------------------------------------------------------------------
DEFAULT_TARGET = asteroide
#------------------------------------------------------------------------------

all: compile run 
	
compile: $(DEFAULT_TARGET)

run:
	./$(DEFAULT_TARGET)

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(EXECUTABLES)

#------------------------------------------------------------------------------

$(DEFAULT_TARGET): $(DEFAULT_TARGET).$(SrcSuf)
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIBS) $(GCCPARSER)

