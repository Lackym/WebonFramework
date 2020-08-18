#pragma once

#include <webon/webon.h>
#include <vector>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread.hpp>
#include <string>

namespace webon {

	typedef std::shared_ptr<boost::asio::ip::tcp::socket> tcp_socket_ptr;

	class WEBON_API server
	{
	public:
		server(std::vector<webon::route>, std::int16_t, 
			webon::i_data_protocol*);
		~server();

		void start_server(bool, unsigned int = boost::thread::hardware_concurrency());

	private:
		std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
		boost::asio::io_context _io;
		boost::asio::io_context::strand _strand;
		webon::i_data_protocol* _data_protocol;
		std::vector<webon::route> _routes;
		std::vector<boost::thread> _threads;

		void start_accept();
		std::string process_request(std::string);
		void start_read(std::shared_ptr<boost::asio::ip::tcp::socket>);
		void accept_handler(boost::system::error_code, 
			std::shared_ptr<boost::asio::ip::tcp::socket>);
		void read_handler(boost::system::error_code,
			std::shared_ptr<boost::asio::ip::tcp::socket>, 
			std::string, size_t);
	};
}