/*
 * read_file_handler.cpp
 *
 *  Created on: Nov 7, 2015
 *      Author: zhili
 */

#include "read_file_handler.h"

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "../server/mime_types.h"
//#include "src/server/reply.h"
//#include "src/server/request.h"

namespace http {
namespace handler {
namespace {

using http::server::mime_types::extension_to_type;
using http::server::reply;
using http::server::request;

class ReadFileHandler : public HttpHandler {
public:
	explicit ReadFileHandler(const std::string doc_root) : doc_root_(doc_root) {}
	~ReadFileHandler() {}

	void HandleRequest (
			const http::server::request& req, http::server::reply* rep) override;

private:
	bool url_decode(const std::string& in, std::string& out) const;

	const std::string doc_root_;
};

void ReadFileHandler::HandleRequest (
		const http::server::request& req, http::server::reply* rep) {
	// Decode url to path.
	std::string request_path;
	if (!url_decode(req.uri, request_path)) {
		std::cout << "Decode url to path fails." << std::endl;
		*rep = reply::stock_reply(reply::bad_request);
		return;
	}

	// Request path must be absolute and not contain "..".
	if (request_path.empty() || request_path[0] != '/'
			|| request_path.find("..") != std::string::npos) {
		std::cout << "Illegal request path: " << request_path << std::endl;
		*rep = reply::stock_reply(reply::bad_request);
		return;
	}

	// If path ends in slash (i.e. is a directory) then add "index.html".
	if (request_path[request_path.size() - 1] == '/') {
		request_path += "index.html";
	}

	std::cout << "Get request_path: " << request_path << std::endl;

	// Determine the file extension.
	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	std::string extension;
	if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
		extension = request_path.substr(last_dot_pos + 1);
	}

	// Open the file to send back.
	std::string full_path = doc_root_ + request_path;
	std::cout << "Tries to open file: " << full_path << std::endl;
	std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	if (!is) {
		std::cout << "Cannot open file: " << full_path << std::endl;
		*rep = reply::stock_reply(reply::not_found);
		return;
	}

	// Fill out the reply to be sent to the client.
	rep->status = reply::ok;
	char buf[512];
	while (is.read(buf, sizeof(buf)).gcount() > 0)
		rep->content.append(buf, is.gcount());
	rep->headers.resize(2);
	rep->headers[0].name = "Content-Length";
	rep->headers[0].value = boost::lexical_cast<std::string>(rep->content.size());
	rep->headers[1].name = "Content-Type";
	rep->headers[1].value = extension_to_type(extension);
}

bool ReadFileHandler::url_decode(
		const std::string& in, std::string& out) const {
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else
		{
			out += in[i];
		}
	}
	return true;
}

}  // namespace

HttpHandlerHolder NewReadFileHandler(const std::string doc_root) {
	return std::unique_ptr<HttpHandler>(new ReadFileHandler(doc_root));
}

}  // namespace handler
}  // namespace http
