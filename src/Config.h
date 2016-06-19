//
// Created by Dawid Drozd aka Gelldur on 6/19/16.
//

#pragma once

#include <string>
#include <json/json.h>

class Config
{
public:
	Config(const std::string& configFile);

	const Json::Value& getConfig() const
	{
		return _data;
	}

	std::string getCrossrefType(const std::string& bibType) const;

	bool isReplaceExistingDoi() const;
	bool isCrossrefEnabled() const;
	bool isNameValidatorEnabled() const;
	bool isAskBeforeReplace() const;

	std::map<std::string, std::string> getReplaceMap();
	void updateReplaceMap(const std::map<std::string, std::string>& replaceMap);

private:
	std::string _filePath;
	Json::Value _data;

	const Json::Value getCrossref() const;
	const Json::Value getNameValidator() const;

	void saveConfig(const std::string& filePath);
};


