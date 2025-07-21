# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djuarez <djuarez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 16:09:51 by djuarez           #+#    #+#              #
#    Updated: 2025/07/21 19:54:57 by djuarez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBS = -lreadline

SRC = main.c \
		src/lexer/tokenizer.c \
		src/lexer/lexer_utils.c \
		src/lexer/tokenizer_utils.c \
		src/lexer/token_lexer_utils.c \
		src/lexer/tokenizer_utils_2.c \
		src/lexer/lexer_utils_3.c \
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/parser_utils2.c \
		src/executor/executor.c \
		src/executor/executor_utils.c \
		src/executor/env_utils.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS) $(INCLUDES)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	
re: fclean all

.PHONY: all clean fclean re