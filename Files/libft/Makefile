# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 09:42:12 by joseferr          #+#    #+#              #
#    Updated: 2024/06/27 19:57:29 by joseferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME = libft.a

# Shell and printf
SHELL =		/bin/bash
UNAME =		$(shell uname -s)
PRINTF =	printf

# Compiler and flags
CC =		gcc -MD
CFLAGS =	-Wall -Wextra -Werror
AR =		ar rcs
RM =		rm -f

# Directories
SRC_DIRS =	checkers mem nbr put str lst gnl ftprintf
OBJ_DIR =	obj
BIN_DIR =	bin

# Colors
RED =		\033[0;31m
GREEN =		\033[0;32m
YELLOW =	\033[0;33m
BLUE =		\033[0;34m
PURPLE =	\033[0;35m
CYAN =		\033[0;36m
WHITE =		\033[0;37m
MAGENTA =	\033[0;35m
RESET =		\033[0m

# Source files
SRCS_CHECKERS =	checkers/ft_isalpha.c \
				checkers/ft_isdigit.c \
				checkers/ft_isalnum.c \
				checkers/ft_isascii.c \
				checkers/ft_isprint.c

SRCS_MEM =		mem/ft_memset.c \
				mem/ft_bzero.c \
				mem/ft_memcpy.c \
				mem/ft_memmove.c \
				mem/ft_memchr.c \
				mem/ft_memcmp.c \
				mem/ft_calloc.c

SRCS_NBR =		nbr/ft_atoi.c \
				nbr/ft_atol.c \
				nbr/ft_itoa.c

SRCS_PUT =		put/ft_putchar_fd.c \
				put/ft_putstr_fd.c \
				put/ft_putendl_fd.c \
				put/ft_putnbr_fd.c

SRCS_STR =		str/ft_strlen.c \
				str/ft_strlcpy.c \
				str/ft_strlcat.c \
				str/ft_toupper.c \
				str/ft_tolower.c \
				str/ft_strchr.c \
				str/ft_strrchr.c \
				str/ft_strncmp.c \
				str/ft_strnstr.c \
				str/ft_strdup.c \
				str/ft_substr.c \
				str/ft_strjoin.c \
				str/ft_strtrim.c \
				str/ft_split.c \
				str/ft_strmapi.c \
				str/ft_striteri.c \
				str/ft_strcmp.c

SRCS_LST =		lst/ft_lstadd_back.c \
				lst/ft_lstadd_front.c \
				lst/ft_lstdelone.c \
				lst/ft_lstlast.c \
				lst/ft_lstnew.c \
				lst/ft_lstsize.c \
				lst/ft_lstclear.c \
				lst/ft_lstiter.c \
				lst/ft_lstmap.c

SRCS_GNL =		gnl/get_next_line_bonus.c

SRCS_FTPRINTF =	ftprintf/ft_printf.c

# Objects
OBJS_CHECKERS =	$(SRCS_CHECKERS:%.c=$(OBJ_DIR)/%.o)
OBJS_MEM =		$(SRCS_MEM:%.c=$(OBJ_DIR)/%.o)
OBJS_NBR =		$(SRCS_NBR:%.c=$(OBJ_DIR)/%.o)
OBJS_PUT =		$(SRCS_PUT:%.c=$(OBJ_DIR)/%.o)
OBJS_STR =		$(SRCS_STR:%.c=$(OBJ_DIR)/%.o)
OBJS_LST =		$(SRCS_LST:%.c=$(OBJ_DIR)/%.o)
OBJS_GNL =		$(SRCS_GNL:%.c=$(OBJ_DIR)/%.o)
OBJS_FTPRINTF =	$(SRCS_FTPRINTF:%.c=$(OBJ_DIR)/%.o)

OBJS =			$(OBJS_CHECKERS) $(OBJS_MEM) $(OBJS_NBR) $(OBJS_PUT) $(OBJS_STR)
OBJS_BONUS =	$(OBJS_LST)

# Counts
SRC_COUNT_TOT :=		$(shell echo $(SRCS_CHECKERS) $(SRCS_MEM) $(SRCS_NBR) $(SRCS_PUT) $(SRCS_STR) | wc -w)
BONUS_COUNT_TOT :=		$(shell echo $(SRCS_LST) | wc -w)
GNL_COUNT_TOT :=		$(shell echo $(SRCS_GNL) | wc -w)
FTPRINTF_COUNT_TOT :=	$(shell echo $(SRCS_FTPRINTF) | wc -w)
SRC_COUNT := 0
BONUS_COUNT := 0
GNL_COUNT := 0
FTPRINTF_COUNT := 0

# Colors by directory
define set_color
	$(if $(findstring checkers,$1),$(PURPLE),\
	$(if $(findstring mem,$1),$(CYAN),\
	$(if $(findstring nbr,$1),$(YELLOW),\
	$(if $(findstring put,$1),$(GREEN),\
	$(if $(findstring str,$1),$(BLUE),\
	$(if $(findstring lst,$1),$(MAGENTA),\
	$(if $(findstring gnl,$1),$(RED),\
	$(if $(findstring ftprintf,$1),$(YELLOW),$(RESET)))))))))
endef

# Targets
all: mandatory bonus gnl printf

mandatory: $(BIN_DIR)/$(NAME)
	@$(PRINTF) "\r$(GREEN)[ %d/%d (%d%%) ] 🚀 Mandatory files have been compiled successfully!$(RESET)\n" $(SRC_COUNT_TOT) $(SRC_COUNT_TOT) 100

bonus: $(OBJS_BONUS)
	@$(AR) $(BIN_DIR)/$(NAME) $^
	@$(PRINTF) "\r$(MAGENTA)[ %d/%d (%d%%) ] 🚀 Bonus files have been compiled successfully!$(RESET)\n" $(BONUS_COUNT_TOT) $(BONUS_COUNT_TOT) 100

gnl: $(OBJS_GNL)
	@$(AR) $(BIN_DIR)/$(NAME) $^
	@$(PRINTF) "\r$(RED)[ %d/%d (%d%%) ] 🚀 GNL files have been compiled successfully!$(RESET)\n" $(GNL_COUNT_TOT) $(GNL_COUNT_TOT) 100

printf: $(OBJS_FTPRINTF)
	@$(AR) $(BIN_DIR)/$(NAME) $^
	@$(PRINTF) "\r$(CYAN)[ %d/%d (%d%%) ] 🚀 FT_PRINTF files have been compiled successfully!$(RESET)\n" $(GNL_COUNT_TOT) $(GNL_COUNT_TOT) 100

$(BIN_DIR)/$(NAME): $(OBJS) | $(BIN_DIR)
	@$(AR) $@ $^


$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(if $(findstring lst,$<),$(eval BONUS_COUNT=$(shell echo $$(($(BONUS_COUNT)+1)))),\
	$(if $(findstring gnl,$<),$(eval GNL_COUNT=$(shell echo $$(($(GNL_COUNT)+1)))),\
	$(eval SRC_COUNT=$(shell echo $$(($(SRC_COUNT)+1))))))
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval COLOR=$(call set_color,$<))
	@$(if $(findstring lst,$<),\
		$(PRINTF) "\r$(MAGENTA)[ %d/%d (%d%%) ] $(COLOR)Compiling $<$(RESET)..." $(BONUS_COUNT) $(BONUS_COUNT_TOT) $$(($(BONUS_COUNT)*100/$(BONUS_COUNT_TOT))),\
	$(if $(findstring gnl,$<),\
		$(PRINTF) "\r$(RED)[ %d/%d (%d%%) ] $(COLOR)Compiling $<$(RESET)..." $(GNL_COUNT) $(GNL_COUNT_TOT) $$(($(GNL_COUNT)*100/$(GNL_COUNT_TOT))),\
	$(if $(findstring ftprintf,$<),\
		$(PRINTF) "\r$(YELLOW)[ %d/%d (%d%%) ] $(COLOR)Compiling $<$(RESET)..." $(FTPRINTF_COUNT) $(FTPRINTF_COUNT_TOT) $$(($(FTPRINTF_COUNT)*100/$(FTPRINTF_COUNT_TOT))),\
		$(PRINTF) "\r$(GREEN)[ %d/%d (%d%%) ] $(COLOR)Compiling $<$(RESET)..." $(SRC_COUNT) $(SRC_COUNT_TOT) $$(($(SRC_COUNT)*100/$(SRC_COUNT_TOT))))))

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@$(PRINTF) "$(CYAN)🧹 Cleaning up object files in libft...$(RESET)\n"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "$(CYAN)🗑️ Removed $(NAME)$(RESET)\n"

norminette:
	@$(PRINTF) "$(RED)\nChecking NORM for libft...$(RESET)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRCS_CHECKERS) $(SRCS_MEM) $(SRCS_NBR) $(SRCS_PUT) $(SRCS_STR) $(SRCS_LST) $(SRCS_GNL) $(SRCS_FTPRINTF) libft.h

re: fclean all

.PHONY: all mandatory bonus gnl printf clean fclean norminette re
