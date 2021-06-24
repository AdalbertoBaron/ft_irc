/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelah <alelah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:50:13 by gkott             #+#    #+#             */
/*   Updated: 2021/06/21 20:43:15 by alelah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	pass( enviroment &env, const std::string &temp, user* i, std::stringstream & )
{
	if ((*i).get_login_lvl() > 0)
		return ;
	if (temp == env.password)
	{
		return ((*i).set_login_lvl(1));
	}
	return (serv_msg(":Wrong password\n", 464, i));
}