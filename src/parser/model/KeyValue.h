//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#pragma once

#include <string>
#include <vector>

class KeyValue
{
public:
	KeyValue(const std::string& key, const std::vector<std::string>& values = {});

	const std::string& getKey() const
	{
		return _key;
	}

	const std::string& getValue(int offset = 0) const
	{
		return _values.at(offset);
	}

private:
	std::string _key;
	std::vector<std::string> _values;
};


