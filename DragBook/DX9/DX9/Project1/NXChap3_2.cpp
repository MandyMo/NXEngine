
/**
*  File:      NXChap3_2.h
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	   2017_03_11
*  Purpose:   DX9 Bone test
*/

#include "NXChap3_2.h"
#include "../../../../engine/Render/NXDX9TextureManager.h"

class NX::NXChap3_2::Bone : public D3DXFRAME {
public:
	D3DXMATRIX			FinalMatrix;
};

class NX::NXChap3_2::BoneMesh : public D3DXMESHCONTAINER {

};

class NX::NXChap3_2::MeshLoader : public ID3DXAllocateHierarchy {
public:
	HRESULT __stdcall CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
		Bone * pBone = new Bone;
		NX::NXZeroMemory(pBone);
		if (Name) {
			pBone->Name = (LPSTR)new char[(strlen(Name) + 1)];
			strcpy(pBone->Name, Name);
		}
		*ppNewFrame = pBone;
		return S_OK;
	}

	HRESULT __stdcall CreateMeshContainer(LPCSTR Name,
		const D3DXMESHDATA *pMeshData,
		const D3DXMATERIAL *pMaterials,
		const D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		const DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer
	) {
		*ppNewMeshContainer = new BoneMesh;
		NX::NXZeroMemory(*ppNewMeshContainer);
		return S_OK;
	}

	HRESULT __stdcall DestroyFrame(LPD3DXFRAME pFrameToFree) {
		Bone *pBone = (Bone*)pFrameToFree;
		if (pBone) {
			delete pBone->Name;
		}
		delete pBone;
		return S_OK;
	}

	HRESULT __stdcall DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree) {
		delete pMeshContainerToFree;
		return S_OK;
	}
};

class NX::NXChap3_2::Mesh{
public:
	Mesh() { 
		m_pRootBone			=	NULL;
		m_pSphereMesh		=	NULL;
		D3DXCreateSphere(glb_GetD3DWindow()->GetD3D9Device(), 0.01f, 10, 10, &m_pSphereMesh, NULL);
		m_fAngle			= 0.f;
	}

	virtual ~Mesh() {
		NX::NXSafeRelease(m_pSphereMesh);
	}

public:
	void Render() {
		D3DXMATRIX identity, world, view, proj;
		D3DXMatrixRotationY(&identity, m_fAngle);
		D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0.0f, 1.5f, -3.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4.0f, (float)MAINFRAME_WIDTH / (float)MAINFRAME_HEIGHT, 1.0f, 1000.0f);

		glb_GetD3DDevice()->SetTransform(D3DTS_WORLD, &identity);
		glb_GetD3DDevice()->SetTransform(D3DTS_VIEW, &view);
		glb_GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &proj);

		RenderSkeleton(m_pRootBone, NULL, identity);
	}

	void Load(const std::string &strFilePath) {
		MeshLoader loader;
		D3DXLoadMeshHierarchyFromX(strFilePath.c_str(), 0, glb_GetD3DWindow()->GetD3D9Device(), &loader, NULL, (D3DXFRAME**)&m_pRootBone, NULL);
		D3DXMATRIX identity;
		D3DXMatrixIdentity(&identity);
		CaculateTransform(m_pRootBone, identity);
	}

	void CaculateTransform(Bone *root, D3DXMATRIX parentTransform) {
		if (!root) {
			return;
		}
		root->FinalMatrix		=	root->TransformationMatrix * parentTransform;
		CaculateTransform((Bone*)root->pFrameFirstChild, root->FinalMatrix);
		CaculateTransform((Bone*)root->pFrameSibling, parentTransform);
	}

	void RenderSkeleton(Bone * pCurrentBone, Bone *pParentBone, D3DXMATRIX WorldTransform) {
		if (!pCurrentBone) {
			return;
		}

		{//render bone
			if(pCurrentBone && pParentBone && pParentBone->Name != NULL && pCurrentBone->Name != NULL){
				D3DXMATRIX ViewProject = pCurrentBone->FinalMatrix * WorldTransform;
				glb_GetD3DWindow()->GetD3D9Device()->SetTransform(D3DTS_WORLD, &ViewProject);
				glb_GetD3DWindow()->GetD3D9Device()->SetRenderState(D3DRS_LIGHTING, true);
				m_pSphereMesh->DrawSubset(0);
				D3DXMATRIX Current	= pCurrentBone->FinalMatrix;
				D3DXMATRIX Parent	= pParentBone->FinalMatrix;
				Vertex v[2] = {Vertex(Current(3, 0), Current(3, 1),Current(3, 2), 0xffff0000), Vertex(Parent(3, 0), Parent(3, 1), Parent(3, 2), 0xff00ff00)};
				glb_GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
				glb_GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, false);
				glb_GetD3DWindow()->GetD3D9Device()->SetTransform(D3DTS_WORLD, &WorldTransform);
				glb_GetD3DDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 1, v, sizeof(Vertex));
			}
		}
		RenderSkeleton((Bone*)pCurrentBone->pFrameFirstChild, pCurrentBone, WorldTransform);
		RenderSkeleton((Bone*)pCurrentBone->pFrameSibling, pParentBone, WorldTransform);
	}
	void OnTick(NXUInt32	dwTime) {
		m_fAngle += dwTime * 0.001;
	}
private:
	Bone			*m_pRootBone;
	ID3DXMesh		*m_pSphereMesh;
	float			m_fAngle;
};

NX::NXChap3_2::NXChap3_2() {

}

NX::NXChap3_2::~NXChap3_2() {

}


void NX::NXChap3_2::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap3_2::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap3_2::Render() {
	m_pMesh->Render();
}

void NX::NXChap3_2::OnInitDX3Succeed() {
	m_pMesh = new Mesh();
	m_pMesh->Load("Resources/mesh3_1/soldier.x");
}

void NX::NXChap3_2::OnTick(NXUInt32 uDelta) {
	m_pMesh->OnTick(uDelta);
}