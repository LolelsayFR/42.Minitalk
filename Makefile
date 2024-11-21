NAME_C			=	client

NAME_S			=	server

SRC_C			=	src_client/mt_client.c

SRC_S			=	src_server/mt_server.c

LIBFT_PATH		=	src_shared/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

FTPRINTF_PATH	=	src_shared/ft_printf
FTPRINTF		=	$(FTPRINTF_PATH)/libftprintf.a

CFLAGS			=	-Wall -Werror -Wextra

all:	$(NAME_C) $(NAME_S) 

lib: $(LIBFT) $(FTPRINTF)

$(NAME_C): ${LIBFT} ${FTPRINTF} ${SRC_C}
	cc ${CFLAGS} ${SRC_C} ${LIBFT} ${FTPRINTF} -o $(NAME_C)

$(NAME_S): ${LIBFT} ${FTPRINTF}
	cc ${CFLAGS} ${SRC_S} ${LIBFT} ${FTPRINTF} -o $(NAME_S)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) clean -C $(LIBFT_PATH)

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTF_PATH)
	$(MAKE) clean -C $(FTPRINTF_PATH)

clean:
	$(RM) ${FTPRINTF} ${LIBFT}

fclean:	clean
	$(RM) $(NAME_C) $(NAME_S)

re:	fclean all


.PHONY: all clean fclean re lib
