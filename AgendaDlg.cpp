
// AgendaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgendaPH.h"
#include "AgendaDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
CAgendaDlg::~CAgendaDlg()
{

}
void CAgendaDlg::ShowControls(bool show)
{
	TreeCtrl.ShowWindow(show);
	listCtrl.ShowWindow(show);
	bSearch.ShowWindow(show);
	bEdit.ShowWindow(show);
	bDelete.ShowWindow(show);
	bNew.ShowWindow(show);
	bClosePb.ShowWindow(show);
	bDeletePb.ShowWindow(show);
	bSavePb.ShowWindow(show);
	bDetails.ShowWindow(show);
}

void CAgendaDlg::InitTree()
{
	TVINSERTSTRUCT agenda;
	agenda.hParent = NULL;
	agenda.hInsertAfter = NULL;
	agenda.item.mask = TVIF_TEXT;
	
	agenda.item.pszText = _T("Agenda");
	TreeCtrl.EditLabel(Agenda);
	Agenda = TreeCtrl.InsertItem(&agenda);
	Acq = TreeCtrl.InsertItem(TVIF_TEXT, "Acquaintances", 0, 0, 0, 0, 0, Agenda, NULL);
	Col = TreeCtrl.InsertItem(TVIF_TEXT, "Colleagues", 0, 0, 0, 0, 0, Agenda, NULL);
	Fr = TreeCtrl.InsertItem(TVIF_TEXT, "Friends", 0, 0, 0, 0, 0, Agenda, NULL);
	char ch = 'A', *c;
	c = new char[2];
	//for(int i = 0; i < 26; i++)
	//{
	//	c[0] = ch;
	//	c[1] = '\0';
	//	TreeCtrl.InsertItem(c, acq, TVI_SORT);
	//	TreeCtrl.InsertItem(c, col, TVI_SORT);
	//	TreeCtrl.InsertItem(c, fr, TVI_SORT);
	//	ch++;
	//}
}

void CAgendaDlg::InitList()
{
	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.pszText = "ID";
	col.cx = 30;
	listCtrl.InsertColumn(0, &col);
	col.cx = 100;
	col.pszText = "First Name";
	listCtrl.InsertColumn(1, &col);
	col.pszText = "Last Name";
	listCtrl.InsertColumn(2, &col);
	col.pszText = "Phone Number";
	listCtrl.InsertColumn(3, &col);
	col.pszText = "Occupation";
	col.cx = 70;
	listCtrl.InsertColumn(4, &col);
	col.pszText = "Age";
	col.cx = 45;
	listCtrl.InsertColumn(5, &col);
	col.pszText = "Address";
	col.cx = 120;
	listCtrl.InsertColumn(6, &col);
	col.pszText = "Email";
	col.cx = 110;
	listCtrl.InsertColumn(7, &col);
	col.pszText = "Type";
	col.cx = 90;
	listCtrl.InsertColumn(8, &col);
	
	
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_HELP_ABOUT, &CAboutDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CAgendaDlg dialog


CAgendaDlg::CAgendaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgendaDlg::IDD, pParent)
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//p = &Phonebook::getInstance();
}

void CAgendaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, TreeCtrl);
	DDX_Control(pDX, IDC_LIST1, listCtrl);
	DDX_Control(pDX, IDC_BTN_SEARCH, bSearch);
	DDX_Control(pDX, IDC_BTN_EDIT_CONTACT, bEdit);
	DDX_Control(pDX, IDC_BTN_DELETE_CONTACT, bDelete);
	DDX_Control(pDX, IDC_NEWCONTACT, bNew);
	DDX_Control(pDX, IDC_BTN_CLOSEPB, bClosePb);
	DDX_Control(pDX, IDC_BUTTON6, bSavePb);
	DDX_Control(pDX, IDC_BUTTON7, bDeletePb);
	//DDX_Control(pDX, IDC_BUTTON8, bDetails);
}

BEGIN_MESSAGE_MAP(CAgendaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CAgendaDlg::OnTcnSelchangeTab1)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CAgendaDlg::OnTcnSelchangeTab2)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CAgendaDlg::OnTvnSelchangedTree1)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CAgendaDlg::OnLvnItemchangedList1)
ON_BN_CLICKED(IDC_BTN_SEARCH, &CAgendaDlg::SearchContact)
ON_MESSAGE(SHOW_WINDOW, &CAgendaDlg::OnShowWnd)
ON_MESSAGE(SEARCH, &CAgendaDlg::Search)
ON_BN_CLICKED(IDC_BTN_DELETE_CONTACT, &CAgendaDlg::DeleteContact)
ON_BN_CLICKED(IDC_BTN_CLOSEPB, &CAgendaDlg::ClosePhoneBook)
ON_BN_CLICKED(IDC_BUTTON8, &CAgendaDlg::OnBnClickedButton8)
ON_BN_CLICKED(IDC_NEWCONTACT, &CAgendaDlg::AddNewContact)
ON_BN_CLICKED(IDC_BTN_EDIT_CONTACT, &CAgendaDlg::EditContact)
ON_COMMAND(ID_FILE_NEWPHONEBOOK, &CAgendaDlg::OnFileNewphonebook)
ON_COMMAND(ID_FILE_NEWCONTACT32798, &CAgendaDlg::OnFileNewcontact32798)
ON_COMMAND(ID_FILE_EXIT32795, &CAgendaDlg::OnFileExit32795)
ON_COMMAND(ID_EDIT_DELETEPHONEBOOK, &CAgendaDlg::DeletePhoneBook)
ON_WM_CLOSE()
ON_COMMAND(ID_EDIT_DELETECONTACT, &CAgendaDlg::DeleteContact)
ON_COMMAND(ID_EDIT_EDITCONTACT, &CAgendaDlg::OnEditContact)
ON_BN_CLICKED(IDC_BUTTON6, &CAgendaDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON7, &CAgendaDlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_RADIO1, &CAgendaDlg::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &CAgendaDlg::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_RADIO3, &CAgendaDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()

LRESULT CAgendaDlg::Search(UINT wParam, LONG lParam)
{
	LRESULT x = NULL;
	LoadList("this", manager->detailsDlg->p->search(info->attribute, info->text, "all"));
	return x;
}

LRESULT CAgendaDlg::OnShowWnd(UINT wParam, LONG lParam)
{
	LRESULT x = NULL;
	ShowControls(0);
	ShowControls(1);
	manager->Hide = 1;
	OpenPb();
	TVINSERTSTRUCT agenda;
	agenda.hParent = NULL;
	agenda.hInsertAfter = NULL;
	agenda.item.mask = TVIF_TEXT;
	agenda.item.pszText = manager->OpenedPb;
	deque<Contact> list;
	LoadList("all", list);
	//MessageBox(manager->OpenedPb, "pb name", 0);
	TreeCtrl.SetItemText(Agenda, manager->OpenedPb);
	return x;
}
// CAgendaDlg message handlers

BOOL CAgendaDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	hAccelerators = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// TODO: Add extra initialization here
	InitTree();
	InitList();
	info = new InfoDlg();
	info->Create(IDD_DIALOG1, this);
	manager = new PbManager();
	manager->Create(IDD_MANAGEDIALOG, this);
	manager->ShowWindow(1);
	manager->InitCbList();
	info->ModifyStyleEx(0, WS_EX_LAYERED, 0);
	info->tSlider.SetRange(0, 255, 0);
	CMenu menu1;
	menu1.LoadMenuA(IDR_MENU1);
	SetMenu(&menu1);
	HICON hSearch = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	HICON hEdit = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2));
	HICON hDelete = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3));
	HICON hNew = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON4));
	HICON hClear = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5));
	HICON hClose = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON7));
	//HICON hSave = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON8));
	HICON hDeletePb = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON9));
	
	DWORD error = GetLastError();
//	char err[100];
	//_itoa_s(error, err, 10);
	//MessageBox(err, err, 0);
	bClosePb.SetIcon(hClose);
	//bSavePb.SetIcon(hSave);
	bDeletePb.SetIcon(hDeletePb);
	bSearch.SetIcon(hSearch);
	bEdit.SetIcon(hEdit);
	bDelete.SetIcon(hDelete);
	bNew.SetIcon(hNew);
	info->bClear.SetIcon(hClear);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAgendaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAgendaDlg::OpenPb()
{
	//int item;
	string file;
	Phonebook *p = &manager->detailsDlg->p->getInstance();
	if(!p->loadPhonebook())
		MessageBox("Error at loading contacts!!", 0, 0);
	

}

void CAgendaDlg::OnPaint()
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
HCURSOR CAgendaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAgendaDlg::LoadList(char *type, deque<Contact> list)
{
	int item = 0;
	Phonebook *p = manager->detailsDlg->p;
	if(_stricmp(type, "this"))
		list = p->getContacts(p->ContactList, type);
	if(listCtrl.DeleteAllItems() == 0)
		MessageBox("error emptying list", 0, 0);
	cout<<"\nlist items count="<<listCtrl.GetItemCount();
	cout<<"\ndeque items count="<<list.size()<<endl;
	char tmp[5]; //tmp array of chars for converting from int to char*
	for(int i = 0; i < (int) list.size(); i++)
	{
		int id = list[i].getID();
		if(id >= 0)
		{
			_itoa_s(id, tmp, 10);
			item = listCtrl.InsertItem(i, tmp);
		}
		listCtrl.SetItemText(item, 1, list[i].getFirstName().c_str());
		listCtrl.SetItemText(item, 2, list[i].getLastName().c_str());
		listCtrl.SetItemText(item, 3, list[i].getPhoneNumber().c_str());
		listCtrl.SetItemText(item, 4, list[i].getOccupation().c_str());
		int age =list[i].getAge();
		if(age)
		{
			_itoa_s(age, tmp, 10);
			listCtrl.SetItemText(item, 5, tmp);
		}
		listCtrl.SetItemText(item, 6, list[i].getHomeAddress().c_str());
		listCtrl.SetItemText(item, 7, list[i].getEmailAddress().c_str());
		listCtrl.SetItemText(item, 8, list[i].getContactType().c_str());
		
	}

}

void CAgendaDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM h = TreeCtrl.GetSelectedItem();
	deque<Contact> list;
	if(h == Agenda)
		LoadList("all", list);
	else if(h == Acq)
		LoadList("acquaintance", list);
	else if(h == Col)
		LoadList("colleague", list);
	else if(h == Fr)
		LoadList("friend", list);
	*pResult = 0;
}


void CAgendaDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void CAgendaDlg::SearchContact()
{
	// TODO: Add your control notification handler code here
	info->Show = !info->Show;
	info->tSlider.SetPos(230);
	info->SetLayeredWindowAttributes(0xFF00FF,230, LWA_ALPHA);
	info->ShowWindow(info->Show);	
}


void CAgendaDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}





int CAgendaDlg::GetSelectedContact()
{
	int sel = listCtrl.GetSelectionMark();
	if(sel == -1)
		return -1;
	char data[1024];
	
	Phonebook *p = manager->detailsDlg->p;
	cout<<"sel="<<sel<<endl;
	string str[10];
	listCtrl.GetItemText(sel, 0, data, 1024); //first name
	str[0] = data;
	cout<<"sel name="<<data<<endl;
	listCtrl.GetItemText(sel, 1, data, 1024); //last name
	str[1] = data;
	listCtrl.GetItemText(sel, 2, data, 1024); //phone number
	str[2] = data;
	listCtrl.GetItemText(sel, 3, data, 1024); //occupation
	str[3] = data;
	listCtrl.GetItemText(sel, 4, data, 1024); //age
	str[4] = data;
	int age;
	age = atoi(data);
	listCtrl.GetItemText(sel, 5, data, 1024); //address
	str[5] = data;
	listCtrl.GetItemText(sel, 6, data, 1024); //email
	str[6] = data;
	listCtrl.GetItemText(sel, 7, data, 1024);
	str[7] = data;
	cout<<"contact1 fn:"<<str[0]<<endl;
	for(int i = 0; i < (int) p->ContactList.size(); i++)
	{
		if( p->ContactList[i].getFirstName().compare(str[0]) == 0 &&
			//p->ContactList[i].getContactType().compare((str[0]) == 0 &&
			p->ContactList[i].getLastName().compare(str[1]) == 0 &&
			//p->ContactList[i].getGender().compare(str[0]) == 0 &&
			//p->ContactList[i].getBirthDate().toString().compare(p->ContactList[sel].getBirthDate().toString()) == 0 &&
			p->ContactList[i].getAge() == age &&
			p->ContactList[i].getPhoneNumber().compare(str[2]) == 0 &&
			p->ContactList[i].getHomeAddress().compare(str[5]) == 0 &&
			p->ContactList[i].getEmailAddress().compare(str[6]) == 0
		)
		return i;
	}
	return sel;
}

void CAgendaDlg::DeleteContact()
{
	// TODO: Add your control notification handler code here
	Phonebook *p = manager->detailsDlg->p;
	int sel = listCtrl.GetSelectionMark();
	Iterator *it = p->createIterator();
///	cout<<"age="<<it->currentItem().getFirstName()<<endl;
	CString cStr;
	cStr = listCtrl.GetItemText(sel, 0);
	int i = atoi(cStr.GetBuffer());
	//int i = GetSelectedContact();
	if(i == -1)
		MessageBox("invalid index", 0, 0);
	else
	{
		if(p->ContactDB->openDB())
		try
		{
		
			char Query[256];
			sprintf(Query, "DELETE FROM %s WHERE Id=%s;", manager->detailsDlg->p->getPbName().c_str(), cStr.GetBuffer());
			manager->detailsDlg->p->ContactDB->query(Query);
			it->first();
			while(it->currentItem()->getID() != i)
				it->next();
			p->ContactList.erase(p->ContactList.begin() + it->getIndex());
			listCtrl.DeleteItem(sel);
			p->ContactDB->close();
			manager->detailsDlg->p->setChanged(true);
		}
		catch(string error)
		{
			MessageBox(error.c_str(), "Exception caught when deleting contact", MB_ICONWARNING);
		}
		else
			MessageBox("Can't open database", 0, MB_ICONWARNING);
		
	}
	
}


BOOL CAgendaDlg::PreTranslateMessage(MSG* pMsg)
{
	// utilizare acceleratori
	if(TranslateAccelerator(m_hWnd, hAccelerators, pMsg))
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CAgendaDlg::ClosePhoneBook()
{
	// TODO: Add your control notification handler code here
	if(manager->detailsDlg->p->isChanged())
	{
		if(MessageBox("Do you want to save the changes made to this phone book?", "Save", MB_ICONQUESTION | MB_YESNO) == IDYES)
			manager->detailsDlg->p->savePhonebook(1);
	}
	else
		manager->detailsDlg->p->savePhonebook(0);
	manager->detailsDlg->p->setChanged(false);
	if(listCtrl.DeleteAllItems() == 0)
		MessageBox("Error deleting items", "ERROR", MB_ICONERROR);
	cout<<"deleted\n";
	ShowControls(0);
	manager->ShowWindow(1);
	
}


BOOL CAgendaDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	/*if( MessageBox("Do you want to save the Phone Book?", "Save", MB_ICONQUESTION | MB_YESNO) == IDYES)
		manager->detailsDlg->p->savePhonebook(1);
	else manager->detailsDlg->p->savePhonebook(0);*/
	return CDialogEx::DestroyWindow();
}


void CAgendaDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	int i = this->GetSelectedContact();
	manager->detailsDlg->contact = i;
	manager->detailsDlg->mode = ADD_CONTACT;
	manager->detailsDlg->DoModal();
}


void CAgendaDlg::AddNewContact()
{
	// TODO: Add your control notification handler code here
	manager->detailsDlg->mode = ADD_CONTACT;
	if(manager->detailsDlg->DoModal() == IDOK)
	{
		manager->detailsDlg->p->setChanged(true);
		deque<Contact> List;
		LoadList("all", List);
	}

}


void CAgendaDlg::EditContact()
{
	// TODO: Add your control notification handler code here
	
	int sel = GetSelectedContact();
	if(sel == -1)
		MessageBox("First select a contact!", "ERROR", MB_ICONWARNING);
	else
	{
		CString str = listCtrl.GetItemText(sel, 0);
		manager->detailsDlg->ID = atoi(str.GetBuffer());
		manager->detailsDlg->mode = EDIT_CONTACT;
		manager->detailsDlg->contact = sel;
		if(manager->detailsDlg->DoModal() == IDOK)
		{
			manager->detailsDlg->p->setChanged(true);
			deque<Contact> List;
			LoadList("all", List);
		}
	}
}


void CAgendaDlg::OnFileNewphonebook()
{
	manager->OnBnClickedButton1();
	// TODO: Add your command handler code here
}


void CAgendaDlg::OnFileNewcontact32798()
{
	this->AddNewContact();
	// TODO: Add your command handler code here
}


void CAgendaDlg::OnFileExit32795()
{
	// TODO: Add your command handler code here
	this->CloseWindow();
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


void CAgendaDlg::DeletePhoneBook()
{
	// TODO: Add your command handler code here
	manager->DeletePhoneBook();
	ShowControls(0);
	manager->ShowWindow(1);
}


void CAgendaDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(manager->detailsDlg->p->isChanged())
	{
		if(MessageBox("Do you want to save the changes made to this phone book before you exit?", "Save", MB_ICONQUESTION | MB_YESNO) == IDYES)
			manager->detailsDlg->p->savePhonebook(1);
	}
	else
		manager->detailsDlg->p->savePhonebook(0);
	CDialogEx::OnClose();
}


//void CAgendaDlg::DeleteContact()
//{
//	// TODO: Add your command handler code here
//}


void CAgendaDlg::OnEditContact()
{
	// TODO: Add your command handler code here
	this->EditContact();
}


void CAgendaDlg::OnBnClickedButton6()
{
	manager->detailsDlg->p->Sort(SortType);
	deque<Contact> List;
	listCtrl.DeleteAllItems();
	LoadList("all", List);
	// TODO: Add your control notification handler code here
}


void CAgendaDlg::OnBnClickedButton7()
{
	manager->DeletePhoneBook();
	// TODO: Add your control notification handler code here
}


void CAboutDlg::OnHelpAbout()
{
	MessageBox("Phone Book Created by Bujdea Bogdan-Costinel", "3A", MB_ICONINFORMATION);
	// TODO: Add your command handler code here
}


void CAgendaDlg::OnBnClickedRadio1()
{
	SortType = SORT_BY_FIRST_NAME;
	
	// TODO: Add your control notification handler code here
}


void CAgendaDlg::OnBnClickedRadio2()
{
	SortType = SORT_BY_LAST_NAME;
	
	// TODO: Add your control notification handler code here
}


void CAgendaDlg::OnBnClickedRadio3()
{
	SortType = SORT_BY_ID;
	
	// TODO: Add your control notification handler code here
}
