#include "..\..\NXDX9Window.h"
#include "NXChap1.h"
#include "NXChap2.h"
#include "NXChap17_1.h"
#include "NXChap17_2.h"
#include "NXChap17_3.h"
#include "NXChap2_1.h"
#include "NXChap3_1.h"
#include "NXChap3_2.h"
#include "NXChap4_1.h"
#include "NXEngineDemo.h"
#include "math/NXAlgorithm.h"
#include "math/NXMatrix.h"
#include "entity/NXTerrain.h"

int main() {
	srand(time(NULL));
	NX::Window*	mainframe = new	NX::NXEngineDemo();
	RECT	MainFrameRt = { 300, 200, MAINFRAME_WIDTH + 300, MAINFRAME_HEIGHT + 200 };
	mainframe->Create(WS_EX_WINDOWEDGE, (WS_VISIBLE | WS_TILED | WS_SYSMENU) & (~WS_SIZEBOX), _T("MainFramwClass"), _T("NXEngine"), MainFrameRt, NULL, NULL, NULL);
	mainframe->MessageLoop();


	delete	mainframe;
}
