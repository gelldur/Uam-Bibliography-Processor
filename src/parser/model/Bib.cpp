//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "Bib.h"

const std::string& Bib::getValue(const std::string& key, size_t offset)
{
	const auto& element = _keys.find(key);
	if (element == _keys.end())
	{
		throw std::runtime_error(std::string("Key not found:") + key);
	}

	const auto& found = _keyValues[element->second];
	return found.getValue(offset);
}

