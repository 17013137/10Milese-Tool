#include "stdafx.h"
#include "Fire.h"
#include "GameInstance.h"

CFire::CFire(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CBlendObject(pGraphic_Device)
{
}

CFire::CFire(const CFire & rhs)
	: CBlendObject(rhs)
{
}

HRESULT CFire::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFire::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	_float3 Pos = *(_float3*)pArg;
	Pos.y += 1.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos);

	//m_fFrame = rand() % 32;

	

	return S_OK;
}

_bool CFire::Picking(_float3 * _pickpos)
{
	_float3	vOut;
	if (true == m_pVIBufferCom->Picking(m_pTransformCom, &vOut)) {
		D3DXVec3TransformCoord(&vOut, &vOut, &m_pTransformCom->Get_WorldMatrix());
		*_pickpos = vOut;
		return true;
	}

	return false;
}


void CFire::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance*	pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (rand()%100>97)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(m_Current_Level, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Effect_Action"), &m_Effect_Type)))
			return;
		
	}
	

	Safe_Release(pGameInstance);

}

void CFire::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	_float4x4		ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3		vScale = m_pTransformCom->Get_Scale();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0] * vScale.x);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0] * vScale.y);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0] * vScale.z);


	m_fFrame += 32.0f * fTimeDelta;

	if (m_fFrame >= 32.0f)
		m_fFrame = 0.f;

	Compute_CamDistance(m_pTransformCom);
	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CFire::Render()
{

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice((_uint)m_fFrame)))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CFire::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.3f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), STAGE_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), STAGE_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), STAGE_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), STAGE_SCENE, TEXT("Prototype_Component_Texture_Fire"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	//m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));

	return S_OK;
}

CFire * CFire::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFire*	pInstance = new CFire(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFire"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFire::Clone(void * pArg)
{
	CFire*	pInstance = new CFire(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFire"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFire::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
