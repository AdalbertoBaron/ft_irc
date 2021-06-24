/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:42:06 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	die( enviroment &env, const std::string &, user* i, std::stringstream &)
{
	if ((*i).is_op())
	{
		stop(env);
	}
	else
	{
		serv_msg(":Permission denied!\n", 481, i);
	}
}