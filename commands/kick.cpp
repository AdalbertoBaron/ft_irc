/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:43:29 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:33:08 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	kick( enviroment &env, const std::string &temp, user* i, std::stringstream &ss )
{
	if ((*i).is_op())
	{
		user* it;
		std::string name;
		ss >> name;
		if (temp.empty() || name.empty())
		{
			return (serv_msg(":No recipient given\n", 411, i));
		}
		it = find_name(env.users, name);
		if (it != &(*env.users.end()))
		{
			return (part(env, temp, it, ss));
		}
		serv_msg(":User not found\n", 481, i);
	}
	else
	{
		serv_msg(":Permission denied!\n", 481, i);
	}
}   