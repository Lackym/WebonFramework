#pragma once

#include <webon/webon.h>
#include <string>

namespace webon {

	class WEBON_API http_protocol : public webon::i_data_protocol
	{
	public:
		webon::request parse_request(std::string) override;
		std::string get_response(webon::i_response*) override;
	};

}