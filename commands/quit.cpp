/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:41:03 by gkott             #+#    #+#             */
/*   Updated: 2021/06/22 18:22:59 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

void    quit(enviroment &, const std::string &msg, user* i, std::stringstream &ss )
{
    std::string buff;
    std::string temp(msg);
    while (ss >> buff)
    {
        temp = temp + " " + buff;
    }
    (*i).set_quit_msg(temp);
    (*i).set_quit();
    (*i).msg_push(c_string("technical msg\n"));
}