/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:47:22 by ncotte            #+#    #+#             */
/*   Updated: 2023/04/10 15:23:27 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/* Return codes */

# define EXIT_SUCCESS			0
# define EXIT_ERROR				1
# define EXIT_ERROR_NEG			-1

/* Const */

# define READ_BUFFER_SIZE		513
# define KEVENT_BUFFER_SIZE		1024
# define NB_PARAMS				15
# define NB_CMD					18
# define SERVER_VERSION			"1.0.0"

/* Colors */

# define RESET_COLOR			"\033[0m"
# define BLACK					"\033[0m\033[30m"
# define RED					"\033[0m\033[31m"
# define GREEN					"\033[0m\033[32m"
# define YELLOW					"\033[0m\033[33m"
# define BLUE					"\033[0m\033[34m"
# define MAGENTA				"\033[0m\033[35m"
# define CYAN					"\033[0m\033[36m"
# define WHITE					"\033[0m\033[37m"
# define BOLD_BLACK				"\033[1m\033[30m"
# define BOLD_RED				"\033[1m\033[31m"
# define BOLD_GREEN				"\033[1m\033[32m"
# define BOLD_YELLOW			"\033[1m\033[33m"
# define BOLD_BLUE				"\033[1m\033[34m"
# define BOLD_MAGENTA			"\033[1m\033[35m"
# define BOLD_CYAN				"\033[1m\033[36m"
# define BOLD_WHITE				"\033[1m\033[37m"

/* Replies */

# define RPL_WELCOME			"001"
# define RPL_YOURHOST			"002"
# define RPL_CREATED			"003"
# define RPL_MYINFO				"004"
# define RPL_BOUNCE				"005"
# define RPL_USERHOST			"302"
# define RPL_ISON				"303"
# define RPL_AWAY				"301"
# define RPL_UNAWAY				"305"
# define RPL_NOWAWAY			"306"
# define RPL_WHOISUSER			"311"
# define RPL_WHOISSERVER		"312"
# define RPL_WHOISOPERATOR		"313"
# define RPL_WHOISIDLE			"317"
# define RPL_ENDOFWHOIS			"318"
# define RPL_WHOISCHANNELS		"319"
# define RPL_WHOWASUSER			"314"
# define RPL_ENDOFWHOWAS		"369"
# define RPL_LISTSTART			"321"
# define RPL_LIST				"322"
# define RPL_LISTEND			"323"
# define RPL_UNIQOPIS			"325"
# define RPL_CHANNELMODEIS		"324"
# define RPL_NOTOPIC			"331"
# define RPL_TOPIC				"332"
# define RPL_INVITING			"341"
# define RPL_SUMMONING			"342"
# define RPL_INVITELIST			"346"
# define RPL_ENDOFINVITELIST	"347"
# define RPL_EXCEPTLIST			"348"
# define RPL_ENDOFEXCEPTLIST	"349"
# define RPL_VERSION			"351"
# define RPL_WHOREPLY			"352"
# define RPL_ENDOFWHO			"315"
# define RPL_NAMREPLY			"353"
# define RPL_ENDOFNAMES			"366"
# define RPL_LINKS				"364"
# define RPL_ENDOFLINKS			"365"
# define RPL_BANLIST			"367"
# define RPL_ENDOFBANLIST		"368"
# define RPL_INFO				"371"
# define RPL_ENDOFINFO			"374"
# define RPL_MOTDSTART			"375"
# define RPL_MOTD				"372"
# define RPL_ENDOFMOTD			"376"
# define RPL_YOUREOPER			"381"
# define RPL_REHASHING			"382"
# define RPL_YOURESERVICE		"383"
# define RPL_TIME				"391"
# define RPL_USERSSTART			"392"
# define RPL_USERS				"393"
# define RPL_ENDOFUSERS			"394"
# define RPL_NOUSERS			"395"
# define RPL_TRACELINK			"200"
# define RPL_TRACECONNECTING	"201"
# define RPL_TRACEHANDSHAKE		"202"
# define RPL_TRACEUNKNOWN		"203"
# define RPL_TRACEOPERATOR		"204"
# define RPL_TRACEUSER			"205"
# define RPL_TRACESERVER		"206"
# define RPL_TRACESERVICE		"207"
# define RPL_TRACENEWTYPE		"208"
# define RPL_TRACECLASS			"209"
# define RPL_TRACERECONNECT		"210"
# define RPL_TRACELOG			"261"
# define RPL_TRACEEND			"262"
# define RPL_STATSLINKINFO		"211"
# define RPL_STATSCOMMANDS		"212"
# define RPL_ENDOFSTATS			"219"
# define RPL_STATSUPTIME		"242"
# define RPL_STATSOLINE			"243"
# define RPL_UMODEIS			"221"
# define RPL_SERVLIST			"234"
# define RPL_SERVLISTEND		"235"
# define RPL_LUSERCLIENT		"251"
# define RPL_LUSEROP			"252"
# define RPL_LUSERUNKNOWN		"253"
# define RPL_LUSERCHANNELS		"254"
# define RPL_LUSERME			"255"
# define RPL_ADMINME			"256"
# define RPL_ADMINLOC1			"257"
# define RPL_ADMINLOC2			"258"
# define RPL_ADMINEMAIL			"259"
# define RPL_TRYAGAIN			"263"

/* Errors */

# define ERR_UNKNOWNERROR		"400"
# define ERR_NOSUCHNICK			"401"
# define ERR_NOSUCHSERVER		"402"
# define ERR_NOSUCHCHANNEL		"403"
# define ERR_CANNOTSENDTOCHAN	"404"
# define ERR_TOOMANYCHANNELS	"405"
# define ERR_WASNOSUCHNICK		"406"
# define ERR_TOOMANYTARGETS		"407"
# define ERR_NOSUCHSERVICE		"408"
# define ERR_NOORIGIN			"409"
# define ERR_NORECIPIENT		"411"
# define ERR_NOTEXTTOSEND		"412"
# define ERR_NOTOPLEVEL			"413"
# define ERR_WILDTOPLEVEL		"414"
# define ERR_BADMASK			"415"
# define ERR_UNKNOWNCOMMAND		"421"
# define ERR_NOMOTD				"422"
# define ERR_NOADMININFO		"423"
# define ERR_FILEERROR			"424"
# define ERR_NONICKNAMEGIVEN	"431"
# define ERR_ERRONEUSNICKNAME	"432"
# define ERR_NICKNAMEINUSE		"433"
# define ERR_NICKCOLLISION		"436"
# define ERR_UNAVAILRESOURCE	"437"
# define ERR_USERNOTINCHANNEL	"441"
# define ERR_NOTONCHANNEL		"442"
# define ERR_USERONCHANNEL		"443"
# define ERR_NOLOGIN			"444"
# define ERR_SUMMONDISABLED		"445"
# define ERR_USERSDISABLED		"446"
# define ERR_NOTREGISTERED		"451"
# define ERR_NEEDMOREPARAMS		"461"
# define ERR_ALREADYREGISTRED	"462"
# define ERR_NOPERMFORHOST		"463"
# define ERR_PASSWDMISMATCH		"464"
# define ERR_YOUREBANNEDCREEP	"465"
# define ERR_YOUWILLBEBANNED	"466"
# define ERR_KEYSET				"467"
# define ERR_CHANNELISFULL		"471"
# define ERR_UNKNOWNMODE		"472"
# define ERR_INVITEONLYCHAN		"473"
# define ERR_BANNEDFROMCHAN		"474"
# define ERR_BADCHANNELKEY		"475"
# define ERR_BADCHANMASK		"476"
# define ERR_NOCHANMODES		"477"
# define ERR_BANLISTFULL		"478"
# define ERR_NOPRIVILEGES		"481"
# define ERR_CHANOPRIVSNEEDED	"482"
# define ERR_CANTKILLSERVER		"483"
# define ERR_RESTRICTED			"484"
# define ERR_UNIQOPPRIVSNEEDED	"485"
# define ERR_NOOPERHOST			"491"
# define ERR_UMODEUNKNOWNFLAG	"501"
# define ERR_USERSDONTMATCH		"502"

#endif
