#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Crystal/Core/Log.h"
#include "Crystal/Debug/Instrumentor.h"

#ifdef CR_PLATFORM_WINDOWS
	#include <Windows.h>
#endif