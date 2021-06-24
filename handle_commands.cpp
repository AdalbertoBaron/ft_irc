/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:51:41 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 17:43:36 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	mode( enviroment &, const std::string &temp, user* i, std::stringstream & )
{
	serv_msg(temp + " \n", 324, i);
}

void	cap( enviroment &, const std::string &, user* , std::stringstream & )
{
	return ;
}

void	ping( enviroment &, const std::string &temp, user* i, std::stringstream & )
{
	(*i).msg_push(c_string("PONG " + temp + "\n"));
}

void	handle_commands( enviroment &env, user* i, std::string str )
{
	std::stringstream ss;
	std::string command;
	std::string temp;
	std::map<std::string, void(*)(enviroment &, const std::string &, user*, std::stringstream &)>::iterator	func_it;

	ss << str;
	ss >> command;
	ss >> temp;

	func_it = env.handlers.find(command);
	if (func_it == env.handlers.end())
	{
		return (serv_msg(":List of avalible command: PRIVMSG, NICK, \
USER, JOIN, KICK, LIST, PART, INVITE, TOPIC, NAMES, OPER, KILL, DIE, QUIT\n", 481, i));
	}
	if ((*i).get_login_lvl() == 0 && command != "PASS" && command != "CAP" && command != "QUIT")
	{
		return (serv_msg("PASS :Use PASS <server_password>\n", 464, i));
	}
	if ((*i).get_login_lvl() < 2 && command != "USER" && command != "NICK" && command != "CAP" && command != "PASS" && command != "QUIT")
	{
		return (serv_msg("USER :You need to set NICK and USER\n", 451, i));
	}
	(*func_it).second(env, temp, i, ss);
}

void	multiline_fix(enviroment &env, user* i, std::string str )
{
	size_t		new_line;
	std::string	fixed;
	while ((new_line = str.find('\n')) < str.size())
	{
		fixed = (*i).get_buffer() + str.substr(0, new_line + 1);
		handle_commands(env, i, fixed);
		(*i).clear_buffer();
		str = str.substr(new_line + 1);
	}
	if (str.size() > 0)
	{
		(*i).push_buffer(str);
	}
}
