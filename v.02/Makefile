NAME = fdf

SRC = fdf.c\
	  fdf_utils_1.c\
	  fdf_utils_2.c\
	  fdf_utils_3.c\
	  fdf_utils_4.c\
	  fdf_hooks.c\
	  get_next_line.c\
	  get_next_line_utils.c\
	  ft_split.c\
	  ft_atoi.c
			 
OBJS = $(SRC:.c=.o)

CC = gcc -Wall -Werror -Wextra
SAN = -g3 -fsanitize=address
MLX = -L mlx -lmlx -framework OpenGL -framework Appkit

RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	make -C mlx/
	$(CC) $^ -o $@ $(MLX) -lm #$(SAN)


clean:
	$(RM) $(OBJS)
	make clean -C mlx/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean bonus fclean re
