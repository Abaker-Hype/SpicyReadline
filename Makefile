#NAME/DIRS
NAME:=libspicyrl.a
INC:=./includes
SRCDIR:=./srcs
OBJDIR:=./objs
LIBDIR:=./liball

#FLAGS
CC:=gcc
FLAGS:=-Wall -Werror -Wextra -I$(INC)
LIB:=$(LIBDIR)/liball.a
LIBFLAGS:=-I$(LIBDIR)/includes

#SRCS/OBJS
SRCS:=$(shell find $(SRCDIR) -type f -name '*.c')
OBJS:=$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o:**/%.c | $(OBJDIR)
	@$(CC) $< $(FLAGS) $(LIBFLAGS) -c -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIB):
	@make -s -C $(LIBDIR)

clean:
	@rm -rf $(OBJDIR)
	@make clean -s -C $(LIBDIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBDIR)

re: fclean all

norm:
	@norminette $(SRCS) $(INC)
	@make norm -s -C $(LIBDIR)

testing: $(NAME)
	@$(CC) test/*.c -L. -lspicyrl $(FLAGS) $(LIBFLAGS) -o test/test
	@test/test
	@rm test/test