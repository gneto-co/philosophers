# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/04/23 09:54:00 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
ORANGE = \033[31m\033[33m
GREEN = \033[32m
NC = \033[0m

#--------------------------------------------------------------------------------
#-----------------------------SIDE SOURCE FILES---------------------------------
#--------------------------------------------------------------------------------

SIDE_PATH = ./side_functions

SIDE = $(SIDE_PATH)/side.a

$(SIDE):
	@$(MAKE) -C $(SIDE_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#----------------------------PROJECT SOURCE FILES--------------------------------
#--------------------------------------------------------------------------------


PROJECT_PATH = ./$(NAME)_files

PROJECT = $(PROJECT_PATH)/$(NAME).a

$(PROJECT):
	@$(MAKE) -C $(PROJECT_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC = cc
OBJ = $(PROJECT) $(SIDE)
CFLAGS = -Wall -Wextra -Werror -g -I$(SIDE_PATH) -I$(PROJECT_PATH)

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------

.DEFAULT_GOAL := all

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@clear
	@echo "$(GREEN)\n---------- $(NAME) compiled and ready! ----------$(NC)"

clean:
	@rm -f $(NAME)
	@$(MAKE) -C $(SIDE_PATH) clean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) clean --no-print-directory
	@clear
	@echo "$(ORANGE)\n---------- program objects cleaned ----------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(SIDE_PATH) fclean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) fclean --no-print-directory
	@clear
	@echo "$(ORANGE)\n--------- program name and objects cleaned ----------$(NC)"
	
re: fclean all
