NAME:= minishell
CFLAGS:= #-Wall -Werror -Wextra

HEADER = includes/minishell.h
GREEN:= \033[0;32m
RED:=\033[0;31m 
BLUE=\033[0;34m
default_colour=\033[0m


SRC_FILES:=  main.c \
					analise.c \
					list_utils.c \
					token_utils.c \
					env_expand.c\
					init_AST.c\
					destroy_utils.c\
					destroy_all.c\
					tree_validation.c\
#					init_tree.c\

MAKE:= make -C
LIBFT_DIR:= includes/libft
LIBFT:= includes/libft/libft.a

OBJ_FILES:= $(patsubst %.c, %.o, $(SRC_FILES))

SRC_PATH:= src/
OBJ_PATH:= obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: ${NAME}

${COMP_LIB}:
		echo "${RED}DONE${default_colour}"
		${MAKE} ${LIBFT_DIR}

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
		${COMP_LIB}
		@mkdir -p ${OBJ_PATH}
		cc   ${CFLAGS}  -c $< -o $@

${NAME}:  ${OBJ} 
#		${MAKE} ${LIBFT_DIR}
		cc  -I. ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME} -lreadline
		@echo "${GREEN}executable file: ./${NAME}${default_colour}\n"
	
clean:
#		${MAKE} ${LIBFT_DIR} clean
		@rm -fr ${OBJ_PATH}
		@echo "${RED}object files and directory deleted:${default_colour}"

fclean: clean
#		${MAKE} ${LIBFT_DIR} fclean
		@rm -f ${NAME}
		@echo "${RED}executable deleted:$(default_colour)"
		@echo "${RED}deleted all:$(default_colour)\n"

re : fclean all

.PHONY: all re clean fclean normi
.SIELNT:


