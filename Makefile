# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 11:16:04 by lomasson          #+#    #+#              #
#    Updated: 2022/07/27 12:14:29 by lomasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==--------------------------------------==#
# *                                      * #
#             GLOBAL SETTINGS              #
# *                                      * #
#==--------------------------------------==#

# Executable specialities
NAME = minishell
LANG = c
DEFINES = 
TEST_ARGS = 

# Compilation options
COMPILER = default
FLAGS = -Wall -Werror -Wextra -g3 -I /usr/local/opt/readline/include -I ~/.brew/opt/readline/include
ifneq ($(OS), Windows_NT)
	DANGER = -fsanitize=address
endif
LIBRARIES =  -lreadline
LIBS_MAC = -L /usr/local/Cellar/readline/8.1.2/lib/  -L /usr/local/opt/readline/lib/  -L ~/.brew/opt/readline/lib 

# Messages to display
COMPILE_MSG = ƒ Compiling $@ ...
SUCCESS_MSG = √ The programm $(NAME) has been compiled successfully!
CLEANING_MSG = ƒ Cleaning files ...
CLEANOBJ_MSG = ø Objects has been cleared!

#==--------------------------------------==#
# *                                      * #
#             LISTING SOURCES              #
# *                                      * #
#==--------------------------------------==#

# External libft files
LIBFT_FILES = ft_isdigit ft_isalnum ft_isascii ft_isprint ft_isalpha \
		ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy \
		ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
		ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup \
		ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_putchar_fd \
		ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_striteri ft_strmapi \
		get_next_line ft_printf_utils ft_printf ft_strcmp
LIBFT_FOLDER = libft/
LIBFT = $(addprefix $(LIBFT_FOLDER), $(LIBFT_FILES))

# External pipex files
PIPEX_FILES = pipe_utils pipe
PIPEX_FOLDER = pipex/
PIPEX = $(addprefix $(PIPEX_FOLDER), $(PIPEX_FILES))

# Listing every source files
ALL = $(LIBFT) $(PIPEX) \
	arbre_binaire check_condition ft_split_commande ft_split_argument main verif_commande builtins exec_cmd builtins_part exec_cmd_utils
SUBFOLDER = 

# Adds the applicable extension and path to each files
SRC = $(addprefix $(SUBFOLDER), $(addsuffix .$(LANG), $(ALL)))
OBJ = $(SRC:.$(LANG)=.o)

#==--------------------------------------==#
# *                                      * #
#               QUICK MACROS               #
# *                                      * #
#==--------------------------------------==#

# Quick control
SILENT = > /dev/null 2>&1
NOERR = || true
STOP = && false

# Syntax colors
RED = \033[0;31m
GRN = \033[0;32m
YLW = \033[0;33m
BLU = \033[0;34m
NUL = \033[0m
END = \033[0m\n
BACK = \033[2K\r

# Compiler counter
CMP_TOTAL = $(shell awk -F' ' '{printf NF}' <<< "$(SRC)")
CMP_COUNT = 0

# If COMPILER is set to 'default'
ifeq ($(COMPILER), default)
	ifeq ($(LANG), c)
		COMPILER = gcc
	else ifeq ($(LANG), cpp)
		COMPILER = c++
	else
		COMPILER = 
	endif
endif

#==--------------------------------------==#
# *                                      * #
#              RULES - COMMON              #
# *                                      * #
#==--------------------------------------==#

# Main call upon 'make'
all: $(NAME)

# Clears and recompile the whole project
re: fclean all

# Compile and run the executable and clears
ifeq ($(NAME), test)
tester: all
else # Prevents override issue due to commonly choosen name
test: all
endif
	@./$(NAME) $(TEST_ARGS) $(NOERR)
	@make fclean

# Protection
.PHONY: all re clean fclean re

#==--------------------------------------==#
# *                                      * #
#             RULES - LINUX OS             #
# *                                      * #
#==--------------------------------------==#

# Checks if its NOT Windows
ifneq ($(OS), Windows_NT)

# Compile the sources into object files
.$(LANG).o:
	@printf "$(BACK)$(YLW)[$(CMP_COUNT) / $(CMP_TOTAL)] $(COMPILE_MSG)$(NUL)"
	@$(COMPILER) $(FLAGS) -o $@ -c $<
	@$(eval CMP_COUNT = $(shell expr $(CMP_COUNT) + 1))

# Compile the objects and dependencies into an executable
$(NAME): $(OBJ)
	@printf "$(BACK)$(YLW)[Finalizing..] $(COMPILE_MSG)$(NUL)"
	@$(COMPILER) $(LIBS_MAC) $(LIBRARIES) $(DANGER) -o $(NAME) $(OBJ)
	@printf "$(BACK)$(GRN)$(SUCCESS_MSG)$(END)"

# Clears all objects files
clean:
	@printf "$(BACK)$(YLW)$(CLEANING_MSG)$(NUL)"
	@rm -f $(OBJ)
	@printf "$(BACK)$(RED)$(CLEANOBJ_MSG)$(END)"

# Clears all objects files, INCLUDING the executable
fclean: clean
	@rm -f $(NAME)

#==--------------------------------------==#
# *                                      * #
#            RULES - WINDOWS OS            #
# *                                      * #
#==--------------------------------------==#

# In case its running under Windows
else

# Compile the sources into object files
.$(LANG).o:
	@echo $(COMPILE_MSG)
	@$(COMPILER) $(FLAGS) -o $@ -c $<
	@$(eval CMP_COUNT = $(shell expr $(CMP_COUNT) + 1))

# Compile the objects and dependencies into an executable
$(NAME): $(OBJ)
	@echo $(COMPILE_MSG)
	@$(COMPILER) $(LIBRARIES) $(DANGER) -o $(NAME) $(OBJ) $(MLX) 
	@echo $(SUCCESS_MSG)

# Clears all objects files
clean:
	@echo $(CLEANING_MSG)
	@del /F /Q $(subst /,\,$(OBJ))
	@echo $(CLEANOBJ_MSG)

# Clears all objects files, INCLUDING the executable
fclean: clean
	@del /F /Q $(addsuffix .exe, $(subst /,\,$(NAME)))

endif

# Personal free to use template
# BY Rosie~
