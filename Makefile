NAME = get_next_line.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)
OBJB = $(BONUS:.c=.o)

all: $(NAME)

bonus: $(OBJB)
		ar rc $(NAME) $(OBJB)
		ranlib $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
