#include "..\..\NXDX9Window.h"
#include "NXChap1.h"
#include "NXChap2.h"
#include "NXChap17_1.h"
#include "NXChap17_2.h"

int main() {
	NX::Window*	mainframe = new	NX::NXChap17_2();
	RECT	MainFrameRt = { 300, 200, MAINFRAME_WIDTH + 300, MAINFRAME_HEIGHT + 200 };
	mainframe->Create(WS_EX_WINDOWEDGE, (WS_VISIBLE | WS_TILED | WS_SYSMENU) & (~WS_SIZEBOX), _T("MainFramwClass"), NULL, MainFrameRt, NULL, NULL, NULL);
	mainframe->MessageLoop();
	delete	mainframe;
}
