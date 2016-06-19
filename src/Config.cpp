//
// Created by Dawid Drozd aka Gelldur on 6/19/16.
//

#include "Config.h"
#include <fstream>
#include <iostream>

using namespace Json;

Config::Config(const std::string& configFile)
		: _filePath(configFile)
{
	std::ifstream file(configFile);
	if (file.is_open() == false)
	{
		throw std::runtime_error(std::string("Can't open config file:") + configFile);
	}

	Json::Reader reader;
	if (reader.parse(file, _data, false) == false)
	{
		throw std::runtime_error(std::string("Can't parse config file:") + configFile + std::string{" Error:"} +
								 reader.getFormattedErrorMessages());
	}

	//for check ;)
	if (getCrossref() != Value::nullRef)
	{
		saveConfig(_filePath + ".backup");
	}
}

std::string Config::getCrossrefType(const std::string& bibType) const
{
	const auto& types = getCrossref().get("types", Value::nullRef);
	for (const auto& element : types)
	{
		if (element.get("amsrefType", Value::nullRef).asString() == bibType)
		{
			return element.get("to", Value::nullRef).asString();
		}
	}
	throw std::runtime_error(std::string("Missing bib type:") + bibType);
}

const Json::Value Config::getCrossref() const
{
	const auto crossref = _data.get("crossref", Value::nullRef);
	if (crossref == Value::nullRef)
	{
		throw std::runtime_error("Missing crossref config");
	}
	return crossref;
}

const Json::Value Config::getNameValidator() const
{
	const auto nameValidator = _data.get("nameValidator", Value::nullRef);
	if (nameValidator == Value::nullRef)
	{
		throw std::runtime_error("Missing nameValidator config");
	}
	return nameValidator;
}

bool Config::isReplaceExistingDoi() const
{
	const bool defaultValue = false;
	const std::string OPTION_REPLACE_EXISTING_DOI{"replaceExistingDoi"};
	const auto& options = _data.get("options", Value::nullRef);
	for (const auto& option : options)
	{
		if (option.get("name", Value::nullRef).asString() == OPTION_REPLACE_EXISTING_DOI)
		{
			return option.get("value", defaultValue).asBool();
		}
	}
	return defaultValue;
}

bool Config::isCrossrefEnabled() const
{
	return getCrossref().get("enable", true).asBool();
}

bool Config::isNameValidatorEnabled() const
{
	return getNameValidator().get("enable", true).asBool();
}

std::map<std::string, std::string> Config::getReplaceMap()
{
	const auto& replaceMap = getNameValidator().get("replaceMap", Value::nullRef);
	std::map<std::string, std::string> map;
	for (const auto& element : replaceMap)
	{
		map.emplace(element.get("from", Value::nullRef).asString(), element.get("to", Value::nullRef).asString());
	}
	return map;
}

bool Config::isAskBeforeReplace() const
{
	return getNameValidator().get("askBeforeReplace", true).asBool();
}

void Config::updateReplaceMap(const std::map<std::string, std::string>& replaceMap)
{
	Value newReplaceMap{ValueType::arrayValue};
	for (const auto& element : replaceMap)
	{
		Value entry{ValueType::objectValue};
		entry["from"] = element.first;
		entry["to"] = element.second;
		newReplaceMap.append(entry);
	}

	_data["nameValidator"]["replaceMap"] = newReplaceMap;
	saveConfig(_filePath);
}

void Config::saveConfig(const std::string& filePath)
{
	std::ofstream file(filePath);
	if (file.is_open() == false)
	{
		std::cout << "Can't save config!" << std::endl;
		return;
	}
	file << _data.toStyledString();
	file.flush();
	file.close();
}









