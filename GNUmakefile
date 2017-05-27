# GNUmakefile
#		(c) S.Suzuki 2017.1.16 ————— patch 2017.5.28


NAME    := GRAPPA

SUFFIX   = .cpp
SRCDIR   = ./src
INCLUDE  = -I./include
EXEDIR   = ./bin

OBJ      = .o

COMPILER = g++
CFLAGS   = -Wall -O2
FRAME    = -framework GLUT -framework OpenGL 

#! DO NOT EDIT !#
SOURCES  = $(wildcard $(SRCDIR)/*$(SUFFIX))
OBJECTS  = $(addsuffix $(OBJ),$(notdir $(basename $(SOURCES))))

# compile "NAME"
$(NAME):$(OBJECTS)
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -o $(EXEDIR)/$@ $(OBJECTS)

# macro for make
define MACRO
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -c $(word $1,$(SOURCES))
endef

.PHONY:$(OBJECTS)
$(word 1,$(OBJECTS)): 
	$(call MACRO,1)
$(word 2,$(OBJECTS)):
	$(call MACRO,2)
$(word 3,$(OBJECTS)):
	$(call MACRO,3)
$(word 4,$(OBJECTS)):
	$(call MACRO,4)
$(word 5,$(OBJECTS)):
	$(call MACRO,5)
$(word 6,$(OBJECTS)):
	$(call MACRO,6)
$(word 7,$(OBJECTS)):
	$(call MACRO,7)
$(word 8,$(OBJECTS)):
	$(call MACRO,8)
$(word 9,$(OBJECTS)):
	$(call MACRO,9)
$(word 10,$(OBJECTS)):
	$(call MACRO,10)
$(word 11,$(OBJECTS)):
	$(call MACRO,11)
$(word 12,$(OBJECTS)):
	$(call MACRO,12)
$(word 13,$(OBJECTS)):
	$(call MACRO,13)
$(word 14,$(OBJECTS)):
	$(call MACRO,14)
$(word 15,$(OBJECTS)):
	$(call MACRO,15)

# make clean
.PHONY: clean
clean: 
	$(RM) $(OBJECTS)
