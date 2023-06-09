# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 16:24:58 by ncotte            #+#    #+#              #
#    Updated: 2023/04/10 15:24:41 by shalimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		:=	cmd/kill.cpp		cmd/invite.cpp		cmd/pass.cpp \
					cmd/part.cpp		cmd/quit.cpp		cmd/topic.cpp \
					cmd/nick.cpp		cmd/ping.cpp		cmd/privmsg.cpp \
					cmd/user.cpp		cmd/who.cpp			cmd/pong.cpp \
                    cmd/kick.cpp		cmd/mode.cpp		cmd/oper.cpp \
                    cmd/join.cpp		cmd/cap.cpp			cmd/notice.cpp \
                    rpl/err_alreadyregistred.cpp	rpl/err_passwdmismatch.cpp \
                    rpl/err_erroneusnickname.cpp	rpl/err_umodeunknownflag.cpp \
                    rpl/err_needmoreparams.cpp		rpl/err_unknowncommand.cpp \
                    rpl/err_nicknameinuse.cpp		rpl/err_usersdontmatch.cpp \
                    rpl/err_nonicknamegiven.cpp		rpl/rpl_created.cpp \
                    rpl/err_nooperhost.cpp			rpl/rpl_myinfo.cpp \
                    rpl/err_noorigin.cpp			rpl/rpl_umodeis.cpp \
                    rpl/err_norecipient.cpp			rpl/rpl_welcome.cpp \
                    rpl/err_nosuchchannel.cpp		rpl/rpl_youreoper.cpp \
                    rpl/err_nosuchnick.cpp			rpl/rpl_yourhost.cpp \
                    rpl/err_notexttosend.cpp		rpl/rpl_mode.cpp \
                    rpl/err_badchanmask.cpp			rpl/err_badchannelkey.cpp \
                    rpl/err_bannedfromchan.cpp		rpl/err_notonchannel.cpp \
                    rpl/err_cannotsendtochan.cpp	rpl/rpl_privmsg.cpp \
					rpl/rpl_error.cpp				rpl/rpl_part.cpp \
					rpl/rpl_quit.cpp				rpl/rpl_join.cpp \
					rpl/rpl_topic.cpp				rpl/rpl_endofnames.cpp \
					rpl/rpl_namreply.cpp			rpl/rpl_channelmodeis.cpp \
					rpl/err_chanoprivsneeded.cpp	rpl/rpl_whoreply.cpp \
					rpl/rpl_endofwho.cpp			rpl/err_unknownmode.cpp \
					rpl/err_usernotinchannel.cpp	rpl/rpl_kick.cpp \
					rpl/rpl_notopic.cpp				rpl/err_useronchannel.cpp \
					rpl/rpl_inviting.cpp			rpl/rpl_channelmode.cpp \
					rpl/err_channelisfull.cpp		rpl/err_inviteonlychan.cpp \
					rpl/rpl_invite.cpp				rpl/err_noprivileges.cpp \
					rpl/rpl_kill.cpp				rpl/err_unknownerror.cpp \
					rpl/rpl_notice.cpp	\
					utils/split.cpp		utils/stringUtils.cpp	utils/printTime.cpp \
					utils/parsing.cpp	\
					Cmd.cpp				main.cpp			Server.cpp			Channel.cpp \
					User.cpp			Operator.cpp		Bot.cpp
SRCS_DIR		:=	./src/
SRCS			:=	$(addprefix $(SRCS_DIR),$(SRCS_FILES))

OBJS_FILES		:=	$(SRCS_FILES:.cpp=.o)
OBJS_DIR		:=	./bin/
OBJS_SUB_DIR	:= 	$(OBJS_DIR)utils $(OBJS_DIR)cmd $(OBJS_DIR)rpl
OBJS			:=	$(addprefix $(OBJS_DIR),$(OBJS_FILES))

INCS_FILES		:=	constants.h	cmd.h	Cmd.hpp		ft_irc.hpp 	Server.hpp	Channel.hpp \
					User.hpp		Operator.hpp	reply.h	Bot.hpp error.h
INCS_DIR		:=	./inc/
INCS		 	:=	$(addprefix $(INCS_DIR),$(INCS_FILES))

TMP				:=	.tmp.txt

CXX				:=	@c++-12
CXXFLAGS		:=	-g -Wall -Wextra -Werror -std=c++98 -pedantic -I $(INCS_DIR)
DEBUG			:=	-g3 -fsanitize=undefined
LOG_LEVEL		:= -D LOG_LEVEL=1
FULL_LOG_LEVEL	:= -D LOG_LEVEL=10
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

clean:			sclean
				@echo $(BOLD_BLUE)[CLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fclean:			sclean
				$(RM) $(NAME)
				$(RM) -r $(TEST).dSYM
				@echo $(BOLD_BLUE)[FCLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

re:				fclean all

leaks:			$(NAME)
				$(LEAKS) ./$(NAME) 6667 IRC4life

log:			CXXFLAGS += $(LOG_LEVEL)
log:			$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[LOG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

debug:			CXXFLAGS += $(DEBUG)
debug:			$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fdebug:			CXXFLAGS += $(FULL_LOG_LEVEL)
fdebug:			CXXFLAGS += $(DEBUG)
fdebug:			$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[FULL_DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)
				./$(NAME) 6667 IRC4life

run:			$(NAME)
				./$(NAME) 6667 IRC4life

.PHONY:			all sclean clean fclean re run leaks debug log fdebug
