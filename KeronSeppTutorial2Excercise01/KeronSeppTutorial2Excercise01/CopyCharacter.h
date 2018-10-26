#pragma once
#include "Prop.h";
#include <string.h>

class CopyCharacter
{

public:
	CopyCharacter(std::string _name);
	std::string name;
	Prop* prop;

	~CopyCharacter();
};

