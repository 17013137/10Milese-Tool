#include "stdafx.h"
#include "Tile.h"
#include "GameInstance.h"
#include "Transform.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CTile::CTile(const CTile & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTile::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))	
		return E_FAIL;

	return S_OK;
}

HRESULT CTile::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float4x4 temp;
	memcpy(temp, pArg, sizeof(_float4x4));
	ImgNum = (int)temp.m[0][3];
	temp.m[0][3] = 0;

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(temp.m[0][0], temp.m[0][1], temp.m[0][2]));
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(temp.m[1][0], temp.m[1][1], temp.m[1][2]));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(temp.m[2][0], temp.m[2][1], temp.m[2][2]));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(temp.m[3][0], temp.m[3][1], temp.m[3][2]));
	return S_OK;
}

void CTile::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CTile::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CTile::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;	

	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(ImgNum)))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	return S_OK;
}

_bool CTile::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}

HRESULT CTile::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), STAGE_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), STAGE_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), STAGE_SCENE, TEXT("Prototype_Component_VIBuffer_Tile"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), STAGE_SCENE, TEXT("Prototype_Component_Texture_Terrain"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CTile * CTile::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTile*	pInstance = new CTile(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTile::Clone(void * pArg)
{
	CTile*	pInstance = new CTile(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTile::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}
