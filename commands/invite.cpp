/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelah <alelah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:48:58 by gkott             #+#    #+#             */
/*   Updated: 2021/06/21 20:27:40 by alelah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	invite( enviroment &env, const std::string &temp, user* i, std::stringstream &ss )
{
	user* it = &(*env.users.begin());
	CHANNEL::iterator	find;
	std::string ch_name;
	if (temp.size() == 0)
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	it = find_name(env.users, temp);
	if (it == &(*env.users.end()))
	{
		return (serv_msg(":No such nick or channel\n", 401, i));
	}
	ss >> ch_name;
	if (ch_name.size() == 0)
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	if (!(*i).channels_find(ch_name))
	{
		return (serv_msg(":You are not member of this channel\n", 401, i));
	}
	for (find = env.channels[ch_name].begin(); find != env.channels[ch_name].end(); ++find)
	{
		if ((*find) == it)
			break;
	}
	if (find != env.channels[ch_name].end())
	{
		return (serv_msg(temp + " :is already on channel " + ch_name + ".\n", 443, i));
	}
	serv_msg(temp + " " + ch_name + ".\n", 341, i);
	(*it).msg_push(c_string((*i).sign_msg(" INVITE " + temp + " :" + ch_name + "\n")));
}