/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:38:34 by gkott             #+#    #+#             */
/*   Updated: 2021/06/22 18:53:39 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	join( enviroment &env, const std::string &channel, user* i, std::stringstream &ss )
{
	std::string temp(channel);
	std::stringstream tmp;
	if (temp.empty())
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	if (temp[0] != '#')
		temp = "#" + temp;
	if (!((*i).channels_find(temp)))
	{
		(*i).channels_push(temp);
		env.channels[temp].push_back(i);
		send_to_channel(env, temp, (*i).sign_msg("JOIN :" + temp + "\n"));
		topic(env, temp, i, tmp);
		names(env, temp, i, ss);
	}
	else
	{
		serv_msg(":You already joined to this channel\n", 443, i);
	}
}