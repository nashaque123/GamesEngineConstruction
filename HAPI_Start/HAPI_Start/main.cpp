#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

#include <time.h>
#include <stdlib.h>
#include "World.h"

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	srand((unsigned int)time(0));

	World world;

	world.Run();
}