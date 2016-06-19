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

	const std::string& getValue(const std::string& key, size_t offset = 0);
	const std::string& getValueSafe(const std::string& key, const std::string& defaultValue = "", size_t offset = 0);
	const KeyValue& getKeyValue(const std::string& key, size_t offset = 0);
	void setValue(const std::string& key, const std::string& value, size_t offset = 0);

	bool hasKey(const std::string& key);
	int getValuesCount(const std::string& key);

	void setCite(const std::string& cite)
	{
		_cite = cite;
	}

	void setEntryType(const std::string& entryType)
	{
		_entryType = entryType;
	}

	void add(const std::vector<KeyValue>& keyValues);
	void add(const KeyValue& keyValue);

	std::string toString() const;

private:
	std::string _cite;
	std::string _entryType;
	std::vector<KeyValue> _keyValues;
};


