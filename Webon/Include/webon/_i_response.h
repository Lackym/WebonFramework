#pragma once

#include <webon/webon.h>
#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include <tuple>

namespace webon {

	typedef std::tuple<std::string, std::string> header;

	class WEBON_API i_response
	{
	public:
		virtual std::int16_t get_status_code() = 0;
		virtual std::vector<webon::header> get_headers() = 0;
		virtual std::string get_content() = 0;
	};
}