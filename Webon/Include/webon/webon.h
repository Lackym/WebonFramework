#ifndef __WebonHeader__
#   define __WebonHeader__
#   ifdef BUILD_WEBON
#       define WEBON_API __declspec(dllexport)
#   else
#       define WEBON_API __declspec(dllimport)
#   endif

#include "_response_codes.h"
#include "_request.h"

//responses
#include "_i_response.h"
#include "_error_response.h"
#include "_text_response.h"
#include "_redirect_response.h"

#include "_route.h"

//data protocols
#include "_i_data_protocol.h"
#include "_http_protocol.h"

#include "_server.h"

#endif //__webonHeader__