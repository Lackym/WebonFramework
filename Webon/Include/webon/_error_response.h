#pragma once

#include <webon/webon.h>
#include <cstdint>
#include <string>
#include <vector>

namespace webon {

	class WEBON_API error_response : public webon::i_response
	{
	public:
		error_response(std::int16_t, std::vector<webon::header> = std::vector<header>());

		std::int16_t get_status_code() override;
		std::vector<webon::header> get_headers() override;
		std::string get_content() override;

	private:
		std::int16_t _status_code;
		std::vector<webon::header> _headers;
	};

}