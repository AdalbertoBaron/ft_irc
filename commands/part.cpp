/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:39:03 by gkott             #+#    #+#             */
/*   Updated: 2021/06/22 18:03:39 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	part( enviroment &env, const std::string &channel, user* i, std::stringstream & )
{
	std::string temp(channel);
	if (temp.empty())
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	if (temp[0] != '#')
		temp = "#" + temp;
	CHANNEL::iterator res = std::find(env.channels[temp].begin(), env.channels[temp].end(), i);
	if (res != env.channels[temp].end())
	{
		send_to_channel(env, temp, (*i).sign_msg("PART :" + temp + "\n"));
		env.channels[temp].erase(res);
		(*i).channels_delete(temp);
	}
	else
	{
		serv_msg(":You are not member of this chat\n", 481, i);
	}
}