NAME:=libsr.a
INC:=includes
SRCDIR:=srcs
OBJDIR:=objs
CC:=gcc
FLAGS:=-Wall -Wextra -I$(INC)

SRCS:=$(shell find $(SRCDIR) -type f -name '*.c')
OBJS:=$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(SRCS)
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

testing: $(NAME)
	@$(CC) test/*.c $(FLAGS) -L. -lsr -o test/test
	@test/test
	@rm test/test