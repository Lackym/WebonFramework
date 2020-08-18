#include <webon/webon.h>
#include <string>
#include <tuple>
#include <vector>

namespace webon {

	webon::request http_protocol::parse_request(std::string)
	{
		return webon::request();
	}

	std::string http_protocol::get_response(webon::i_response* i_response)
	{
		std::string content = i_response->get_content();
		std::int16_t status = i_response->get_status_code();
		std::vector<webon::header> headers = i_response->get_headers();
		
		//TODO: add more headers here.
		std::vector<webon::header> protocol_headers = {
			{ "Content-Length", std::to_string(content.size()) },
			{ "Server", "Webon" },
			{ "Connection", "keep-alive" },
			{ "Keep-Alive", "timeout=10, max=1000" }
		};

		headers.insert(headers.end(), protocol_headers.begin(), protocol_headers.end());

		std::string response_text = "HTTP/1.1 " + std::to_string(status) + 
			" " + webon::get_status_text(status) + "\n";

		for (auto& header : headers)
		{
			response_text += std::get<0>(header) + ": " + std::get<1>(header) + "\n";
		}

		response_text += "\n" + content;

		return response_text;
	}

}