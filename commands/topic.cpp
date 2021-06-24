/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:38:26 by gkott             #+#    #+#             */
/*   Updated: 2021/06/22 18:44:38 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	topic( enviroment &env, const std::string &temp, user* i, std::stringstream &ss )
{
	std::string	new_topic;
	std::string	buff;
	if (temp.size() == 0)
	{
		return (serv_msg("TOPIC :Not enough parameters \n", 461, i));
	}
	ss >> new_topic;
	if (new_topic.size() == 0)
	{
		if (env.topics[temp].size() == 0)
		{
			return (serv_msg(temp + " :No topic is set.\n", 331, i));
		}
		return (serv_msg(temp + " :" + env.topics[temp] + "\n", 332, i));
	}
	if (new_topic[0] == ':')
		new_topic.erase(new_topic.begin());
	
	while (ss >> buff)
	{
		new_topic = new_topic + " " + buff;
	}
	env.topics[temp] = new_topic;
	send_to_channel(env, temp, (*i).sign_msg(" TOPIC " + temp + " :" + new_topic + "\n"));
}