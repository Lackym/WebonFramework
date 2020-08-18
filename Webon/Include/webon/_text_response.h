#pragma once

#include <webon/webon.h>
#include <string>
#include <vector>

namespace webon {

	class WEBON_API text_response : public webon::i_response
	{
	public:
		text_response(std::string, std::vector<webon::header> = std::vector<header>());

		std::int16_t get_status_code() override;
		std::vector<webon::header> get_headers() override;
		std::string get_content() override;

	private:
		std::vector<webon::header> _headers;
		std::string _content;
	};

}