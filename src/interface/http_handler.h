/*
 * request_handler_interface.h
 *
 *  Created on: Nov 7, 2015
 *      Author: zhili
 */

#ifndef SRC_REQUEST_HANDLER_INTERFACE_H_
#define SRC_REQUEST_HANDLER_INTERFACE_H_

#include <memory>

#include "../server/reply.h"
#include "../server/request.h"

namespace http {
namespace handler {

class HttpHandler {
public:
	virtual ~HttpHandler() {}

	// Handles the request and fills in the response.
	virtual void HandleRequest(const http::server::request& req,
														 http::server::reply* rep) = 0;
};

using HttpHandlerHolder = std::unique_ptr<HttpHandler>;

}  // namespace http
}  // namespace handler

#endif /* SRC_REQUEST_HANDLER_INTERFACE_H_ */
