/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkott <gkott@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:11:41 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 14:18:49 by gkott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

int		main(int argc, char const *argv[])
{
	if (argc < 3 || argc > 4)
	{
		std::cerr << "Usage: ./ircserv [host:port_network:password_network] "
		<< "<port> <password>" << std::endl;
		return (1);
	}
	for (size_t i = 0; i < strlen(argv[argc - 2]); ++i)
	{
		if (!isdigit(argv[argc - 2][i]) || !argv[argc - 2][0])
		{
			std::cerr << "wrong port" << std::endl;
			exit(1);
		}
	}

	enviroment env;
	env.password = argv[argc - 1];

	env.users.push_back(server_init(atoi(argv[argc - 2])));
	comands_init(env);

	fd_set	fd_read;
	fd_set	fd_write;

	while(1)
	{
		set_fd(env.users, fd_read, fd_write);
		handle_fd(env, fd_read, fd_write);
	}
	return (0);
}