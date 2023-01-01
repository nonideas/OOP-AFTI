#pragma once
#include "User.h"
#include <unordered_set>

namespace UserTrend {
	double calculate_user_trend(const std::unordered_set<std::string>& top_n, const User& user);
}
