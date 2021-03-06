
// Diffie-HillmanDlg.h : header file
//

#pragma once


// CDiffieHillmanDlg dialog
class CDiffieHillmanDlg : public CDialogEx
{
// Construction
public:
	CDiffieHillmanDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIFFIEHILLMAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int gPublic;
	int pPublic;
	afx_msg void OnEnChangeEdit3();
	int aPrivate;
	int bPrivate;
	int A;
	int B;
	int K1;
	int K2;
	afx_msg void OnBnClickedButton1();
	int power_module(int base, int exp, int module);
	bool is_prime(int p);
};
