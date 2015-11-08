/*
 * param.h
 *
 *  Created on: Nov 8, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_PARAM_H_
#define SRC_SERVER_PARAM_H_

#include <string>

namespace http {
namespace server {

struct Param {
	std::string name;
	std::string value;
};

}  // namespace server
}  // namespace http

#endif /* SRC_SERVER_PARAM_H_ */
