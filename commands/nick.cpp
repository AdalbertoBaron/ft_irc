/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:47:42 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:34:55 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	nick( enviroment &env, const std::string &temp, user* i, std::stringstream & )
{
	if (temp.empty())
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	if (find_name(env.users, temp) == &(*env.users.end()))
	{
		if (!(*i).get_user().empty())
		{
			if ((*i).get_login_lvl() == 1)
			{
				(*i).set_login_lvl(2);
				(*i).msg_push(c_string(":server 251 " + temp + " :Connected\n"));
				(*i).msg_push(c_string(":server 396 " + temp + " server :Connected\n"));
				#ifdef IRC_DEBUG_MODE
				std::cerr << (*i).get_user() << " loaded" << std::endl;
				#endif
			}
		}
		(*i).set_name(temp);
	}
	else
	{
		serv_msg(":Nickname already taken\n", 433, i);
	}
}