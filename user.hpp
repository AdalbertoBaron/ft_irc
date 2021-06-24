/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaron <abaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 01:45:51 by alelah            #+#    #+#             */
/*   Updated: 2021/06/22 18:11:41 by abaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

#ifndef USER_H
# define USER_H

class user
{
private:
	std::string				_nick;
	std::string				_user;
	std::string				_hostname;
	std::string				_servername;
	std::string				_realname;
	std::string				_buffer;
	std::string				_quit_msg;
	int						_fd;
	bool					_op;
	bool					_quit;
	int						_login_lvl;
	std::queue<char*>		_messeges;
	std::list<std::string>	_user_channels;
	std::string				_address;

public:
	user( const int &fd ) : _fd(fd)
	{
		_op = false;
		_login_lvl = 0;
		_quit = false;
	};
	user( const user &cpy ) : 
	_nick(cpy._nick),
	_user(cpy._user),
	_hostname(cpy._hostname),
	_servername(cpy._servername),
	_realname(cpy._realname),
	_buffer(cpy._buffer),
	_quit_msg(cpy._quit_msg),
	_fd(cpy._fd),
	_op(cpy._op),
	_quit(cpy._quit),
	_login_lvl(cpy._login_lvl),
	_messeges(cpy._messeges),
	_user_channels(cpy._user_channels),
	_address(cpy._address) {};
	user	&operator=( const user &cpy )
	{
		if (this == &cpy)
			return (*this);
		_nick = cpy._nick;
		_user = cpy._user;
		_hostname = cpy._hostname;
		_servername = cpy._servername;
		_realname = cpy._realname;
		_buffer = cpy._buffer;
		_quit_msg = cpy._quit_msg;
		_fd = cpy._fd;
		_op = cpy._op;
		_quit = cpy._quit;
		_login_lvl = cpy._login_lvl;
		_messeges = cpy._messeges;
		_user_channels = cpy._user_channels;
		_address = cpy._address;
		return (*this);
	}
	void		destroy( void )
	{
		close(_fd);
		while (!_messeges.empty())
		{
			delete[] _messeges.front();
			_messeges.pop();
		}
	}
	~user() {};

	int			get_fd( void ) const { return (_fd); };
	bool		is_op( void ) const { return (_op); };
	void		op_me( void ) 	{ _op = true; };
	void		deop_me( void )	{ _op = false; };
	const int	&get_login_lvl( void ) const { return (_login_lvl); };
	void		set_login_lvl( const int &lvl ) { _login_lvl = lvl; };

	const std::string	&get_name( void ) const {return (_nick);};
	void				set_name(const std::string &name) {_nick = name;};
	const std::string	&get_user( void ) const {return (_user);};
	void				set_user(const std::string &name)
	{
		if (_user.size() == 0)
			_user = name;
	};
	const std::string	&get_host_name( void ) const {return (_hostname);};
	void				set_host_name(const std::string &name)
	{
		if (_hostname.size() == 0)
			_hostname = name;
	};
	const std::string	&get_server_name( void ) const {return (_servername);};
	void				set_server_name(const std::string &name)
	{
		if (_servername.size() == 0)
			_servername = name;
	};
	const std::string	&get_real_name( void ) const {return (_realname);};
	void				set_real_name(const std::string &name)
	{
		if (_realname.size() == 0)
			_realname = name;
	};

	void				set_adress( const struct sockaddr_in &adr )
	{
		_address = inet_ntoa(adr.sin_addr);
	};

	const std::string	&get_ip( void ) const
	{
		return (_address);
	}

	void				set_quit( void ) {_quit = true;};
	const bool			&get_quit( void ) const {return (_quit);};

	void				set_quit_msg( const std::string &msg ) {_quit_msg = msg;};
	const std::string	&get_quit_msg( void ) const {return (_quit_msg);};

	const std::string	&get_buffer( void ) const {return (_buffer);};
	void				clear_buffer( void ) {_buffer.clear();};
	void				push_buffer( const std::string &str ) {_buffer += str;};

	bool		channels_find( const std::string &tofind ) const
	{
		return (std::find(_user_channels.begin(), _user_channels.end(), tofind) != _user_channels.end());
	}
	void		channels_push( const std::string tofind )
	{
		_user_channels.push_back(tofind);
	}
	void		channels_delete( const std::string &todel )
	{
		std::list<std::string>::iterator it;

		it = std::find(_user_channels.begin(), _user_channels.end(), todel);
		if (it != _user_channels.end())
			_user_channels.erase(it);
		else
			std::cerr << "Error in channels_delete" << std::endl;
	}
	const std::list<std::string> &channels_list( void ) const { return (_user_channels); };

	void		msg_push(char *msg) {_messeges.push(msg);};
	bool		msg_empty( void ) {return (_messeges.empty());};

	void		msg_send( void )
	{
		if (!_messeges.empty())
		{
			send(_fd, _messeges.front(), strlen(_messeges.front()), 0);
			delete[] _messeges.front();
			_messeges.pop();
		}
		else
			std::cerr << "Smth was broken :c No msg to send" << std::endl;
	}

	std::string sign_msg(const std::string &s )
	{
		std::string ret = ":" + _nick + "!" + _user + "@" + _address + " " + s;
		return (ret);
	}
};

#endif
