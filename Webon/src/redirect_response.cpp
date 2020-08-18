#include <webon/webon.h>
#include <string>
#include <cstdint>
#include <tuple>

namespace webon {

	redirect_response::redirect_response(std::string location)
		: _location(location)
	{

	}

	std::int16_t redirect_response::get_status_code()
	{
		return 302;
	}

	std::vector<webon::header> redirect_response::get_headers()
	{
		return {
			{ "Location", _location },
		};
	}

	std::string redirect_response::get_content()
	{
		return "";
	}

}