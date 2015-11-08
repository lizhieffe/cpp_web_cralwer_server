/*
 * read_file_handler.h
 *
 *  Created on: Nov 7, 2015
 *      Author: zhili
 */

#ifndef SRC_HTTP_HANDLER_READ_FILE_HANDLER_H_
#define SRC_HTTP_HANDLER_READ_FILE_HANDLER_H_

#include "../interface/http_handler.h"

namespace http {
namespace handler {

HttpHandlerHolder NewReadFileHandler(const std::string doc_root);

}  // namespace handler
}  // namespace http

#endif /* SRC_HTTP_HANDLER_READ_FILE_HANDLER_H_ */
