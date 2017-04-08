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
#include "math/NXAlgorithm.h"
#include "math/NXMatrix.h"

int main() {
	srand(time(NULL));
	float radian = NX::DG2RD(rand());
	float fov = NX::DG2RD(75);
	float asp = 1000;
	float axis[3] = {rand(), rand(), rand()};
	float zf = 10000;
	float zn = 0.0001;
	D3DXMATRIX m1;
	//D3DXMatrixRotationAxis(&m1, &D3DXVECTOR3(axis[0], axis[1], axis[2]), radian);
	//NX::float4X4 m2 = GetTransposed(NX::GetMatrixRotateByAix(NX::float3(axis), radian));
// 	D3DXMatrixPerspectiveFovLH(&m1, fov, asp, zn, zf);
// 	NX::float4X4 m2 = GetTransposed(NX::GetPerspectiveMatrix<float>(75, asp, zn, zf));

	D3DXMatrixOrthoLH(&m1, fov, asp, zn, zf);
	NX::float4X4 m2 = GetTransposed(NX::GetOrthogonalMatrix<float>(75, asp, zn, zf));
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (!NX::Equalfloat(m1.m[i][j], m2[i][j])) {
				cout << "not equal" << endl;
			}
		}
	}

	cout << "end of compare" << endl;
	NX::Window*	mainframe = new	NX::NXChap4_1();
	RECT	MainFrameRt = { 300, 200, MAINFRAME_WIDTH + 300, MAINFRAME_HEIGHT + 200 };
	mainframe->Create(WS_EX_WINDOWEDGE, (WS_VISIBLE | WS_TILED | WS_SYSMENU) & (~WS_SIZEBOX), _T("MainFramwClass"), _T("DX Shadow"), MainFrameRt, NULL, NULL, NULL);
	mainframe->MessageLoop();


	delete	mainframe;
}
