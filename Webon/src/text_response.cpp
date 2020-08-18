#include <webon/webon.h>
#include <string>
#include <cstdint>
#include <tuple>

namespace webon {

	text_response::text_response(std::string content, std::vector<webon::header> headers)
		: _content(content), _headers(headers)
	{
		_headers.push_back(std::make_tuple("Content-Type", "text/html; charset=utf-8"));
	}

	std::int16_t text_response::get_status_code()
	{
		return 200;
	}

	std::vector<webon::header> text_response::get_headers()
	{
		return _headers;
	}

	std::string text_response::get_content()
	{
		return _content;
	}

}