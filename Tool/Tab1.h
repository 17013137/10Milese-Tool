#pragma once
#include "afxwin.h"


// CTab1 대화 상자입니다.

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_VertexX;
	int m_VertexZ;
	afx_msg void VertexCnt_Button();
	virtual BOOL OnInitDialog();
	afx_msg void Tile_ListBox();
	CListBox m_Tile_Listbox;
	CListBox m_Scene_ListBox;
	afx_msg void OnLbnSelchangeList2();
	afx_msg void Tile_Delete_Button();
	afx_msg void Tile_Save_Button();
	afx_msg void Load_Save_Button();
	CListBox m_Blend_ListBox;
	CListBox m_Scene_Blend;
	CListBox m_Blend_Texture_ListBox;
};
