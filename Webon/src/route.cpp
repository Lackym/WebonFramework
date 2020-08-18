#include <webon/webon.h>
#include <functional>
#include <string>
#include <boost/algorithm/string.hpp>

namespace webon {

	route::route(std::string method, std::string path, webon::controller controller)
		: _path(path), _controller(controller)
	{
		boost::to_upper(method);
		_method = method;
	}

	void route::add_middleware(webon::middleware middleware)
	{
		_middlewares.push_back(middleware);
	}

	route::~route() 
	{
		
	}

	std::vector<webon::middleware> route::get_middlewares()
	{
		return _middlewares;
	}

	webon::controller route::get_controller()
	{
		return _controller;
	}

	bool route::is_match(std::string path)
	{
		return _path.compare(path) == 0;
	}

	std::string route::get_method()
	{
		return _method;
	}

	route* route::match_route(std::string method, std::string path, std::vector<route>& routes)
	{
		boost::to_upper(method);
		auto result = std::find_if(routes.begin(), routes.end(), [&path, &method](route& route) {
			return route.get_method().compare(method) == 0 && route.is_match(path);
		});
		
		return result._Ptr;
	}
}