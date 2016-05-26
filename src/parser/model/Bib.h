//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#pragma once

#include <map>

#include "KeyValue.h"

class Bib
{
public:
	const std::string& getCite() const
	{
		return _cite;
	}

	const std::string& getEntryType() const
	{
		return _entryType;
	}

	const std::vector<KeyValue>& getKeyValues() const
	{
		return _keyValues;
	}

	const std::string& getValue(const std::string& key, size_t offset = 0);

private:
	std::string _cite;
	std::string _entryType;
	std::map<std::string, int> _keys;
	std::vector<KeyValue> _keyValues;
};


