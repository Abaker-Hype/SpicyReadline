NAME:=libspicyrl.a
INC:=includes
SRCDIR:=srcs
OBJDIR:=objs
CC:=gcc
FLAGS:=-Wall -Werror -Wextra -I$(INC)

SRCS:=$(shell find $(SRCDIR) -type f -name '*.c')
OBJS:=$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o:**/%.c | $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

norm:
	@norminette $(SRCS) $(INC)

testing: $(NAME)
	@$(CC) test/*.c $(FLAGS) -L. -lsr -o test/test
	@test/test
	@rm test/test