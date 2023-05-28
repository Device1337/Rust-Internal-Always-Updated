#include "sky.hpp"
#include "../rust base/utils/memory.hpp"
#include "../rust base/game/offsets.hpp"
#include <cmath>
#include "Glob.hpp"

namespace sky {
	void sky(rust::TOD_Sky SKY)
	{
		SKY.get_instance();
	}
}