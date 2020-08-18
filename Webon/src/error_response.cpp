#include <webon/webon.h>
#include <cstdint>
#include <vector>
#include <exception>
#include <string>

namespace webon {

	error_response::error_response(std::int16_t status_code, std::vector<webon::header> headers)
		: _status_code(status_code), _headers(headers)
	{
		if (status_code < 400 || status_code > 599)
		{
			throw std::exception("Cannot create error response with no error status");
		}

		_headers.push_back(std::make_tuple("Content-Type", "text/html; charset=utf-8"));
	}

	std::int16_t error_response::get_status_code()
	{
		return _status_code;
	}

	std::vector<webon::header> error_response::get_headers()
	{
		return _headers;
	}

	std::string error_response::get_content()
	{
		return "<b>Error</b>: " +
			std::to_string(get_status_code()) +
			" " + webon::get_status_text(get_status_code()) +
			"<br/>" +
			"<hr/>" +
			"<small>Webon framework.</small>";
	}

}