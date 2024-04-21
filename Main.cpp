#include "MarsStation.h"

int main()
{
	MarsStation *marsStation = new MarsStation;
	marsStation->run();

	delete marsStation;

	return 0;
}
