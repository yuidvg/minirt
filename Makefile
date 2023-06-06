#Compiler Preferences
CC = cc
CFLAGS = -Wall -Werror -Wextra -I includes/
CFLAGS_DEBUG = -g

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
		utils/double.c \
		utils/calculate.c utils/color.c\
		utils/objects.c\
		utils/vector.c\
		utils/sphere.c

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

debug: $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(OBJS) -o $(NAME)



.PHONY: fclean all re clean
