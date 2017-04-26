# GNUmakefile
#		(c) S.Suzuki 2017.1.16

NAME    := main

SUFFIX   = .cpp
SRCDIR   = ./src
INCLUDE  = -I./include
EXEDIR   = ./bin

COMPILER = g++
CFLAGS   = -Wall -O2
FRAME    = -framework GLUT -framework OpenGL 

#! DO NOT EDIT !#
SOURCES  = $(if $(NAME),$(EMPTY),$(wildcard $(SRCDIR)/*$(SUFFIX)))
TARGETS  = $(addprefix $(EXEDIR)/,$(notdir $(basename $(SOURCES))))

# compile "NAME"
$(NAME):
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -o $(EXEDIR)/$@ $(SRCDIR)/$(NAME)$(SUFFIX)

# macro for make all
define MACRO
	$(COMPILER) $(INCLUDE) $(CFLAGS) $(FRAME) -o $@ $(word $1,$(SOURCES))
endef

# make all
.PHONY: all
all:$(TARGETS)
$(word 1,$(TARGETS)):
	$(call MACRO,1)
$(word 2,$(TARGETS)):
	$(call MACRO,2)
$(word 3,$(TARGETS)):
	$(call MACRO,3)
$(word 4,$(TARGETS)):
	$(call MACRO,4)
$(word 5,$(TARGETS)):
	$(call MACRO,5)
$(word 6,$(TARGETS)):
	$(call MACRO,6)
$(word 7,$(TARGETS)):
	$(call MACRO,7)
$(word 8,$(TARGETS)):
	$(call MACRO,8)
$(word 9,$(TARGETS)):
	$(call MACRO,9)
$(word 10,$(TARGETS)):
	$(call MACRO,10)
$(word 11,$(TARGETS)):
	$(call MACRO,11)
$(word 12,$(TARGETS)):
	$(call MACRO,12)
$(word 13,$(TARGETS)):
	$(call MACRO,13)
$(word 14,$(TARGETS)):
	$(call MACRO,14)
$(word 15,$(TARGETS)):
	$(call MACRO,15)

# make clean
.PHONY: clean
clean: 
	$(RM) $(wildcard $(EXEDIR)/*)
