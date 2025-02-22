#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_XRect final : public CVIBuffer
{
protected:
	explicit CVIBuffer_XRect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer_XRect(const CVIBuffer_XRect& rhs);
	virtual ~CVIBuffer_XRect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:

	static CVIBuffer_XRect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END