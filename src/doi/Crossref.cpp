//
// Created by Dawid Drozd aka Gelldur on 6/18/16.
//

#include "Crossref.h"
#include "api/UrlBuilder.h"
#include "StringUtils.h"

#include <sstream>
#include <iostream>

#include <json/json.h>
#include <api/Request.h>
#include <Config.h>

void Crossref::fetchDoi(std::vector<Bib>& bibs)
{
	int doiCount = 0;
	int position = 0;
	for (auto& bib : bibs)
	{
		if (_config.isReplaceExistingDoi() || bib.hasKey("doi") == false)
		{
			std::cout << "\nSearching DOI for " << bib.getCite() << " " << bib.getEntryType() << " progress:" <<
			++position << "/" << bibs.size() << std::endl;
			if (checkDoi(bib) == false)
			{
				std::cout << "Sorry can't find DOI for " << bib.getCite() << std::endl;
			}
			else
			{
				++doiCount;
			}
		}
		else
		{
			++doiCount;
			std::cout << "\nAlready have DOI for " << bib.getCite() << " " << bib.getValue("doi") << " progress:" <<
			++position << "/" << bibs.size() << std::endl;
		}
	}

	std::cout << "Crossref doi: " << doiCount << "/" << bibs.size() << std::endl;
}

bool Crossref::checkDoi(Bib& bib)
{
	UrlBuilder builder{"/works"};
	builder.appendQuery("query.title", bib.getValue("title"));
	builder.appendQuery("rows", 25);

	const auto& authors = getAuthors(bib);
	if (authors.empty() == false)
	{
		builder.appendQuery("query.author", StringUtils::join(authors, "+"));
	}

	const auto& filters = getFilters(bib);
	if (filters.empty() == false)
	{
		builder.appendQuery("filter", StringUtils::join(filters, ","));
	}

	auto& responseStream = Request::get(_session, builder.build());

	//		std::string responseAsString(std::istreambuf_iterator<char>(responseStream), {});
	//		std::cout << responseAsString << std::endl;

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(responseStream, root, false) == false)
	{
		std::cout << "Error parsing json:" << reader.getFormattedErrorMessages() << std::endl;
		throw std::runtime_error(reader.getFormattedErrorMessages());
	}

	const auto& message = root.get("message", Json::Value::nullRef);
	const auto& items = message.get("items", Json::Value::nullRef);

	for (const auto& item : items)
	{
		auto doi = extractDoi(item, bib);

		auto previousDoi = bib.getValueSafe("doi", "");
		if (previousDoi.empty() == false && doi.empty() == false)
		{
			if (doi != previousDoi)
			{
				std::cout << "NEW DOI IS DIFFERENT!!!!!!!!!!!!!!!!!!!" << std::endl;
				std::cout << "New:" << doi << "\nOld:" << previousDoi << std::endl;
			}
		}

		if (doi.empty() == false)
		{
			if (bib.hasKey("doi"))
			{
				bib.setValue("doi", doi);
			}
			else
			{
				bib.add({"doi", doi});
			}
			return true;
		}

	}

	return false;
}

std::vector<std::string> Crossref::getFilters(Bib& bib)
{
	std::vector<std::string> filters;

	const auto& date = bib.getValueSafe("date");
	if (date.empty() == false)
	{
		filters.emplace_back(std::string("from-pub-date:") + date);
		filters.emplace_back(std::string("until-pub-date:") + date);
	}

	filters.emplace_back(std::string("type:") + _config.getCrossrefType(bib.getEntryType()));

	return filters;
}

std::vector<std::string> Crossref::getAuthors(Bib& bib)
{
	std::vector<std::string> authors;
	int authorCount = bib.getValuesCount(KEY_AUTHOR);
	for (int i = 0; i < authorCount; ++i)
	{
		const auto& value = bib.getValue(KEY_AUTHOR, i);
		std::string surname{value.begin(), std::find(value.begin(), value.end(), ',')};
		authors.emplace_back(StringUtils::trim(surname));
	}

	return authors;
}

enum class Check
{
	SKIP, INVALID, OK
};

std::string  Crossref::extractDoi(Json::Value item, Bib& bib)
{
	using namespace std;
	using namespace Json;

	const auto& doi = item.get("DOI", Value::nullRef);
	if (doi.isNull())
	{
		std::cerr << "Missing DOI number!" << std::endl;
		return {};
	}

	Check isSameTitle = Check::INVALID;
	{
		int i = 0;
		const auto& titles = item.get("title", Value::nullRef);
		while (isSameTitle == Check::INVALID && i < titles.size())
		{
			if (StringUtils::fuzzyCompare(bib.getValue("title"), titles[i].asString()) >= 0.75F)
			{
				isSameTitle = Check::OK;
			}
			++i;
		}
	}

	Check isSameVolume = bib.hasKey("volume") ? Check::INVALID : Check::SKIP;
	if (isSameVolume == Check::INVALID)
	{
		isSameVolume = item.get("volume", "").asString() == bib.getValue("volume") ? Check::OK : Check::INVALID;
	}

	Check isSamePages = bib.hasKey("pages") ? Check::INVALID : Check::SKIP;
	if (isSamePages == Check::INVALID)
	{
		auto pages = bib.getValue("pages");
		pages.replace(pages.find("--"), 2, "-");

		isSamePages = item.get("page", "NO!*@#&").asString() == pages ? Check::OK : Check::INVALID;
	}

	Check isSameAuthorCount =
			bib.getValuesCount(KEY_AUTHOR) == item.get("author", Value::nullRef).size() ? Check::OK : Check::INVALID;

	if (isSameTitle == Check::OK)
	{
		cout << "Same title" << endl;
	}
	if (isSameAuthorCount == Check::OK)
	{
		cout << "Same Author count" << endl;
	}
	if (isSameVolume == Check::OK)
	{
		cout << "Same Volume" << endl;
	}
	if (isSamePages == Check::OK)
	{
		cout << "Same Pages" << endl;
	}

	std::function<void()> printItem = [&]()
	{
		const auto& titles = item.get("title", Value::nullRef);
		for (const auto& title : titles)
		{
			cout << "Title: " << title.asString() << endl;
		}

		cout << "Publisher: " << item.get("publisher", "null").asString() << endl;
		cout << "Authors: " << item.get("author", "null").toStyledString() << endl;
		cout << "Container: " << item.get("container-title", "null").toStyledString() << endl;
	};

	std::function<std::string()> returned = [&]()
	{
		cout << "I got DOI: " << doi.asString() << endl;
		cout << "Bib Title: " << bib.getValueSafe("title") << endl;
		for (int i = 0; i < bib.getValuesCount("author"); ++i)
		{
			cout << "Bib Author: " << bib.getValue("author", i) << endl;
		}

		printItem();
		return doi.asString();
	};

	if (isSameTitle == Check::OK && isSameAuthorCount == Check::OK)
	{
		return returned();
	}

	std::function<bool(Check)> checker = [&](Check check)
	{
		return check == Check::OK || check == Check::SKIP;
	};

	if (isSameAuthorCount == Check::OK && checker(isSamePages) && checker(isSameVolume))
	{
		return returned();
	}

	return {};
}
