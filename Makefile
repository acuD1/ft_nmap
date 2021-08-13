define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for ft_nmap                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By arsciand cempassi                           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#                                                      #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
endef

# Progress bar with on line output printing. This script get the maximum
# lines , then expr a compilation percentage.

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL		=	make
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T					:=	$(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
						-nrRf $(firstword $(MAKEFILE_LIST)) \
						ECHO="OutputPrintable" | grep -c "OutputPrintable")
N					:=	x
C					=	$(words $N)$(eval N := x $N)
V					=	"`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
ECHO				=	printf "\e[1A\r%s %s %s                                          \n" $V
endif

# Color

RESET_C				=	\033[m
B_C					=	\033[0;34m
Y_C					=	\033[0;33m
G_C					=	\033[0;32m
R_C					=	\033[0;31m
M_C					=	\033[0;35m
C_C					=	\033[0;36m
F_C					=	\033[35;5;108m

# Programms names

NAME				=	ft_nmap
LNAME				=	libft.a

# Build information that can be added the predefines buffer at compilation


BUILD_BRANCH		=	$$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)


# Dir/Files Path (Do not modify)

S_PATH				=	srcs/
H_PATH				+=	includes/
H_PATH				+=	libft/includes/
B_PATH				=	build/
O_PATH				=	build/objs/
L_PATH				=	libft/

###############################################################################
#                               Modifications                                 #
###############################################################################

# Add custom dir for .o

# Add previous custom dir with $(O_PATH){custom dir} to PATH varriable

PATHS				+=	$(B_PATH)
PATHS				+=	$(O_PATH)

# Files

SRC					+= $(S_PATH)main.c
SRC					+= $(S_PATH)memory.c
SRC					+= $(S_PATH)opts_args.c
SRC					+= $(S_PATH)display.c
SRC					+= $(S_PATH)errors.c
SRC					+= $(S_PATH)resolve.c
SRC 				+= $(S_PATH)init.c
SRC 				+= $(S_PATH)set_scan_type.c
SRC 				+= $(S_PATH)exec_nmap.c
SRC 				+= $(S_PATH)send_packets.c
SRC 				+= $(S_PATH)ports.c
SRC 				+= $(S_PATH)lexer_base.c
SRC 				+= $(S_PATH)lexer_checks.c
SRC 				+= $(S_PATH)tools.c

# DEV

SRC					+= $(S_PATH)dev.c

# Headers

HDR					+=	libft.h
HDR					+=	ft_nmap.h

# std

# STD					+=	gnu17


###############################################################################
#                                                                             #
###############################################################################

# Objects

OBJ					=	$(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
LIB					=	$(L_PATH)$(LNAME)
vpath %.h $(H_PATH)

# Variables

DEBUG				=
CFLAGS				=	-Wall -Wextra -Werror #-std=$(STD)
ifeq ($(DEBUG), g)
	CFLAGS			+=	-g
else ifeq ($(DEBUG), fsanitize)
	CFLAGS			+=	-fsanitize=address -g3
else ifeq ($(DEBUG), hard)
	CFLAGS			+=	-g3 -Weverything -fsanitize=address,undefined # -Wno-cast-qual -Wno-missing-noreturn -Wno-disabled-macro-expansion -Wno-reserved-id-macro
else ifeq ($(DEBUG), dev)
	CFLAGS			=
endif
CC					=	clang $(CFLAGS)
IFLAGS				+=	$(addprefix -I, $(H_PATH))
CMPLC				=	$(CC) -c $(IFLAGS)
CMPLO				=	$(CC) -o
BUILD				=	$(PATHS)
AR_RC				=	ar rc
RANLI				=	ranlib
RM_RF				=	/bin/rm -rf
MKDIR				=	mkdir -p
NORME				=	norminette
SLEEP				=	sleep 0.01
GCFIL				=	"- > Compiling	-"
RMSHW				=	"- - Removing	-"
MKSHW				=	"- + Creating	-"
GCSUC				=	echo "$(G_C)=====>     SUCCESS$(RESET_C)"
CLSUC				=	echo "$(R_C)=====>     DONE$(RESET_C)"
NORMD				=	echo "$(G_C)=====>     DONE$(RESET_C)"

.PHONY: all norme clean fclean re test

# Rules
make:
	echo "# **************************************************************************** #"
	echo "#                                                                              #"
	echo "#                                                         :::      ::::::::    #"
	echo "#    Makefile for ft_nmap                               :+:      :+:    :+:    #"
	echo "#                                                     +:+ +:+         +:+      #"
	echo "#    By arsciand cempassi                           +#+  +:+       +#+         #"
	echo "#                                                 +#+#+#+#+#+   +#+            #"
	echo "#                                                      #+#    #+#              #"
	echo "#                                                     ###   ########.fr        #"
	echo "#                                                                              #"
	echo "# **************************************************************************** #"
	$(MAKE) --no-print-directory all

all: libm $(BUILD) $(NAME)

# Compilation core

ifneq ("$(wildcard $(L_PATH)$(LNAME))","")
TEST				=	libft/libft.a
else
TEST				=
endif

$(NAME): $(OBJ) $(TEST)
	$(ECHO) $(GCFIL) $(NAME)
	$(CMPLO) $(NAME) $(OBJ) $(LIB)
	$(GCSUC)
	echo "---\nCFLAGS - =$(B_C) $(CFLAGS)$(RESET_C)\n---"
	echo "\n$(G_C)[$(BUILD_BRANCH)] $(RESET_C) $@ is ready !"

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	$(CMPLC) $< -o $@
	$(ECHO) $(GCFIL) $<

$(PATHS):
	$(MKDIR) $(PATHS)
	$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	$(NORMR)
	$(NORME) $(SRC) $(H_PATH)$(HNAME)
	$(NORMD)

clean: libco
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	$(CLSUC)

fclean: libc
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	$(RM_RF) $(NAME)
	$(ECHO) $(RMSHW) $(NAME)
	$(CLSUC)

test: all
	behave

# Libc rules

libm:
	make -C $(L_PATH)
	printf "\n"

libco:
	make clean -C $(L_PATH)

libc:
	make fclean -C $(L_PATH)

help:
	echo "Makefile for ft_ping"
	echo "usage : make [VERBOSE=1] [DEBUG=g|fsanitize|hard|dev] [all|clean|fclean|re|libm|libco|libc|help]"

re:
	$(MAKE) --no-print-directory fclean all

ifndef VERBOSE
.SILENT:
endif

endif
