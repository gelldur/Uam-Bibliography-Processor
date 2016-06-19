//
// Created by Dawid Drozd aka Gelldur on 6/18/16.
//

#pragma once

#include <parser/model/Bib.h>
#include <json/json.h>
#include <Config.h>
#include <Poco/Net/HTTPClientSession.h>

class Crossref
{
public:
	Crossref(const Config& config)
			: _config(config)
	{
	}

	void fetchDoi(std::vector<Bib>& bibs);

private:
	bool checkDoi(Bib& bib);
	std::vector<std::string> getFilters(Bib& bib);
	std::vector<std::string> getAuthors(Bib& bib);

	std::string extractDoi(Json::Value item, Bib& bib);

	const std::string KEY_AUTHOR{"author"};
	Poco::Net::HTTPClientSession _session{"api.crossref.org"};
	const Config& _config;
};


