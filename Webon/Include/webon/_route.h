#pragma once

#include <webon/webon.h>
#include <string>
#include <functional>
#include <vector>

namespace webon {
	
	typedef std::function<webon::i_response*(webon::request)> next_middleware;
	typedef std::function<webon::i_response*(webon::request, webon::next_middleware)> middleware;
	typedef std::function<webon::i_response*(webon::request)> controller;

	class WEBON_API route final
	{
	public:
		route(std::string, std::string, webon::controller);
		~route();
		void add_middleware(webon::middleware);
		std::vector<webon::middleware> get_middlewares();
		webon::controller get_controller();
		bool is_match(std::string);
		std::string get_method();

		static route* match_route(std::string, std::string, std::vector<route>&);

	private:
		std::vector<webon::middleware> _middlewares;
		webon::controller _controller;
		std::string _path;
		std::string _method;
	};

}