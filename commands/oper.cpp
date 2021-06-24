/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:44:29 by gkott             #+#    #+#             */
/*   Updated: 2021/06/20 17:18:24 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void	oper( enviroment &, const std::string &name, user* i, std::stringstream &ss )
{
	std::string	temp(name);
	if (temp.empty())
	{
		return (serv_msg(":No recipient given\n", 411, i));
	}
	std::ifstream fin;
	temp = "./data/OPERdata/" + temp;
	fin.open(temp.c_str());
	if (fin.is_open())
	{
		std::string pwd;
		fin >> pwd;
		ss >> temp;
		if (pwd == temp)
		{
			(*i).op_me();
			fin.close();
			return ;
		}
		fin.close();
	}
	serv_msg(":Wrong name or password!\n", 481, i);
}
