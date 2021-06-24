/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:48:06 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	user_command( enviroment &, const std::string &temp, user* i, std::stringstream &ss )
{
	std::string hostname;
	std::string servername;
	std::string realname;
	std::string	realbuff;

	ss >> hostname;
	ss >> servername;
	ss >> realname;
	if (temp.empty() || hostname.empty() || servername.empty() || realname.empty())
	{
		return (serv_msg(":Not enough parameters\n", 461, i));
	}
	if ((*i).get_login_lvl() == 2)
		return (serv_msg(":You can not register again\n", 433, i));
	if (!(*i).get_name().empty())
	{
		if ((*i).get_login_lvl() == 1)
		{
			(*i).set_login_lvl(2);
			#ifdef IRC_DEBUG_MODE
			std::cerr << (*i).get_user() << " loaded" << std::endl;
			#endif
		}
	}
	(*i).set_user(temp);
	(*i).set_host_name(hostname);
	(*i).set_server_name(servername);
	if (realname[0] == ':')
	{
		realname.erase(realname.begin());
		while (ss >> realbuff)
		{
			realname += (" " + realbuff);	
		}
	}
	(*i).set_real_name(realname);
}