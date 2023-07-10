#Compiler Preferences
CC = cc
CFLAGS = -Wall -Werror -Wextra -I includes/

#Libft
LIBFTDIR = libft/
LIBFTNAME = $(LIBFTDIR)libft.a

#Libraries
LIBSFLAGS = -lm -L$(LIBFTDIR) -lft -I$(MLXINCLUDE) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
MLXDIR = /usr/local/lib/
MLXINCLUDE = /usr/local/include/

#Mandatory
NAME = miniRT
SRCSDIR = srcs/
SRCS = main.c mlx.c\
		calculate/double.c \
		calculate/calculate.c\
		calculate/cylinder.c\
		calculate/sphere.c\
		calculate/plane.c\
		calculate/vector.c\
		calculate/vectors.c\
		calculate/color.c\
		parse/check.c\
		parse/color.c\
		parse/double.c\
		parse/integer.c\
		parse/object.c\
		parse/scene.c\
		parse/vector.c\
		render/pixel.c\
		render/window.c
OBJSDIR = objs/
OBJS = $(SRCS:%.c=$(OBJSDIR)%.o)

all: $(NAME)
$(LIBFTNAME):
	make -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFTNAME)
	$(CC) $(CFLAGS) $(LIBSFLAGS) $^ -o $@
$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all re clean