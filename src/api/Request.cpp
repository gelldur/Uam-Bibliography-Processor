//
// Created by Dawid Drozd aka Gelldur on 6/19/16.
//

#include "Request.h"

#include <iostream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

namespace Request
{

std::istream& get(Poco::Net::HTTPClientSession& session, const std::string& url)
{
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPMessage;

	//"http://api.crossref.org"
	HTTPRequest request(HTTPRequest::HTTP_GET, url, HTTPMessage::HTTP_1_1);
	std::cout << session.getHost() << url << std::endl;

	session.sendRequest(request);
	HTTPResponse response;
	return session.receiveResponse(response);
}

}
