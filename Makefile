RED=\033[31m
GREEN=\033[32m
BOLD=\033[1m
MAGENTA=\033[95m
RESET=\033[0m

define LOADING
    @sleep 0.4
    @echo -n "$(MAGENTA)."
    @sleep 0.15
    @echo -n "."
    @sleep 0.15
    @echo ".$(RESET)"
    @sleep 0.15
endef

DEPENDENCIES= -lreadline
INCLUDES= -Iincludes -Ilibft/headers -Itests/
CC= cc -Werror -Wextra -Wall -g $(INCLUDES)

MAIN_SRC= srcs/main.c

SRC= srcs/lexer/lexer.c \
	srcs/input_pipeline.c \
	srcs/lexer/lexer_destroy.c \
	srcs/lexer/tokenize.c \
	srcs/lexer/lexer_error_handler.c \
	srcs/parser/ast_builder.c \
	srcs/parser/get_node.c \
	srcs/parser/parser.c \
	srcs/parser/parser_destroy.c \
	srcs/parser/syntax_validator.c \
	srcs/parser/parser_error_handler.c \
	srcs/prompt/prompt_line.c \
	srcs/heredoc/collect_heredocs.c \
	srcs/heredoc/heredoc_fd_handler.c \
	srcs/expansion/expansion.c \
	srcs/expansion/expand_utils.c \
	srcs/expansion/expand_string.c \
	srcs/expansion/split_unprotected_spaces.c \
	srcs/execution/exec/exec.c \
	srcs/execution/exec/exec_builtin.c \
	srcs/execution/pipe/pipe.c \
	srcs/execution/redirect/redir.c \
	srcs/execution/exec/utils_exec.c \
	srcs/execution/exec/exec_error_handler.c \
	srcs/execution/pipe/utils_pipe.c \
	srcs/execution/redirect/utils_redir.c \
	srcs/builtins/builtin_utils.c \
	srcs/builtins/cd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/exit.c \
	srcs/builtins/export.c \
	srcs/builtins/pwd.c \
	srcs/builtins/unset.c \
	srcs/env/env_functions_two.c \
	srcs/env/env_functions.c \
	srcs/env/env_utils.c \
	srcs/signals/shell_signals.c \
	srcs/execution/executor.c \
	srcs/execution/exec/exec_pipe.c \
	srcs/execution/exec/utils_pipe_exec.c \

O_DIR= obj/
OBJ= $(SRC:%.c=$(O_DIR)%.o)
MAIN_OBJ= $(MAIN_SRC:%.c=$(O_DIR)%.o)

NAME= minishell

LIBFT= libft/libft.a
LIBPATH= libft/

TEST_BIN_DIR= tests/bin/
TEST_NAMES= lexer ast expansion
TEST_BINARIES= $(addprefix $(TEST_BIN_DIR), $(TEST_NAMES))

VALGRIND = valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes

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

$(TEST_BIN_DIR)expansion: tests/tester_expansion/tester_expansion.c $(LIBFT) $(OBJ)
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

leaks: all $(valgrind)
	@$(VALGRIND) ./$(NAME)
	
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

.PHONY: $(LIBFT) all test re fclean clean parse exec re_nolib fclean_nolib
#comentario