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
NAME = minirt
SRCSDIR = srcs/
SRCS = main.c mlx.c\
		calculate/double.c \
		calculate/calculate.c\
		calculate/object.c\
		calculate/vector.c\
		calculate/vectors.c\
		calculate/sphere.c\
		calculate/color.c\
		parse/color.c\
		parse/double.c\
		parse/integer.c\
		parse/object.c\
		parse/scene.c\
		parse/vector.c
OBJSDIR = objs/
OBJS = $(SRCS:%.c=$(OBJSDIR)%.o)

#debug
NAME_DEBUG=minirt_debug
OBJSDIR_DEBUG=objs_debug/
CFLAGS_DEBUG = -g -Wall -Werror -Wextra -I includes/
LIBSFLAGS_DEBUG = -lm -L$(LIBFTDIR) -lft_debug -I$(MLXINCLUDE) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
OBJS_DEBUG = $(SRCS:%.c=$(OBJSDIR_DEBUG)%.o)
LIBFTNAME_DEBUG = $(LIBFTDIR)libft_debug.a

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
	rm -rf $(OBJS) $(OBJS_DEBUG)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

$(LIBFTNAME_DEBUG):
	make -C $(LIBFTDIR) debug
debug: $(NAME_DEBUG)
$(NAME_DEBUG): $(OBJS_DEBUG) $(LIBFTNAME_DEBUG)
	$(CC) $(CFLAGS_DEBUG) $(LIBSFLAGS_DEBUG) $^ -o $@
$(OBJSDIR_DEBUG)%.o: $(SRCSDIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

.PHONY: fclean all re clean debug