/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:39:01 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:36:09 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

std::string construct_msg( user* i, const std::string &sendto, std::stringstream &ss )
{
	std::string	result;
	std::string	temp;
	size_t		len;

	temp = ss.str();
	len = temp.find(' ');
	if (sendto.empty())
	{
		serv_msg(":No recipient given\n", 411, i);
		return ("");
	}
	while (isspace(temp[len])) {++len;}
	len += sendto.size();
	while (isspace(temp[len]) && len < temp.size()) {++len;}
	if (len == temp.size())
	{
		serv_msg(":No text to send\n", 412, i);
		return ("");
	}
	if (temp[0] == 'N')
		result = "NOTICE " + sendto + " ";
	else
		result = "PRIVMSG " + sendto + " ";
	if (temp[len] != ':')
	{
		result += ":";
	}
	result += temp.substr(len);
	return ((*i).sign_msg(result));
}

void	privmsg( enviroment &env, const std::string &sendto, user* i, std::stringstream &ss )
{
	std::string result = construct_msg(i, sendto, ss);

	if (result.empty())
		return ;
	if (sendto[0] != '#')
	{
		user* j = find_name(env.users, sendto);
		if (j != &(*env.users.end()))
		{
			(*j).msg_push(c_string(result));
			return ;
		}
		return (serv_msg(":No such nickname\n", 401, i));
	}
	if (env.channels.find(sendto) == env.channels.end())
	{
		return (serv_msg(":No such channel\n", 401, i));
	}
	for (CHANNEL::iterator j = env.channels[sendto].begin(); j != env.channels[sendto].end(); ++j)
	{
		if (*j != i)
		{
			(**j).msg_push(c_string(result));
		}
	}
}