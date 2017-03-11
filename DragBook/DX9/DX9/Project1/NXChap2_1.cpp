
/**
*  File:      NXChap2_1.h
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	   2017_03_08
*  Purpose:   DX9 X File test
*/

#include "NXChap2_1.h"
#include "../../NXDX9TextureManager.h"

static double m_angle = 0;

NX::NXChap2_1::NXChap2_1() {
	m_pEffect				=	NULL;
	BaseColorHandle			=	NULL;
	WorldMatrixHandle		=	NULL;
	ViewProjectHandle		=	NULL;
	LightPositionHandle		=	NULL;
	m_pXMesh				=	NULL;
	m_vTextures.clear();
}

NX::NXChap2_1::~NXChap2_1() {
	NX::NXSafeRelease(m_pEffect);
	NX::NXSafeRelease(m_pXMesh);
	m_vTextures.clear();
}


void NX::NXChap2_1::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap2_1::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap2_1::Render() {

	D3DXMATRIX identity, shadow;
	D3DXMatrixIdentity(&identity);

	//Set ground plane + light position
	D3DXPLANE ground(0.0f, 1.0f, 0.0f, 0.0f);
	D3DXVECTOR4 lightPos(-20.0f, 75.0f, -120.0f, 0.0f);

	//Create the shadow matrix
	D3DXMatrixShadow(&shadow, &lightPos, &ground);

	//Create Transformation Matrices
	D3DXMATRIX view, proj, world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(cos(m_angle) * 2.0f, 2.0f, sin(m_angle) * 2.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4.0f, (float)MAINFRAME_WIDTH / (float)MAINFRAME_HEIGHT, 0.1f, 100.0f);

	m_pEffect->SetMatrix(ViewProjectHandle, &(view * proj));




		//Render Soldier
		{
			m_pEffect->SetMatrix(WorldMatrixHandle, &identity);
			m_pEffect->SetVector(LightPositionHandle, &lightPos);
			D3DXHANDLE hTech = m_pEffect->GetTechniqueByName("Lighting");
			m_pEffect->SetTechnique(hTech);
			m_pEffect->Begin(NULL, NULL);
			m_pEffect->BeginPass(0);

			for(int i = 0; i < m_vTextures.size(); ++i){
				m_pEffect->SetTexture(BaseColorHandle, NXDX9TextureManager::Instance().GetTexture(m_vTextures[i]));
				m_pXMesh->DrawSubset(i);
			}

			m_pEffect->EndPass();
			m_pEffect->End();
		}

		//Render Shadow
		{
			m_pEffect->SetMatrix(WorldMatrixHandle, &shadow);
			m_pEffect->SetVector(LightPositionHandle, &lightPos);
			D3DXHANDLE hTech = m_pEffect->GetTechniqueByName("Shadow");
			m_pEffect->SetTechnique(hTech);
			m_pEffect->Begin(NULL, NULL);
			m_pEffect->BeginPass(0);

			for (int i = 0; i < m_vTextures.size(); ++i) {
				m_pEffect->SetTexture(BaseColorHandle, NXDX9TextureManager::Instance().GetTexture(m_vTextures[i]));
				m_pXMesh->DrawSubset(i);
			}

			m_pEffect->EndPass();
			m_pEffect->End();
		}
	
}

void NX::NXChap2_1::OnInitDX3Succeed() {
	ID3DXBuffer	*errorBuffer = NULL;
	HRESULT hr = 0;
	do{
		{//compile effective file
			hr = ::D3DXCreateEffectFromFile(GetD3D9Device(), "NXChap2_1_effect.hlsl", NULL, NULL, D3DXSHADER_DEBUG, NULL, &m_pEffect, &errorBuffer);
			if (errorBuffer != NULL) {
				glb_GetLog().logToConsole("create effect file %s", errorBuffer->GetBufferPointer());
				break;
			}
		}

		{//get handles
			BaseColorHandle		= m_pEffect->GetParameterByName(NULL, "BaseColor");
			WorldMatrixHandle	= m_pEffect->GetParameterByName(NULL, "WorldMatrix");
			ViewProjectHandle	= m_pEffect->GetParameterByName(NULL, "ViewProjectMatrix");
			LightPositionHandle = m_pEffect->GetParameterByName(NULL, "LightPosition");
		}

		{//load mesh & textures
			ID3DXBuffer * adjacencyBfr	= NULL;
			ID3DXBuffer * materialBfr	= NULL;
			DWORD		  noMaterials	= NULL;
			::D3DXLoadMeshFromX("Resources/meshes/soldier.x", D3DXMESH_MANAGED, GetD3D9Device(), &adjacencyBfr, &materialBfr, NULL, &noMaterials, &m_pXMesh);
			D3DXMATERIAL *mtrls = (D3DXMATERIAL*)materialBfr->GetBufferPointer();
			for (int i = 0; i < noMaterials; ++i) {
				m_vTextures.push_back(std::string("Resources/Meshes/") + mtrls[i].pTextureFilename);
			}
			m_pXMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)adjacencyBfr->GetBufferPointer(), NULL, NULL, NULL);
			NX::NXSafeRelease(adjacencyBfr);
			NX::NXSafeRelease(materialBfr);
		}
	}while(false);
}

void NX::NXChap2_1::OnTick(NXUInt32 uDelta) {
	m_angle += uDelta / 1000.f;
}
