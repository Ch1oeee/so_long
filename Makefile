NAME = so_long
BONUS_NAME = so_long_bonus
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
MLX_FLAGS = -L./minilibx-linux -lmlx -lbsd -lXext -lX11 -lm
RM = rm -rf

GREEN = \033[38;5;114m
ROSE = \033[38;5;218m
BLUE = \033[38;5;153m
NC = \033[0m

LIBRARIES_DIR = ./Libraries/libft
LIBRARIES = $(LIBRARIES_DIR)/libft.a

SRCS =	srcs/parsing/parsing.c\
		srcs/parsing/parsing_map.c\
		srcs/parsing/init_map.c\
		srcs/game/game.c\
		srcs/game/draw_map.c\
		srcs/parsing/map_verify_paths.c\
		srcs/parsing/parsing_map_utils.c\

BONUS_SRCS =	srcs/bonus/bonus.c\
				srcs/bonus/parsing_bonus.c\

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(LIBRARIES) $(OBJS)
	@echo "$(ROSE)\e[1m┌─────$(NAME)────────────────────────────────────┐\e"
	@echo "││$(BLUE)	      Compiling $(NAME) 🌀		$(ROSE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBRARIES) $(MLX_FLAGS)
	@echo "$(RED)\e[1m┌─────$(NAME)────────────────────────────────────┐\e"
	@echo "││$(GREEN)	      \e[1mCompilation finished 🌱\e		$(ROSE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"

$(BONUS_NAME): $(LIBRARIES) $(BONUS_OBJS)
	@echo "$(ROSE)\e[1m┌─────$(BONUS_NAME)────────────────────────────────────┐\e"
	@echo "││$(BLUE)		Compiling $(BONUS_NAME) 🎯	$(ROSE)	 │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@$(CC) $(FLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBRARIES) $(MLX_FLAGS)
	@echo "$(RED)\e[1m┌─────$(BONUS_NAME)────────────────────────────────────┐\e"
	@echo "││$(GREEN)		\e[1mCompilation finished 🌟\e	$(ROSE)	 │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"

$(LIBRARIES):
	@$(MAKE) -C $(LIBRARIES_DIR) --no-print-directory

minilibx :
	@git clone "https://github.com/42Paris/minilibx-linux.git"
	cd minilibx-linux && make

.c.o:
	@cc $(FLAGS) -c -o $@ $<

all: $(NAME)

bonus: $(BONUS_NAME)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBRARIES_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBRARIES_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all bonus clean fclean re minilibx bonus