NAME = libft.a
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS =	ft_putstr_fd.c\
		ft_strdup.c\
		../gnl/get_next_line.c\
		../gnl/get_next_line_utils.c\


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.c.o:
	@cc $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re