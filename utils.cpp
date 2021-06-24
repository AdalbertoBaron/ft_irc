/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:38:39 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 18:20:28 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

char	*c_string(const std::string &s)
{
	char *ret = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), ret);
	ret[s.size()] = '\0';
	return (ret);
}

void	destroy_it( user* it, enviroment &env)
{
	std::string msg = (*it).get_quit_msg();
	if (msg.size() == 0)
	{
	 	msg = ":Quit";
	}
	if (msg[0] != ':')
	{
		msg = ":" + msg;
	}
	std::list<std::string>::const_iterator channel = (*it).channels_list().begin();
	while (channel != (*it).channels_list().end())
	{
		send_to_channel(env, *channel, ":" + (*it).get_name() + "!" + (*it).get_user() + " QUIT " + msg + "\n");
		env.channels[*channel].erase(std::find(env.channels[*channel].begin(), env.channels[*channel].end(), it));
		(*it).channels_delete(*channel);
		++channel;
	}
	(*it).destroy();
}

void	serv_msg(const std::string &msg, int code, user* i)
{
	std::stringstream result;
	result << ":server " << code << ' ';
	result << (*i).get_name();
	result << ' ' << msg;
	(*i).msg_push(c_string(result.str()));
}

user* find_user( std::list<user> &users, const std::string &name )
{
	std::list<user>::iterator it;
	for (it = users.begin(); it != users.end(); ++it)
	{
		if ((*it).get_user() == name)
		{
			break ;
		}
	}
	return (&(*it));
}

user* find_name( std::list<user> &users, const std::string &name )
{
	std::list<user>::iterator it;
	for (it = users.begin(); it != users.end(); ++it)
	{
		if ((*it).get_name() == name)
		{
			break ;
		}
	}
	return (&(*it));
}

std::list<user>::iterator find_name_iterator( std::list<user> &users, const std::string &name )
{
	std::list<user>::iterator it;
	for (it = users.begin(); it != users.end(); ++it)
	{
		if ((*it).get_name() == name)
		{
			break ;
		}
	}
	return (it);
}

void	send_to_channel( enviroment &env, const std::string &temp, const std::string &msg )
{
	for (CHANNEL::iterator j = env.channels[temp].begin(); j != env.channels[temp].end(); ++j)
	{
		(**j).msg_push(c_string(msg));
	}
}

void	comands_init(enviroment &env)
{
	env.handlers["CAP"] = cap;
	env.handlers["PASS"] = pass;
	env.handlers["NICK"] = nick;
	env.handlers["USER"] = user_command;
	env.handlers["MODE"] = mode;
	env.handlers["WHO"] = who;
	env.handlers["INVITE"] = invite;
	env.handlers["NAMES"] = names;
	env.handlers["LIST"] = list;
	env.handlers["PRIVMSG"] = privmsg;
	env.handlers["NOTICE"] = privmsg;
	env.handlers["JOIN"] = join;
	env.handlers["KICK"] = kick;
	env.handlers["PART"] = part;
	env.handlers["OPER"] = oper;
	env.handlers["KILL"] = kill;
	env.handlers["DIE"] = die;
	env.handlers["TOPIC"] = topic;
	env.handlers["QUIT"] = quit;
}

void	stop( enviroment &env )
{
	while (!env.users.empty())
	{
		env.users.back().destroy();
		env.users.pop_back();
	}
	std::cout << "Good night <3" << std::endl;
	exit(0);
}