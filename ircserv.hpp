/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:45:49 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 15:44:48 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_H
# define IRCSERV_H
# include <cstring>
# include <cstdlib>
# include <cstdio>
# include <map>
# include <list>
# include <string>
# include <queue>
# include <fstream>
# include <algorithm>
# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sstream>
# include <csignal>
# include "user.hpp"

# define CHANNEL std::list<user*>
# define CHANNELS_MAP std::map<std::string, CHANNEL >

# define IRC_DEBUG_MODE 1

struct						enviroment
{
	std::list<user>						users;
	CHANNELS_MAP						channels;
	std::string							password;
	std::map<std::string, std::string>	topics;
	std::map<std::string, void(*)(enviroment &, const std::string &, user*, std::stringstream &)>	handlers;
};

char	*c_string(const std::string &s);
void	destroy_it( user* it, enviroment &env );
user	server_init( int port );
void	set_fd(std::list<user> &users, fd_set &fd_read, fd_set &fd_write );
void	new_connection( std::list<user> &users );
void	handle_fd( enviroment &env, fd_set &fd_read, fd_set &fd_write );
void	handle_commands( enviroment &env, user* i, std::string str );
void	serv_msg(const std::string &msg, int code, user* i);
bool	check_user_nick(std::string s1, std::string s2, enviroment &env, user* i);
void	multiline_fix(enviroment &env, user* i, std::string str );
void	stop( enviroment &env );
void	send_to_channel( enviroment &env, const std::string &temp, const std::string &msg );
void	comands_init(enviroment &env);
void	send_to_channel( enviroment &env, const std::string &temp, const std::string &msg );
user*	find_name( std::list<user> &users, const std::string &name );
user*	find_user( std::list<user> &users, const std::string &name );

std::list<user>::iterator find_name_iterator( std::list<user> &users, const std::string &name );

void	privmsg( enviroment &env, const std::string &sendto, user* i, std::stringstream &ss );
void	nick( enviroment &env, const std::string &temp, user* i, std::stringstream & );
void	user_command( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	names( enviroment &env, const std::string &temp, user* i, std::stringstream & );
void	join( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	part( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	kick( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	oper( enviroment &, const std::string &temp, user* i, std::stringstream &ss );
void	kill( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	die( enviroment &env, const std::string &, user* i, std::stringstream &);
void	pass( enviroment &env, const std::string &temp, user* i, std::stringstream & );
void	invite( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void	list( enviroment &env, const std::string &temp, user* i, std::stringstream & );
void	mode( enviroment &, const std::string &temp, user* i, std::stringstream & );
void	who( enviroment &env, const std::string &temp, user* i, std::stringstream & );
void	cap( enviroment &, const std::string &, user* , std::stringstream & );
void	topic( enviroment &env, const std::string &temp, user* i, std::stringstream &ss );
void    quit(enviroment &, const std::string &, user* i, std::stringstream & );

#endif
