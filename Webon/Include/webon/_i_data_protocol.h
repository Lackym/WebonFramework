#pragma once

#include <string>
#include <webon/webon.h>

namespace webon {

	class WEBON_API i_data_protocol
	{
	public:
		virtual webon::request parse_request(std::string) = 0;
		virtual std::string get_response(webon::i_response*) = 0;
	};

}