NAME		= get_next_line
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs

SRC_FILES	= get_next_line	

SRC		 =	 $(addsuffix .c, $(SRC_FILES))
OBJ		 =	 $(addsuffix .o, $(SRC_FILES))

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)

fclean:		clean
			@$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re norm
