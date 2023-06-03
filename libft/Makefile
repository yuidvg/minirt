#Compiler Preferences
CC = cc
CFLAGS = -Wall -Werror -Wextra -I includes/

NAME = libft.a
SRCSDIR = srcs/
SRCS = char/determine.c char/operate.c\
		error/exit.c\
		list/create.c list/delete.c list/read.c list/update.c\
		memory/allocate.c memory/measure.c memory/operate.c\
		print/number.c print/string.c print/printf.c\
		string/copy.c string/measure.c string/modify.c\
		string/get_next_line.c string/ft_substr.c string/ft_split.c string/ft_itoa.c string/ft_atoi.c
OBJSDIR = objs/
OBJS = $(SRCS:%.c=$(OBJSDIR)%.o)

all: $(NAME)
$(NAME): $(OBJS)
	ar rcs $@ $^
$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all re clean
