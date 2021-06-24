/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:39:15 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	names( enviroment &env, const std::string &temp, user* i, std::stringstream & )
{
	if (temp.size() == 0)
		return ;
	CHANNEL::iterator it = env.channels[temp].begin();
	std::string result = "= " + temp + " :";
	while (it != env.channels[temp].end())
	{
		result = result + (**it).get_name() + " ";
		++it;
	}
	serv_msg(result + "\n", 353, i);
	serv_msg(temp + " :End of /NAMES list.\n", 366, i);
}