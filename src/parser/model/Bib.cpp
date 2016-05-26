//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "Bib.h"

#include <algorithm>

const std::string& Bib::getValue(const std::string& key, size_t offset)
{
	return getKeyValue(key, offset).getValue();
}

const KeyValue& Bib::getKeyValue(const std::string& key, size_t offset)
{
	int foundCount = -1;
	auto found = std::find_if(_keyValues.begin(), _keyValues.end(), [&](const KeyValue& keyValue)
	{
		if (keyValue.getKey() == key)
		{
			if (++foundCount == offset)
			{
				return true;
			}
		}
		return false;
	});

	if (found != _keyValues.end())
	{
		return *found;
	}
	if (foundCount != -1)
	{
		throw std::runtime_error(std::string("Offset to big:") + std::to_string(offset));
	}
	throw std::runtime_error(std::string("Key not found:") + key);
}

void Bib::add(const std::vector<KeyValue>& keyValues)
{
	//TODO sort by keys?
	for (const auto& element : keyValues)
	{
		_keyValues.emplace_back(element);
	}
}
