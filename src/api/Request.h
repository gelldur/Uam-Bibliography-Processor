//
// Created by Dawid Drozd aka Gelldur on 6/19/16.
//

#pragma once

#include <sstream>
#include <Poco/Net/HTTPClientSession.h>

namespace Request
{

std::istream& get(Poco::Net::HTTPClientSession& session, const std::string& url);

};


