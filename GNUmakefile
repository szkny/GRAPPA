# GNUmakefile
#		(c) S.Suzuki 2017.1.16 ————— patch 2017.5.28

NAME     = GRAPPA

SUFFIX   = .cpp

SRCDIR   = ./src
INCLUDE  = -I./include
EXEDIR   = ./bin

COMPILER = g++
CFLAGS   = -Wall -O2
FRAME    = -framework GLUT -framework OpenGL 

SOURCES  = $(wildcard $(SRCDIR)/*$(SUFFIX))
OBJECTS  = $(notdir $(SOURCES:%$(SUFFIX)=%.o))
TARGETS  = $(basename $(OBJECTS))

# make execute file
$(NAME): $(OBJECTS)
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -o $(EXEDIR)/$@ $^

# macro for make object file
define MACRO
$(1).o:
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -c $(SRCDIR)/$(1)$(SUFFIX)
endef

$(foreach var,$(TARGETS),$(eval $(call MACRO,$(var))))

#make clean
.PHONY: clean
clean: 
	$(RM) $(OBJECTS) 
