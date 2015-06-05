/*
 * Selector.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include <string>

class ISelector {
public:
	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~ISelector() {
	}

	virtual std::string selectObjects(std::string status) = 0;

	virtual std::string getPrefix() = 0;

	virtual void setPrefix(std::string inputPrefix) = 0;
};

class DefaultSelector: public ISelector {
public:
	DefaultSelector() : prefix(""), delimiter("\t") {
	}

	std::string selectObjects(std::string status);
	std::string getPrefix();
	void setPrefix(std::string inputPrefix);

private:
	std::string prefix;
	std::string delimiter;
};

#endif /* SELECTOR_HPP_ */
