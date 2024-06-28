# Makefile informations
NAME 		= cub3D
CC 			= clang
RM			= rm -f

# Compilation flags
CFLAGS 		= -gdwarf-4 -Wall -Wextra -Werror -O3
LIBFTFLAGS	= -L./lib/libft -lft -fPIE
MLXFLAGS	= ./lib/MLX42/build/libmlx42.a -I./MLX42/include -ldl -lglfw -pthread -lm

# Lib informations
LIBFTEXEC	= ./lib/libft/libft.a
LIBFTHEADERS= ./lib/libft/
MLX42EXEC	= ./lib/MLX42/build/libmlx42.a
MLX42HEADERS= ./lib/MLX42/include/

# Debug and bonus flags
DEBUG		= 0
BONUS		= 0

# Sources and objects
SRC			= $(wildcard src/*.c) $(wildcard src/parsing/*.c) $(wildcard src/game/*.c)
OBJ			= $(SRC:.c=.o)

# Makefile rules
all:
	@printf "\033[1;36m\nStarting Cub3d compilation\n\e[0m"
	@make -s LIBFT
	@make -s MLX42
	@make -s $(NAME)
	@if [ $(DEBUG) -eq 1 ]; then printf "\033[1;31m\n > 🚧DEBUG MODE🚧\n\e[0m"; fi
	@if [ $(BONUS) -eq 1 ]; then printf "\033[1;31m\n > 🌟BONUS MODE🌟\n\e[0m"; fi
	@printf "\033[1;36m\nDONE !\n\e[0m"

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFTFLAGS) $(MLXFLAGS)
	@printf "\033[1;92m >>> Cub3d compiled                                                     \033[0m"

%.o: %.c
	@printf "\033[0;33mCompilation de %-33.33s\r\e[0m" $@
	@if [ $(DEBUG) -eq 1 ]; then $(CC) $(CFLAGS) -I $(MLX42HEADERS) -c $< -o $@ -D DEBUG=1; \
	elif [ $(BONUS) -eq 1 ]; then $(CC) $(CFLAGS) -I $(MLX42HEADERS) -c $< -o $@ -D BONUS=1; \
	else $(CC) $(CFLAGS) -I $(MLX42HEADERS) -c $< -o $@; fi

LIBFT:
	@if [ ! -f $(LIBFTEXEC) ]; \
	then printf "\033[1;35m\n\t| Starting libft compilation\n\e[0m" \
	&& make -s -C ./lib/libft; fi

MLX42:
	@if [ ! -f $(MLX42EXEC) ]; \
	then printf "\033[1;35m\n\t| Starting MLX42 compilation\n\e[0m" \
	&& git clone --quiet https://github.com/codam-coding-college/MLX42.git ./lib/MLX42\
	&& cmake -S ./lib/MLX42 -B ./lib/MLX42/build > /dev/null \
	&& cmake --build ./lib/MLX42/build -j4 > /dev/null \
	&& make -s -C ./lib/MLX42/build > /dev/null \
	&& printf "\033[1;92m\t|  >>> MLX42 compiled                                       \n\n\033[0m"; fi

clean:
	@$(RM) $(OBJ)
	@make -s clean -C ./lib/libft
	@printf "\033[1;31m- Object files deleted\n\033[0m"

fclean: clean
	@$(RM) $(LIBFTEXEC)
	@printf "\033[1;31m- [LIBFT] Static lib deleted\n\033[0m"
	@$(RM) -r ./lib/MLX42
	@printf "\033[1;31m- [MLX42] Static lib deleted\n\033[0m"
	@$(RM) $(NAME)
	@printf "\033[1;31m- Executable file deleted\n\033[0m"

re: fclean all

test:
	@make -s re
	@make -s clean
	@clear
	@echo "\033[1;92mDONE !"

norminette:
	@clear
	@echo "Header files norm :\n"
	@norminette include/
	@echo "\nSrc files norm : \n"
	@norminette src/
	@echo "\nLib files norm (except MLX42) :\n"
	@norminette lib/DailyLib/
	@norminette lib/libft/

debug: fclean
	@make -s DEBUG=1 all

bonus: fclean
	@make -s BONUS=1 all

.PHONY: all clean fclean re test norminette debug bonus
