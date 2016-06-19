//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "KeyValue.h"

KeyValue::KeyValue(const std::string& key, const std::string& value)
		: _key(key)
		, _value(value)
{
}

void KeyValue::setValue(const std::string& value)
{
	_value = value;
}
