/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:42:22 by gkott             #+#    #+#             */
/*   Updated: 2021/06/22 18:44:51 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	kill( enviroment &env, const std::string &temp, user* i, std::stringstream &ss )
{
	if ((*i).is_op())
	{
		if (temp.empty())
		{
			return (serv_msg(":No recipient given\n", 411, i));
		}
		user* victim = find_name(env.users, temp);
		if (victim != &(*env.users.end()))
		{
			return quit(env, temp, victim, ss);
		}
		return (serv_msg(":Nick not found\n", 481, i));
	}
	serv_msg(":Permission denied!\n", 481, i);
}