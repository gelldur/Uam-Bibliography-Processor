//
// Created by Dawid Drozd aka Gelldur on 6/18/16.
//

#pragma once

#include <parser/model/Bib.h>
#include "Config.h"

class NameValidator
{
public:
	NameValidator(Config& config)
			: _config(config)
	{
	}

	void check(std::vector<Bib>& bibs);

private:
	Config& _config;
};


