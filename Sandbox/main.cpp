#include <webon/webon.h>
#include <vector>
#include <iostream>
#include <tuple>
#include <boost/thread.hpp>

int main()
{
	std::vector<webon::route> routes;

	//std::vector<webon::header> custom_headers;
	//custom_headers.push_back(std::make_tuple("Custom-Sandbox-Header", "This header value"));

	//webon::route index_route = webon::route("GET", "/", [&](webon::request request) {
	//	/*return new webon::text_response("Hello world from webon::text_response!!! Yaaaiii!!!",
	//		custom_headers);*/
	//	return new webon::redirect_response("https://google.com/");
	//});

	//routes.push_back(index_route);

	webon::server server(routes, 8080, new webon::http_protocol());
	server.start_server(false);

	for (;;)
	{
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		printf("Infinit loop!\n");
	}

	return 0;
}