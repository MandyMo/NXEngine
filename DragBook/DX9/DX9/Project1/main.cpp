#include "NXEngineDemo.h"

int main() {
	srand(time(NULL));
	NX::Window*	mainframe = new	NX::NXEngineDemo();
	RECT	MainFrameRt = { 300, 200, MAINFRAME_WIDTH + 300, MAINFRAME_HEIGHT + 200 };
	mainframe->Create(WS_EX_WINDOWEDGE, (WS_VISIBLE | WS_TILED | WS_SYSMENU) & (~WS_SIZEBOX), _T("MainFramwClass"), _T("NXEngine"), MainFrameRt, NULL, NULL, NULL);
	mainframe->MessageLoop();
	delete	mainframe;
}
