/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:44:23 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 17:45:14 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

user	server_init( int port )
{
	int server_fd;
	int optval = 1;
	struct sockaddr_in address;

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}
	fcntl(server_fd, F_SETFL, O_NONBLOCK);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); 

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 10) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}
	return (user(server_fd));
}

void	set_fd(std::list<user> &users, fd_set &fd_read, fd_set &fd_write)
{
	int max = -1;
	std::list<user>::iterator i = users.begin();
	FD_ZERO(&fd_read);									//https://www.opennet.ru/base/dev/kevent_freebsd.txt.html
	FD_ZERO(&fd_write);									//Тут коротко и понятно описан принцип работы select,
	while (i != users.end())
	{
		FD_SET((*i).get_fd(), &fd_read);
		if (!(*i).msg_empty() && i != users.begin())
			FD_SET((*i).get_fd(), &fd_write);
		max = std::max(max, (*i).get_fd());
		++i;
	}

	if (select(max + 1, &fd_read, &fd_write, NULL, NULL) < 0)
	{
		std::cerr << "Select error max = " << max << std::endl;
		std::cerr << std::strerror(errno) << std::endl;
		exit(1);
	}
}

void	new_connection( enviroment &env )
{
	int new_socket;															//users[0] == server c:
	struct sockaddr_in address;												//Пользователь с индексом 0 это наш сервер
    int addrlen = sizeof(address);

	if ((new_socket = accept(env.users.front().get_fd(), \
	(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)					//Таким образом мы можем подключать новых пользователей
	{
		std::cerr << "Accept error" << std::endl;
		std::cerr << std::strerror(errno) << std::endl;
		exit(1);
	}
	fcntl(new_socket, F_SETFL, O_NONBLOCK);
	#ifdef IRC_DEBUG_MODE
	std::cout << "User " << new_socket - 3 << " IP:" << inet_ntoa(address.sin_addr) <<  " connected" << std::endl;
	#endif
	env.users.push_back(user(new_socket));
	env.users.back().set_adress(address);
	if (env.password.empty())
	{
		env.users.back().set_login_lvl(1);
	}
}

void	disconnect_user( enviroment &env, std::list<user>::iterator &i )
{
	#ifdef IRC_DEBUG_MODE
	std::cout << "User " << (*i).get_fd() - 3 << " disconnected" << std::endl;
	#endif
	destroy_it(&(*i), env);
	i = env.users.erase(i);
}

void	handle_fd( enviroment &env, fd_set &fd_read, fd_set &fd_write )
{
	std::list<user>::iterator i = env.users.begin();
	int	rret;

	while (i != env.users.end())
	{
		if ((*i).get_quit() == true) 
		{
			disconnect_user(env, i);
			if (i == env.users.end())
				break;
		}
		if (FD_ISSET((*i).get_fd(), &fd_write)) {(*i).msg_send();}
		if (FD_ISSET((*i).get_fd(), &fd_read))
		{
			if (i == env.users.begin()) {new_connection(env);}
			else
			{
				char buffer[500] = {0};
				rret = recv((*i).get_fd(), buffer, 500, 0);
				if (rret > 0)
				{
					#ifdef IRC_DEBUG_MODE
					std::cout << (*i).get_name() << ' ' << buffer << std::endl;
					#endif
					if (rret == 500)
					{
						(*i).msg_push(c_string("Your messege is too long, be brief c:\n"));
					}
					else
					{
						multiline_fix(env, &(*i), buffer);
					}
				}
				else
				{
					disconnect_user(env, i);
					--i;
				}
			}
		}
		++i;
	}
}
