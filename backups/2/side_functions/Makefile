# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:51:25 by gneto-co          #+#    #+#              #
#    Updated: 2024/03/26 13:56:49 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = side.a

PRINT_FUNCTIONS = $(addsuffix .c, \
ft_colors \
ft_atoi \
ft_printf/ft_printf \
)

SOURCES = \
$(PRINT_FUNCTIONS) \

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS) 
	@ar rcs $(NAME) $(OBJECTS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all