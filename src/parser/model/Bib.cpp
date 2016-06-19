//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "Bib.h"

#include <algorithm>

const std::string& Bib::getValue(const std::string& key, size_t offset)
{
	return getKeyValue(key, offset).getValue();
}

const std::string& Bib::getValueSafe(const std::string& key, const std::string& defaultValue, size_t offset)
{
	if (hasKey(key) == false)
	{
		return defaultValue;
	}
	return getValue(key, offset);
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


void Bib::setValue(const std::string& key, const std::string& value, size_t offset)
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
		found->setValue(value);
		return;
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

void Bib::add(const KeyValue& keyValue)
{
	_keyValues.emplace_back(keyValue);
}

bool Bib::hasKey(const std::string& key)
{
	return getValuesCount(key) > 0;
}

int Bib::getValuesCount(const std::string& key)
{
	int foundCount = 0;
	for (auto& element : _keyValues)
	{
		if (element.getKey() == key)
		{
			++foundCount;
		}
	}
	return foundCount;
}
