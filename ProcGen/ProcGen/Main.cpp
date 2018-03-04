#include <cstdlib>
#include <ctime>
#include "TerrainGenerator.h"

int main() {
	srand(time(nullptr));
	TerrainGenerator::InitialiseNoise();
}
