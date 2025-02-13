NAME_C			=	client

NAME_S			=	server

SRC_C			=	src_client/mt_client.c

SRC_S			=	src_server/mt_server.c

LIBFT_PATH		=	src_shared/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

FTPRINTF_PATH	=	src_shared/ft_printf
FTPRINTF		=	$(FTPRINTF_PATH)/libftprintf.a

CFLAGS			=	-Wall -Werror -Wextra

all:	hello $(NAME_C) $(NAME_S) info

hello:
	@echo "\e[48;2;100;0;100;1m Welcome to Minitalk Makefile \e[0m\n"

info: hello
	@git submodule update --init --recursive
	@echo "\n\e[48;2;70;70;70;1m Server usage : \e[0m\n"
	@echo "./server \n"
	@echo "\e[48;2;70;70;70;1m Client usage : \e[0m\n"
	@echo "./client <Server PID> <Message arg>\n"

lib: hello $(LIBFT) $(FTPRINTF)

$(NAME_C): ${LIBFT} ${FTPRINTF} ${SRC_C}
	@echo "\e[48;2;0;155;0;1m Compile Minitalk Client \e[0m\n"
	cc ${CFLAGS} ${SRC_C} ${LIBFT} ${FTPRINTF} -o $(NAME_C)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

$(NAME_S): ${LIBFT} ${FTPRINTF}
	@echo "\e[48;2;0;155;0;1m Compile Minitalk Server \e[0m\n"
	cc ${CFLAGS} ${SRC_S} ${LIBFT} ${FTPRINTF} -o $(NAME_S)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

$(LIBFT):
	@echo "\e[48;2;0;155;0;1m Make LIBFT \e[0m\n"
	@$(MAKE) --no-print-directory bonus -C $(LIBFT_PATH)
	@$(MAKE) --no-print-directory  clean  -C $(LIBFT_PATH)
	@echo "\e[48;2;0;0;155;1m Done for LIBFT \e[0m\n"

$(FTPRINTF):
	@echo "\e[48;2;0;155;0;1m Make FT_PRINTF \e[0m\n"
	@$(MAKE) --no-print-directory -C $(FTPRINTF_PATH)
	@$(MAKE) --no-print-directory clean -C $(FTPRINTF_PATH)
	@echo "\e[48;2;0;0;155;1m Done for FT_PRINTF \e[0m\n"
 
clean: hello
	@echo "\e[48;2;155;100;0;1m Clean dependencies \e[0m\n"
	$(RM) ${FTPRINTF} ${LIBFT}
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

fclean:	hello clean
	@echo "\e[48;2;155;100;0;1m Remove Minitalk \e[0m\n"
	$(RM) $(NAME_C) $(NAME_S)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

re:	hello fclean all

.PHONY: all clean fclean re lib info
