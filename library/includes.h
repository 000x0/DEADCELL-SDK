#pragma once

using ulong_t = unsigned long;

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>
#include <cctype>
#include <random>
#include <array>
#include <utility>
#include <intrin.h>
#include <chrono>
#include <ctime>

#include "address/address.h"

#include "hash/hash.h"

#include "input/input.h"
#include "console/console.h"

#include "math/math.h"

#include "pe/types.h"
#include "pe/module/module.h"
#include "pe/pe.h"

#include "pe\image_dir.h"

#include "util/misc/misc.h"
#include "util/pattern/pattern.h"
#include "util/vmt/vmt.h"

#include "stack/stack.h"
