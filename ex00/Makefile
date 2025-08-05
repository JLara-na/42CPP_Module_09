# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 16:19:34 by jlara-na          #+#    #+#              #
#    Updated: 2025/08/03 15:55:20 by jlara-na         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------EXECUTABLE-----------

NAME			:=		btc
#-----------DIR PATHS------------

SRC_DIR			:=		src/
OBJ_DIR			:=		obj/
INC_DIR			:=		inc/

#-----------CMP PARAM------------

MAKEFLAGS		:=		--no-print-directory
CXX = c++
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98 -I inc

#-----------SHORT CUTS-----------

RM				:=		rm -f

#------------ANSI DEF------------

CLEAR			=		\033[H\033[J
DEF_COLOR		=		\033[m
RETURN			=		\033[1A
CLEAN_LINE		=		\033[2K
BLACK			=		\033[0;30m
BLACK_BL		=		\033[0;30;5m
GRAY			=		\033[0;90m
GRAY_BL			=		\033[0;90;5m
RED				=		\033[0;31m
RED_BL			=		\033[0;31;5m
RED_B			=		\033[0;91m
RED_BBL			=		\033[0;91;5m
GREEN			=		\033[0;32m
GREEN_BL		=		\033[0;32;5m
GREEN_B			=		\033[0;92m
GREEN_BBL		=		\033[0;92;5m
YELLOW			=		\033[0;33m
YELLOW_BL		=		\033[0;33;5m
YELLOW_B		=		\033[0;93m
YELLOW_BBL		=		\033[0;93;5m
BLUE			=		\033[0;34m
BLUE_BL			=		\033[0;34;5m
BLUE_B			=		\033[0;94m
BLUE_BBL		=		\033[0;94;5m
MAGENTA			=		\033[0;35m
MAGENTA_BL		=		\033[0;35;5m
MAGENTA_B		=		\033[0;95m
MAGENTA_BBL		=		\033[0;95;5m
CYAN			=		\033[0;36m
CYAN_BL			=		\033[0;36;5m
CYAN_B			=		\033[0;96m
CYAN_BBL		=		\033[0;96;5m
WHITE			=		\033[0;37m
WHITE_BL		=		\033[0;37;5m
WHITE_B			=		\033[0;97m
WHITE_BBL		=		\033[0;97;5m
CUSTOM_1		=		\033[38:5:177m
CUSTOM_2		=		\033[38:5:208m
CUSTOM_3		=		\033[38:5:112m
CUSTOM_4		=		\033[38:5:101m

#---------SRC OBJ DEP INC---------
SRC_FILES		=		main					\
						BitcoinExchange					\


SRC 			= 		$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_FILES)))
OBJ 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS			= 		$(addprefix $(INCLUDE), $(addsuffix .hpp, $(INC_FILES)))

#----------CACHE------------------
OBJF			=		.cache_exists
#---------------------------------

all:
			@$(MAKE) $(NAME)

-include	${DEPS}
$(NAME):	$(OBJ)
			@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
			@echo "$(CLEAN_LINE)$(CUSTOM_4)FLAGS USED	$(CUSTOM_1)$(CXX)$(CXXFLAGS)$(DEF_COLOR)"
			@echo "$(CLEAN_LINE)$(CUSTOM_4)EX00		$(GREEN)✔ COMPILED CORRECTLY$(DEF_COLOR)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCS) | $(OBJF)
			@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(CUSTOM_4)OBJ FILES	$(GREEN)✔ CLEANED$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CUSTOM_4)EXECUTABLE	$(GREEN)✔ CLEANED$(DEF_COLOR)"


re:			fclean
			@$(MAKE)

PHONY: all clean fclean re