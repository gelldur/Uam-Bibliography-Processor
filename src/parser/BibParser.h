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
	Bib parse(const char* bibBegin, const char* bibEnd);
};


