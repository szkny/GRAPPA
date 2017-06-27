# GNUmakefile
#		(c) S.Suzuki 2017.1.16 ————— patch 2017.6.24

NAME     = GRAPPA

SUFFIX   = .cpp

SRC_DIR  = ./src
INC_DIR  = -I./include
LIB_DIR  = ./lib
EXE_DIR  = ./bin

COMPILER = g++
CFLAGS   = -Wall -O2 -mmacosx-version-min=10.8
FRAME    = -framework GLUT -framework OpenGL 

SOURCES  = $(wildcard $(SRC_DIR)/*$(SUFFIX))
OBJECTS  = $(notdir $(SOURCES:%$(SUFFIX)=%.o))
TARGETS  = $(basename $(OBJECTS))
LIBRARY  = $(NAME).a

all: $(LIBRARY) $(NAME)
	@echo "    —————————————————————————————————————————————  "
	@echo "         Complete to create $(NAME) into $(EXE_DIR)"
	@echo "            Let's try doing $(EXE_DIR)/$(NAME) !   "
	@echo "    —————————————————————————————————————————————  "

# make archives
$(LIBRARY): $(OBJECTS)
	@ar ru $(LIB_DIR)/$(LIBRARY) $(OBJECTS)
	@ranlib $(LIB_DIR)/$(LIBRARY)
	@$(RM) $(OBJECTS) 

# make execute file
$(NAME): $(LIB_DIR)/$(LIBRARY)
	$(COMPILER) $(INC_DIR) $(CFLAGS) $(FRAME) -o $(EXE_DIR)/$@ $^

# macro for make object file
define MACRO
$(1).o:
	$(COMPILER) $(INC_DIR) $(CFLAGS) $(FRAME) -c $(SRC_DIR)/$(1)$(SUFFIX)
endef

$(foreach var,$(TARGETS),$(eval $(call MACRO,$(var))))

#make clean
.PHONY: clean
clean: 
	$(RM) $(OBJECTS) $(LIB_DIR)/$(LIBRARY) $(EXE_DIR)/$(NAME)
