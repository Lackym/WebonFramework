#include <webon/webon.h>
#include <string>

namespace webon {

	std::string request::get_path()
	{
		return "/";
	}

	std::string request::get_method()
	{
		return "GET";
	}

	request::request()
	{
		
	}

	request::~request()
	{

	}
}