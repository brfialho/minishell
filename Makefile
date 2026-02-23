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

ifeq ($(findstring parse, $(MAKECMDGOALS)), parse)
	MAIN_SRC = srcs/parsing/parsing_test_main.c
endif

ifeq ($(findstring exec, $(MAKECMDGOALS)), exec)
	MAIN_SRC = srcs/execution/execution_test_main.c
endif

SRC= srcs/parsing/lexer/lexer.c \
	srcs/parsing/lexer/lexer_destroy.c \
	srcs/parsing/lexer/tokenize.c \
	srcs/parsing/lexer/trim_quoted_tokens.c \
	srcs/parsing/parser/ast_builder.c \
	srcs/parsing/parser/get_node.c \
	srcs/parsing/parser/parser.c \
	srcs/parsing/parser/parser_destroy.c \
	srcs/parsing/parsing.c \
	srcs/execution/exec/exec.c \
	srcs/execution/exec/exec_builtin_parent.c \
	srcs/execution/pipeline/pipeline.c \
	srcs/prompt/prompt_line.c \
	srcs/execution/redirect/redir.c \
	srcs/execution/exec/utils_exec.c \
	srcs/execution/pipeline/utils_pipeline.c \
	srcs/execution/redirect/utils_redir.c \
	srcs/execution/builtins/builtin_functions_two.c \
	srcs/execution/builtins/builtin_functions.c \
	srcs/execution/builtins/builtin.c \
	srcs/execution/builtins/env_functions_two.c \
	srcs/execution/builtins/env_functions.c \
	srcs/execution/handler/handler_basic.c \
	srcs/signals/set_signals.c \
	srcs/execution/executor.c

O_DIR= obj/
OBJ= $(SRC:%.c=$(O_DIR)%.o)
MAIN_OBJ= $(MAIN_SRC:%.c=$(O_DIR)%.o)

NAME= minishell

LIBFT= libft/libft.a
LIBPATH= libft/

TEST_BIN_DIR= tests/bin/
TEST_NAMES= lexer ast
TEST_BINARIES= $(addprefix $(TEST_BIN_DIR), $(TEST_NAMES))

parse: re_nolib

exec: re_nolib
#	@rm -rf $(O_DIR)
#	@rm -f $(NAME)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@$(CC) $(OBJ) $(MAIN_OBJ) $(LIBFT) $(DEPENDENCIES) -o $(NAME)
	@echo -n "\033[32m\nSuccessfully Generated $(RESET)$(NAME) \n\n"

$(O_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(MAGENTA)Compiling$(RESET) $(notdir $<)"
	@sleep 0.0001
	@$(CC) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBPATH)

$(TEST_BIN_DIR)lexer: tests/tester_lexer/tester_lexer.c $(LIBFT) $(OBJ)
	@mkdir -p $(TEST_BIN_DIR)
	@echo "$(MAGENTA)Compiling test$(RESET) $(notdir $@)"
	@$(CC) $< $(OBJ) $(LIBFT) $(DEPENDENCIES) -o $@

$(TEST_BIN_DIR)ast: tests/tester_ast/tester_ast.c $(LIBFT) $(OBJ)
	@mkdir -p $(TEST_BIN_DIR)
	@echo "$(MAGENTA)Compiling test$(RESET) $(notdir $@)"
	@$(CC) $< $(OBJ) $(LIBFT) $(DEPENDENCIES) -o $@

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

clean_nolib:
	@echo "$(MAGENTA)Cleansing $(NAME) Objects"
	$(LOADING)
	@rm -rf $(O_DIR)
	@rm -rf $(TEST_BIN_DIR)

fclean_nolib:
	@echo "$(MAGENTA)Cleansing $(NAME)"
	$(LOADING)
	@rm -rf $(O_DIR)
	@rm -f $(NAME)

re_nolib: fclean_nolib all

test: fclean_nolib
	@$(MAKE) --no-print-directory $(TEST_BINARIES)
	@echo "$(MAGENTA)$(BOLD)\nInitializing all unitary tests$(RESET)"
	$(LOADING)
	@echo -n
	@for bin in $(TEST_BINARIES); do \
		echo "$(BOLD)\n======= Running $$bin =======\n$(RESET)"; \
		valgrind -q ./$$bin; \
	done

.PHONY: $(LIBFT) test re fclean clean