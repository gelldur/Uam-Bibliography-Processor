//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#pragma once

#include "model/KeyValue.h"
#include "model/Bib.h"

class BibParser
{
public:
	std::vector<Bib> parse(const std::string& text);

private:
	void parse(const std::string& text, Bib& bib);

	std::pair<size_t, std::string> extractBraces(const std::string& text, size_t offset);

	std::vector<KeyValue> extract(const std::string& text);

	bool isAsciiLetter(char letter);

	std::vector<std::string>& split(const std::string& text, char delim, std::vector<std::string>& elements);
	std::vector<std::string> split(const std::string& text, char delim);
};


