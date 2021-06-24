/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:38:56 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	list( enviroment &env, const std::string &temp, user* i, std::stringstream & )
{
	std::stringstream msg;
	serv_msg("Channel :Users  Name\n", 321, i);
	if (temp.size() > 0)
	{
		msg << temp << " " << env.channels[temp].size() << " :"
		<< env.topics[temp] << "\n";
		serv_msg(msg.str(), 322, i);
	}
	else
	{
		CHANNELS_MAP::iterator it = env.channels.begin();
		while (it != env.channels.end())
		{
			msg.str(std::string());
			msg << (*it).first << " " << (*it).second.size() << " :"
			<< env.topics[(*it).first] << "\n";
			serv_msg(msg.str(), 322, i);
			++it;
		}
	}
	serv_msg(":End of /LIST\n", 323, i);
}