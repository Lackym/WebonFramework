#pragma once

#include <webon/webon.h>
#include <string>
#include <cstdint>

namespace webon {

	class WEBON_API redirect_response : public webon::i_response
	{
	private:
		std::string _location;
	public:
		redirect_response(std::string);
		std::int16_t get_status_code() override;
		std::vector<webon::header> get_headers() override;
		std::string get_content() override;
	};

}