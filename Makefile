RED=\033[31m
GREEN=\033[32m
BOLD=\033[1m
MAGENTA=\033[95m
RESET=\033[0m

define LOADING
    @sleep 0.7
    @echo -n "$(MAGENTA)."
    @sleep 0.2
    @echo -n "."
    @sleep 0.2
    @echo ".$(RESET)"
    @sleep 0.2
endef

DEPENDENCIES= -lreadline
INCLUDES= -Iincludes -Iincludes/execution -Iincludes/parsing -Iincludes/tests -Ilibft/headers
CC= cc -Werror -Wextra -Wall $(INCLUDES)

MAIN_SRC= srcs/main.c

SRC= srcs/parsing/lexer/lexer.c \
	srcs/parsing/lexer/lexer_split.c

O_DIR= obj/
OBJ= $(SRC:%.c=$(O_DIR)%.o)
MAIN_OBJ= $(MAIN_SRC:%.c=$(O_DIR)%.o)

NAME= minishell

LIBFT= libft/libft.a
LIBPATH= libft/

TEST_BIN_DIR= tests/bin/
TEST_NAMES= lexer_split
TEST_BINARIES= $(addprefix $(TEST_BIN_DIR), $(TEST_NAMES))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@$(CC) $(OBJ) $(MAIN_OBJ) $(LIBFT) -o $(NAME)
	@echo -n "\033[32m\nSuccessfully Generated $(RESET)$(NAME) \n\n"

$(O_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(MAGENTA)Compiling$(RESET) $(notdir $<)"
	@sleep 0.0001
	@$(CC) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBPATH)

$(TEST_BIN_DIR)lexer_split: tests/tester_lexer/tester_lexer_split.c $(LIBFT) $(OBJ)
	@mkdir -p $(TEST_BIN_DIR)
	@echo "$(MAGENTA)Compiling test$(RESET) $(notdir $@)"
	@$(CC) $< $(OBJ) $(LIBFT) -o $@

clean:
	@echo "$(MAGENTA)Cleansing $(NAME) Objects"
	$(LOADING)
	@make --no-print-directory -C $(LIBPATH) clean
	@rm -rf $(O_DIR)
	@rm -rf $(TEST_BIN_DIR)

fclean:
	@make --no-print-directory -C $(LIBPATH) fclean
	@echo "$(MAGENTA)Cleansing $(NAME)"
	$(LOADING)
	@rm -rf $(O_DIR)
	@rm -f $(NAME)

re: fclean all

test: fclean
	@$(MAKE) --no-print-directory $(TEST_BINARIES)
	@echo "$(MAGENTA)$(BOLD)\nInitializing all unitary tests$(RESET)"
	$(LOADING)
	@echo -n
	@for bin in $(TEST_BINARIES); do \
		echo "$(BOLD)\n======= Running $$bin =======\n$(RESET)"; \
		valgrind -q ./$$bin; \
	done

.PHONY: $(LIBFT) test re fclean clean