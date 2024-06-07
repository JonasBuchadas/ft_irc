### OPERATING SYSTEM ###
OS=			$(shell uname -s)

### EXECUTABLE ###
NAME=		ircserv

### COMPILATION ###
CC=			c++
CFLAGS=		-Wall -Werror -Wextra -g -std=c++98 -fsanitize=address

### PATHS ###
INCL_PATH=	incl/
SRCS_PATH=	srcs/
OBJS_PATH=	objs/

### SOURCE FILES ###
SRC_NAME=	main.cpp
SRCS=		Server.cpp \
				User.cpp \
				UserManager.cpp \
				Message.cpp \
				Messenger.cpp \
				Channel.cpp \
				ChannelManager.cpp \
				Parser.cpp \
				ACommand.cpp \
				CommandFactory.cpp \
				commands/InvalidCommand.cpp \
				commands/UserCommand.cpp \
				commands/PassCommand.cpp \
				commands/NickCommand.cpp \
				commands/PrivCommand.cpp \
				commands/JoinCommand.cpp \
				commands/KickCommand.cpp \
				commands/PartCommand.cpp \
				commands/NamesCommand.cpp \
				commands/InviteCommand.cpp \
				commands/LogoutCommand.cpp \
				commands/TopicCommand.cpp \
				commands/ModeCommand.cpp
SRCS_NAME=	$(addprefix $(SRCS_PATH), $(SRC_NAME) $(SRCS))
### OBJECT FILES ###
OBJ_NAME=	$(SRC_NAME:.cpp=.o)
OBJS=		$(SRCS:.cpp=.o)
OBJS_NAME=	$(addprefix $(OBJS_PATH), $(OBJ_NAME) $(OBJS))

### INCLUDES ###
INC=	-I $(INCL_PATH)

### COLOURS ###
ifeq ($(OS), Linux)
	ECHO=	echo "
else
	ECHO=	echo "
endif
GREEN= $(addprefix $(ECHO), \033[1;32m)
RED= $(addprefix $(ECHO), \033[1;31m)
DEFAULT= \033[0m"

### IMPLICT RULES ###
%.o: %.cpp
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

### ACTIVE RULES ###
all: $(NAME) ## compiles binary with mandatory requirements

help:  ## show this help
	@echo "usage: make [target]"
	@echo ""
	@egrep "^(.+)\:\ .*##\ (.+)" ${MAKEFILE_LIST} | sed 's/:.*##/#/' | column -t -c 2 -s '#'

$(NAME): $(OBJS_PATH) $(OBJS_NAME)
	@$(CC) $(CFLAGS) $(OBJS_NAME) $(INC) -o $(NAME)
	@$(GREEN)$(NAME) Program created$(DEFAULT)

$(OBJS_PATH):
	@mkdir -p $@/commands

$(OBJS_BT_PATH):
	@mkdir -p $@

clean: ## removes object files
	@rm -rf $(OBJS_PATH)
	@$(RED)Object files removed$(DEFAULT)

fclean: clean ## removes object files and binary
	@rm -f $(NAME)
	@$(RED)$(NAME) Program removed$(DEFAULT)

re: fclean all ## recompiles binary

### PHONY RULE ###
.PHONY:	all help bonus clean fclean re
