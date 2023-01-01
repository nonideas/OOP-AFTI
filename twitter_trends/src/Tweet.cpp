#include "Tweet.h"
#include "Parser.h"
#include <iostream>

using namespace std;

Tweet::Tweet(const std::time_t& ts, const std::vector<std::string>& hashtags) : ts(ts), hashtags(hashtags) {}

