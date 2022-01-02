define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for libft_ft_nmap				            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 19:23:44 by arsciand          #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
endef

# Progress bar

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL	=	make
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T				:=	$(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
					-nrRf $(firstword $(MAKEFILE_LIST)) \
					ECHO="OutputPrintable" | grep -c "OutputPrintable")
N				:=	x
C				=	$(words $N)$(eval N := x $N)
V				=	"`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
ECHO			=	printf "\e[1A\r%s %s %s                                      \n" $V
endif

# Color

RESET_C			=	\033[m
B_C				=	\033[0;34m
Y_C				=	\033[0;33m
G_C				=	\033[0;32m
R_C				=	\033[0;31m
M_C				=	\033[0;35m
C_C				=	\033[0;36

# Programms names

NAME			=	libft.a

# Dir/Files Path

S_PATH			=	srcs/
H_PATH			=	includes/
B_PATH			=	build/
O_PATH			=	build/objs/
PATHS			+=	$(B_PATH)
PATHS			+=	$(O_PATH)

SRC += ft_getargslst.c
SRC += ft_lstadd.c
SRC += ft_lstaddback.c
SRC += ft_lstcmp.c
SRC += ft_lstdel.c
SRC += ft_lstdelfirst.c
SRC += ft_lstdelnext.c
SRC += ft_lstdelone.c
SRC += ft_lstfilter.c
SRC += ft_lstfind.c
SRC += ft_lstfold.c
SRC += ft_lstiter.c
SRC += ft_lstiter_ctx.c
SRC += ft_lstlen.c
SRC += ft_lstmap.c
SRC += ft_lstmerge.c
SRC += ft_lstmove_if.c
SRC += ft_lstnew.c
SRC += ft_lstremove_if.c
SRC += ft_lst_remove_self.c
SRC += ft_lstrev.c
SRC += ft_lstsplit_if.c
SRC += ft_lsttotab.c
SRC += ft_mergesort.c
SRC += ft_stckdestroy.c
SRC += ft_stckinit.c
SRC += ft_stckpop.c
SRC += ft_stckpopnode.c
SRC += ft_stckpush.c
SRC += ft_stckpushnode.c
SRC += ft_stcksize.c
SRC += ft_stcktop.c

SRC += ft_atoi.c
SRC += ft_isnumeric.c
SRC += ft_strbeginswith.c
SRC += ft_strcat.c
SRC += ft_strcheck.c
SRC += ft_strchr.c
SRC += ft_strclr.c
SRC += ft_strcmp.c
SRC += ft_strcpy.c
SRC += ft_strcspn.c
SRC += ft_strdel.c
SRC += ft_strdup.c
SRC += ft_strendswith.c
SRC += ft_strequ.c
SRC += ft_strinsert.c
SRC += ft_striter.c
SRC += ft_striteri.c
SRC += ft_strjoin.c
SRC += ft_strlcat.c
SRC += ft_strlen.c
SRC += ft_strlower.c
SRC += ft_strmap.c
SRC += ft_strmapi.c
SRC += ft_strncat.c
SRC += ft_strncmp.c
SRC += ft_strncpy.c
SRC += ft_strnequ.c
SRC += ft_strnew.c
SRC += ft_strnstr.c
SRC += ft_strrchr.c
SRC += ft_strrev.c
SRC += ft_strsplit.c
SRC += ft_strspn.c
SRC += ft_strstr.c
SRC += ft_strsub.c
SRC += ft_strtrim.c
SRC += ft_tabdel.c

SRC += ft_bzero.c
SRC += ft_memalloc.c
SRC += ft_memccpy.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_memcpy.c
SRC += ft_memdel.c
SRC += ft_memmove.c
SRC += ft_memset.c

SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isdigit.c
SRC += ft_isprint.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_getdelim.c
SRC += ft_tablen.c
SRC += ft_freetab.c

SRC += ft_get_opts_args.c

SRC += vct_add.c
SRC += vct_charat.c
SRC += vct_cut.c
SRC += vct_del.c
SRC += vct_delchar.c
SRC += vct_del_string.c
SRC += vct_dup.c
SRC += vct_dups.c
SRC += vct_getcopy.c
SRC += vct_getstring.c
SRC += vct_insert_char.c
SRC += vct_insert_string.c
SRC += vct_len.c
SRC += vct_ncat.c
SRC += vct_ncpy.c
SRC += vct_new.c
SRC += vct_pop.c
SRC += vct_push.c
SRC += vct_replace_char.c
SRC += vct_replace_string.c
SRC += vct_reset.c
SRC += vct_resize.c
SRC += vct_scale.c
SRC += vct_scat.c
SRC += vct_scpy.c
SRC += vct_set_scale.c
SRC += vct_shift_tool.c
SRC += vct_size.c
SRC += vct_sub.c

vpath %.c srcs
vpath %.c srcs/list
vpath %.c srcs/string
vpath %.c srcs/memory
vpath %.c srcs/other
vpath %.c srcs/vector
vpath %.h includes

# Objects and Headers

HDR				+=	libft.h
HDR				+=	list.h
HDR				+=	str.h
HDR				+=	memory.h
HDR				+=	other.h
HDR				+=	vector.h

# STD				+=	gnu17

OBJ				=	$(patsubst %.c, $(O_PATH)%.o, $(SRC))

# Variables

DEBUG			=
CFLAGS			=	-Wall -Wextra -Werror #-std=$(STD)
ifeq ($(DEBUG), g)
	CFLAGS		=	-g
else ifeq ($(DEBUG), fsanitize)
	CFLAGS		=	-fsanitize=address
else ifeq ($(DEBUG), hard)
	CFLAGS		+=	-g3 -Weverything -fsanitize=address,undefined #-Wno-cast-qual -Wno-missing-noreturn -Wno-disabled-macro-expansion -Wno-reserved-id-macro
else ifeq ($(DEBUG), dev)
	CFLAGS		=
endif
CC				=	clang $(CFLAGS)
COMPL			=	$(CC) -c -I$(H_PATH)
BUILD			=	$(PATHS)
AR_RC			=	ar rc
RANLI			=	ranlib
CFLAG			=	-Wall -Wextra -Werror -g
RM_RF			=	/bin/rm -rf
MKDIR			=	mkdir -p
NORME			=	norminette
SLEEP			=	sleep 0.01
GCFIL			=	"- > Compiling	-"
GCLAR			=	"- } Archiving	-"
RMSHW			=	"- - Removing	-"
MKSHW			=	"- + Creating	-"
GCRUN			=	echo ">\n$(G_C)----->     Compiling$(RESET_C)\n"
CLRUN			=	echo ">\n$(R_C)----->     Cleaning$(RESET_C)\n"
NORMR			=	echo ">\n$(Y_C)----->     Norminette$(RESET_C)\n"

.PHONY: all norme clean fclean re test

# Rules

make:
	$(MSG)
	$(MAKE) --no-print-directory all

all: $(BUILD) $(NAME)

$(NAME): $(OBJ)
	$(SLEEP)
	$(AR_RC) $(NAME) $^
	$(ECHO) $(GCLAR) $@
	$(RANLI) $(NAME)

$(OBJ): $(O_PATH)%.o: %.c $(HDR)
	$(COMPL) $< -o $@
	$(ECHO) $(GCFIL) $<

$(PATHS):
	$(SLEEP)
	$(GCRUN)
	$(MKDIR) $(PATHS)
	$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	$(NORMR)
	$(NORME) $(SRC) $(H_PATH)$(HNAME)
	$(NORMD)

clean:
	$(CLRUN)
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done

fclean:
	$(CLRUN)
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	$(RM_RF) $(NAME)
	$(ECHO) $(RMSHW) $(NAME)

re:
	$(MAKE) --no-print-directory fclean all

ifndef VERBOSE
.SILENT:
endif

endif
