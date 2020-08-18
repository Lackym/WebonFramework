#pragma once

#include <webon/webon.h>
#include <string>

namespace webon {

	class WEBON_API request
	{
	public:
		std::string get_path();
		std::string get_method();
		request();
		~request();

	};

}