#ifndef _DescCommand_H
#define _DescCommand_H

#include "Command.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <map>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <regex>
#include <ctime>
#include <utility>
#include <string>
#include "Functions/general.h"

class DescCommand : Command
{
	public:
		DescCommand();
		~DescCommand();
		void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
