#include <webon/webon.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system/error_code.hpp>
#include <memory>
#include <functional>

namespace webon {

	server::server(std::vector<webon::route> routes, std::int16_t port, 
		webon::i_data_protocol* data_protocol)
		: _routes(routes), _data_protocol(data_protocol), _io(), 
			_strand(_io)
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
		_acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>
			(boost::asio::ip::tcp::acceptor(_io, std::move(endpoint)));

		std::cout << "Server started listen on port " << port << "\n";
		start_accept();
	}

	void server::start_accept()
	{
		using namespace boost::asio;
		using namespace boost::placeholders;

		webon::tcp_socket_ptr socket(new ip::tcp::socket(_io));
		_acceptor->async_accept(*socket,
			boost::asio::bind_executor(_strand,
				boost::bind(&server::accept_handler, this, _1, socket)));
	}

	void server::accept_handler(boost::system::error_code error, 
		webon::tcp_socket_ptr socket)
	{
		if (error)
		{
			std::cout << "New connection with error." << "\n";
			start_accept();
			return;
		}
		
		start_read(socket);

		std::cout << "New connection." << "\n";
		start_accept();
	}

	void server::start_read(webon::tcp_socket_ptr socket)
	{
		using namespace boost::placeholders;

		//TODO: Replace fixed buff size (High)
		//TODO: Add timeout for reading (Medium)
		std::array<char, 2048> buff;
		socket->async_read_some(boost::asio::buffer(buff),
			boost::asio::bind_executor(_strand, boost::bind(&server::read_handler,
				this, _1, socket, buff.data(), _2)));
	}

	void server::read_handler(boost::system::error_code error,
		webon::tcp_socket_ptr socket, std::string data, size_t len)
	{
		if (error)
		{
			std::cout << "Connection lost." << "\n";
			return;
		}

		std::string response = process_request(data);
		
		//TODO: change it with async???
		socket->write_some(boost::asio::buffer(response));
		
		start_read(socket);
	}

	std::string server::process_request(std::string data)
	{
		webon::request request = _data_protocol->parse_request(data);
		webon::route* route_ptr = 
			webon::route::match_route(request.get_method(), request.get_path(), _routes);

		if (!route_ptr)
		{
			return _data_protocol->get_response(
				new webon::error_response(404)
			);
		}

		webon::route route = *route_ptr;
		std::vector<webon::middleware> middlewares = route.get_middlewares();
		webon::controller controller = route.get_controller();
		
		size_t middleware_index = 0;
		webon::next_middleware next;
		next = [&](webon::request lambd_request)
		{
			if (middlewares.size() == middleware_index)
				return controller(lambd_request);
			else
				return middlewares[middleware_index++](lambd_request, next);
		};

		webon:i_response* response = next(request);
		std::string response_text = _data_protocol->get_response(response);
		delete response;
		return response_text;
	}

	void server::start_server(bool block_current_thread,
		unsigned int threads_count)
	{	
		if (threads_count == 0)
		{
			std::cout << "Cannot detect hardware concurrency or threads_count = 0, server will not use concurrency" << "\n";
		}
		else
		{
			std::cout << "Server will use " << threads_count << " concurrency threads." << "\n";
			for (unsigned int i = 0; i < threads_count; ++i)
			{
				_threads.push_back(
					boost::thread(
						boost::bind(&boost::asio::io_context::run, &_io)
					)
				);
			}
		}

		if (block_current_thread)
		{
			_io.run();
		}
	}

	server::~server()
	{
		delete _data_protocol;
	}
}