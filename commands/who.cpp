/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:38:58 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	who( enviroment &env, const std::string &temp, user* i, std::stringstream & )
{
	CHANNEL::iterator it = env.channels[temp].begin();
	while (it != env.channels[temp].end())
	{
		serv_msg(temp + " " +
		(**it).get_user() + " " +
		(**it).get_ip() +
		" ft_irc.server " +
		(**it).get_name() +
		" H :0 " +
		(**it).get_real_name() +
		"\n", 352, i);
		++it;
	}
	serv_msg(temp + " :End of /WHO list.\n", 315, i);
}