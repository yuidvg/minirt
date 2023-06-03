#Compiler Preferences
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS_LEAK = -g -fsanitize=leak

NAME = libft.a
SRCSDIR = srcs/char/ srcs/error/ srcs/list/ srcs/memory/ srcs/print/ srcs/string/
SRCS = char_determine.c char_operate.c\
		error_exit.c\
		list_create.c list_delete.c list_read.c list_update.c\
		mem_allocate.c mem_measure.c mem_operate.c\
		print_number.c print_string.c printf.c\
		string_copy.c string_measure.c string_modify.c get_next_line.c ft_substr.c ft_split.c ft_itoa.c ft_atoi.c
OBJSDIR = objs/
OBJS = $(SRCS:%.c=$(OBJSDIR)%.o)
INCLUDES = -I./

vpath %.c $(SRCSDIR)
vpath %.h includes/
vpath %.o $(OBJSDIR)

all: $(NAME)
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
$(OBJSDIR)%.o: %.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all re clean
