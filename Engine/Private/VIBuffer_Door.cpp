#include "..\Public\VIBuffer_Door.h"



CVIBuffer_Door::CVIBuffer_Door(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Door::CVIBuffer_Door(const CVIBuffer_Door & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Door::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 20;
	m_iStride = sizeof(VTXOBJECTTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitives = 28;

	if (FAILED(Create_VertexBuffer()))
		return E_FAIL;

	m_pVertices = new VTXOBJECTTEX[m_iNumVertices];

	VTXOBJECTTEX*		pVertices = nullptr;
	
	m_pVB->Lock(0, 0/*m_iStride * m_iNumVertices*/, (void**)&pVertices, 0);

	/* 값을 바꾸고. */
	pVertices[0].vPosition = _float3(-0.5f, 1.f, 0.4f);
	pVertices[0].vColor = 0xffffffff;

	pVertices[1].vPosition = _float3(-0.5f, 0.8f, 0.4f);
	pVertices[1].vColor = 0xffffffff;

	pVertices[2].vPosition = _float3(-0.5f, 0.f, 0.4f);
	pVertices[2].vColor = 0xffffffff;

	pVertices[3].vPosition = _float3(-0.3f, 0.f, 0.4f);
	pVertices[3].vColor = 0xffffffff;

	pVertices[4].vPosition = _float3(-0.3f, 0.8f, 0.4f);
	pVertices[4].vColor = 0xffffffff;

	pVertices[5].vPosition = _float3(0.3f, 0.8f, 0.4f);
	pVertices[5].vColor = 0xffffffff;

	pVertices[6].vPosition = _float3(0.3f, 0.f, 0.4f);
	pVertices[6].vColor = 0xffffffff;

	pVertices[7].vPosition = _float3(0.5f, 0.f, 0.4f);
	pVertices[7].vColor = 0xffffffff;

	pVertices[8].vPosition = _float3(0.5f, 0.8f, 0.4f);
	pVertices[8].vColor = 0xffffffff;

	pVertices[9].vPosition = _float3(0.5f, 1.f, 0.4f);
	pVertices[9].vColor = 0xffffffff;
	
	pVertices[10].vPosition = _float3(-0.5f, 1.f, 0.5f);
	pVertices[10].vColor = 0xffbcbcbc;

	pVertices[11].vPosition = _float3(-0.5f, 0.8f, 0.5f);
	pVertices[11].vColor = 0xffbcbcbc;

	pVertices[12].vPosition = _float3(-0.5f, 0.f, 0.5f);
	pVertices[12].vColor = 0xffbcbcbc;

	pVertices[13].vPosition = _float3(-0.3f, 0.f, 0.5f);
	pVertices[13].vColor = 0xffbcbcbc;

	pVertices[14].vPosition = _float3(-0.3f, 0.8f, 0.5f);
	pVertices[14].vColor = 0xffbcbcbc;

	pVertices[15].vPosition = _float3(0.3f, 0.8f, 0.5f);
	pVertices[15].vColor = 0xffbcbcbc;

	pVertices[16].vPosition = _float3(0.3f, 0.f, 0.5f);
	pVertices[16].vColor = 0xffbcbcbc;

	pVertices[17].vPosition = _float3(0.5f, 0.f, 0.5f);
	pVertices[17].vColor = 0xffbcbcbc;

	pVertices[18].vPosition = _float3(0.5f, 0.8f, 0.5f);
	pVertices[18].vColor = 0xffbcbcbc;

	pVertices[19].vPosition = _float3(0.5f, 1.f, 0.5f);
	pVertices[19].vColor = 0xffbcbcbc;

	memcpy(m_pVertices, pVertices, sizeof(VTXOBJECTTEX) * m_iNumVertices);

	m_pVB->Unlock();

	m_iPrimitiveIndicesSize = sizeof(FACELISTINDICES16);
	m_eFormat = D3DFMT_INDEX16;

	m_pIndices = new FACELISTINDICES16[m_iNumPrimitives];
	ZeroMemory(m_pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);

	if (FAILED(Create_IndexBuffer()))
		return E_FAIL;

	FACELISTINDICES16*		pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 9;
	pIndices[0]._2 = 8;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 8;
	pIndices[1]._2 = 1;

	pIndices[2]._0 = 1;
	pIndices[2]._1 = 4;
	pIndices[2]._2 = 3;

	pIndices[3]._0 = 1;
	pIndices[3]._1 = 3;
	pIndices[3]._2 = 2;

	pIndices[4]._0 = 5;
	pIndices[4]._1 = 8;
	pIndices[4]._2 = 7;

	pIndices[5]._0 = 5;
	pIndices[5]._1 = 7;
	pIndices[5]._2 = 6;

	pIndices[6]._0 = 10;
	pIndices[6]._1 = 0;
	pIndices[6]._2 = 2;

	pIndices[7]._0 = 10;
	pIndices[7]._1 = 2;
	pIndices[7]._2 = 12;

	pIndices[8]._0 = 2;
	pIndices[8]._1 = 3;
	pIndices[8]._2 = 13;

	pIndices[9]._0 = 2;
	pIndices[9]._1 = 13;
	pIndices[9]._2 = 12;

	pIndices[10]._0 = 4;
	pIndices[10]._1 = 14;
	pIndices[10]._2 = 13;

	pIndices[11]._0 = 4;
	pIndices[11]._1 = 13;
	pIndices[11]._2 = 3;
					 
	pIndices[12]._0 = 4;
	pIndices[12]._1 = 5;
	pIndices[12]._2 =15;
					 
	pIndices[13]._0 = 4;
	pIndices[13]._1 = 15;
	pIndices[13]._2 = 14;
					 
	pIndices[14]._0 = 15;
	pIndices[14]._1 = 5;
	pIndices[14]._2 = 6;
					 
	pIndices[15]._0 = 15;
	pIndices[15]._1 = 6;
	pIndices[15]._2 = 16;
					 
	pIndices[16]._0 = 6;
	pIndices[16]._1 = 7;
	pIndices[16]._2 = 17;
					 
	pIndices[17]._0 = 6;
	pIndices[17]._1 = 17;
	pIndices[17]._2 = 16;
					 
	pIndices[18]._0 = 9;
	pIndices[18]._1 = 19;
	pIndices[18]._2 = 17;
					 
	pIndices[19]._0 = 9;
	pIndices[19]._1 = 17;
	pIndices[19]._2 = 7;

	pIndices[20]._0 = 10;
	pIndices[20]._1 = 19;
	pIndices[20]._2 = 9;
					 
	pIndices[21]._0 = 10;
	pIndices[21]._1 = 9;
	pIndices[21]._2 = 0;
					 
	pIndices[22]._0 = 19;
	pIndices[22]._1 = 10;
	pIndices[22]._2 = 11;
					 
	pIndices[23]._0 = 19;
	pIndices[23]._1 = 11;
	pIndices[23]._2 = 18;
					 
	pIndices[24]._0 = 14;
	pIndices[24]._1 = 11;
	pIndices[24]._2 = 12;
					 
	pIndices[25]._0 = 14;
	pIndices[25]._1 = 12;
	pIndices[25]._2 = 13;
					 
	pIndices[26]._0 = 18;
	pIndices[26]._1 = 15;
	pIndices[26]._2 = 16;
					 
	pIndices[27]._0 = 18;
	pIndices[27]._1 = 16;
	pIndices[27]._2 = 17;

	memcpy(m_pIndices, pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitives);


	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Door::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Door * CVIBuffer_Door::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Door*	pInstance = new CVIBuffer_Door(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Door"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Door::Clone(void * pArg)
{
	CVIBuffer_Door*	pInstance = new CVIBuffer_Door(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Door"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Door::Free()
{
	__super::Free();
}
