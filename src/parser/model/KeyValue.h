//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#pragma once

#include <string>
#include <vector>

class KeyValue
{
public:
	KeyValue(const std::string& key = "", const std::string& value = "");

	const std::string& getKey() const
	{
		return _key;
	}

	const std::string& getValue() const
	{
		return _value;
	}

	bool hasNested()
	{
		return false;//TODO implement
	}

private:
	std::string _key;
	std::string _value;
	std::vector<KeyValue> _nasted;
};


