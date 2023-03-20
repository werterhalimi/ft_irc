# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 16:24:58 by ncotte            #+#    #+#              #
#    Updated: 2023/03/15 19:11:51 by shalimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		:=	cmd/admin.cpp		cmd/info.cpp		cmd/kill.cpp		cmd/motd.cpp \
					cmd/part.cpp		cmd/quit.cpp		cmd/squery.cpp		cmd/topic.cpp \
					cmd/version.cpp		cmd/away.cpp		cmd/invite.cpp		cmd/links.cpp \
					cmd/names.cpp		cmd/pass.cpp		cmd/rehash.cpp		cmd/squit.cpp \
					cmd/trace.cpp		cmd/wallops.cpp		cmd/connect.cpp		cmd/ison.cpp \
					cmd/list.cpp		cmd/nick.cpp		cmd/ping.cpp		cmd/restart.cpp \
					cmd/stats.cpp		cmd/user.cpp		cmd/who.cpp			cmd/die.cpp \
					cmd/join.cpp		cmd/luser.cpp		cmd/notice.cpp		cmd/pong.cpp \
					cmd/service.cpp		cmd/summon.cpp		cmd/userhost.cpp	cmd/whois.cpp \
                    cmd/error.cpp		cmd/kick.cpp		cmd/mode.cpp		cmd/oper.cpp \
                    cmd/privmsg.cpp  	cmd/servlist.cpp	cmd/time.cpp		cmd/users.cpp \
                    cmd/whowas.cpp \
					Cmd.cpp				main.cpp			Server.cpp			Channel.cpp \
					User.cpp			utils/split.cpp		utils/stringUtils.cpp
SRCS_DIR		:=	./src/
SRCS			:=	$(addprefix $(SRCS_DIR),$(SRCS_FILES))

OBJS_FILES		:=	$(SRCS_FILES:.cpp=.o)
OBJS_DIR		:=	./bin/
OBJS_SUB_DIR	:= 	$(OBJS_DIR)utils $(OBJS_DIR)cmd
OBJS			:=	$(addprefix $(OBJS_DIR),$(OBJS_FILES))

INCS_FILES		:=	constants.h	cmd.h	Cmd.hpp	ft_irc.hpp Server.h Channel.h User.h
INCS_DIR		:=	./inc/
INCS		 	:=	$(addprefix $(INCS_DIR),$(INCS_FILES))

TMP				:=	.tmp.txt

CXX				:=	@c++-12
CXXFLAGS		:=	-g -Wall -Wextra -Werror -std=c++98 -pedantic -I $(INCS_DIR)
DEBUG			:=	-g3 -fsanitize=undefined
RM				:=	@rm -f
LEAKS			:=	@leaks -atExit --

NAME			:=	ircserv

RESET_COLOR		:=	"\033[0m"

BLACK			:=	"\033[0;30m"
RED				:=	"\033[0;31m"
GREEN			:=	"\033[0;32m"
YELLOW			:=	"\033[0;33m"
BLUE			:=	"\033[0;34m"
MAGENTA			:=	"\033[0;35m"
CYAN			:=	"\033[0;36m"
WHITE			:=	"\033[0;37m"

BOLD_BLACK		:=	"\033[1;30m"
BOLD_RED		:=	"\033[1;31m"
BOLD_GREEN		:=	"\033[1;32m"
BOLD_YELLOW		:=	"\033[1;33m"
BOLD_BLUE		:=	"\033[1;34m"
BOLD_MAGENTA	:=	"\033[1;35m"
BOLD_CYAN		:=	"\033[1;36m"
BOLD_WHITE		:=	"\033[1;37m"

all:			$(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp $(INCS)
				@mkdir -p $(OBJS_DIR) $(OBJS_SUB_DIR)
				$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

sclean:
				$(RM) $(OBJS)
				$(RM) -r $(OBJS_DIR)
#$(RM) -r $(OBJS_SUB_DIR) $(OBJS_DIR)

clean:			sclean
				@echo $(BOLD_BLUE)[CLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fclean:			sclean
				$(RM) $(NAME)
				$(RM) -r $(TEST).dSYM
				@echo $(BOLD_BLUE)[FCLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

re:				fclean all

leaks:			$(NAME)
				$(LEAKS) ./$(NAME) 6667 IRC4life

debug:			CFLAGS += $(DEBUG)
debug:			$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

run:			$(NAME)
				./$(NAME) 6667 IRC4life

.PHONY:			all sclean clean fclean re run leaks debug
