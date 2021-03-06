
// Diffie-HillmanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Diffie-Hillman.h"
#include "Diffie-HillmanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDiffieHillmanDlg dialog



CDiffieHillmanDlg::CDiffieHillmanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIFFIEHILLMAN_DIALOG, pParent)
	, gPublic(0)
	, pPublic(0)
	, aPrivate(0)
	, bPrivate(0)
	, A(0)
	, B(0)
	, K1(0)
	, K2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiffieHillmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, gPublic);
	DDX_Text(pDX, IDC_EDIT2, pPublic);
	DDX_Text(pDX, IDC_EDIT3, aPrivate);
	DDX_Text(pDX, IDC_EDIT4, bPrivate);
	DDX_Text(pDX, IDC_EDIT5, A);
	DDX_Text(pDX, IDC_EDIT6, B);
	DDX_Text(pDX, IDC_EDIT7, K1);
	DDX_Text(pDX, IDC_EDIT8, K2);
}

BEGIN_MESSAGE_MAP(CDiffieHillmanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT3, &CDiffieHillmanDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiffieHillmanDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDiffieHillmanDlg message handlers

BOOL CDiffieHillmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiffieHillmanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDiffieHillmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiffieHillmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDiffieHillmanDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CDiffieHillmanDlg::OnBnClickedButton1()
{
	// TODO: Count A,B,K1,K2
	UpdateData(true);

	if (is_prime(pPublic)) {
		A = power_module(gPublic, aPrivate, pPublic);
		B = power_module(gPublic, bPrivate, pPublic);

		K1 = power_module(B, aPrivate, pPublic);
		K2 = power_module(A, bPrivate, pPublic);
	}
	else  IDC_STATIC_one.visible = true;

	UpdateData(false);
}


int CDiffieHillmanDlg::power_module(int base, int exp, int module)
{
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result = base * result % module;
	}
	return result;
}


bool CDiffieHillmanDlg::is_prime(int p)
{
	int bound = int(p/2);
	for (int i = 2; i < bound; i++) {
		if ((p%i) == 0) {
			return false;
		}
	}
	return true;
}
