// PbDetails.cpp : implementation file
//

#include "stdafx.h"
#include "AgendaPH.h"
#include "PbDetails.h"
#include "afxdialogex.h"


// PbDetails dialog

IMPLEMENT_DYNAMIC(PbDetails, CDialogEx)

PbDetails::PbDetails(CWnd* pParent /*=NULL*/)
	: CDialogEx(PbDetails::IDD, pParent), ini("Settings.ini", "Settings")
{
	CString temp = (LPCTSTR) ini.GetIniPath().c_str(); // Force CString to make a copy
	cout<<"ini path="<<ini.GetIniPath()<<endl;
	char path[2048];
	picLoaded = 0;
	::GetCurrentDirectoryA(sizeof(path) - 1, path);
	photoDir = path;
	cout<<"photo dir="<<photoDir<<endl;
	p = &Phonebook::getInstance();
	mode = ADD_PHONEBOOK;
}

PbDetails::~PbDetails()
{
}

void PbDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, bBrowse);
	DDX_Control(pDX, IDC_PICTURE, mPic);
	DDX_Control(pDX, IDC_BUTTON2, bSave);
	DDX_Control(pDX, IDC_BUTTON1, bClear);
	DDX_Control(pDX, IDC_BUTTON4, bCancel);
	DDX_Control(pDX, IDC_EDIT1, eFirstName);
	DDX_Control(pDX, IDC_EDIT2, eLastName);
	DDX_Control(pDX, IDC_EDIT3, ePhoneNumber);
	DDX_Control(pDX, IDC_EDIT4, eOccupation);
	DDX_Control(pDX, IDC_EDIT5, eAge);
	DDX_Control(pDX, IDC_EDIT6, eHomeAddress);
	DDX_Control(pDX, IDC_EDIT7, eEmail);
	DDX_Control(pDX, IDC_EDIT8, eBirthDate);
	DDX_Control(pDX, IDC_EDIT9, ePbName);
	DDX_Control(pDX, IDC_COMBO1, cbType);
}


BEGIN_MESSAGE_MAP(PbDetails, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &PbDetails::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &PbDetails::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &PbDetails::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &PbDetails::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &PbDetails::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &PbDetails::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT9, &PbDetails::OnEnChangeEdit9)
END_MESSAGE_MAP()


// PbDetails message handlers


//browse
void PbDetails::OnBnClickedButton3() 
{
	// TODO: Add your control notification handler code here
	CString name;
	char fileName[1024];
	char Filter[] = { "BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg||" };
	CFileDialog FileDlg(TRUE, ".txt", NULL, 0, Filter, 0, 0, 1);
	if(FileDlg.DoModal() == IDOK)
	{
		name = FileDlg.GetFileName();
		cout<<"\nsizeof filename="<<sizeof(fileName)<<endl;
		strcpy_s(fileName, name.GetBuffer());
		photoName = name.GetBuffer();
		name = FileDlg.GetFolderPath();
		name.Append("\\");
		name.Append(fileName);
	}
	strcpy_s(fileName,  name.GetBuffer());	
	if(mPic.LoadFromFile(name) == 0)
	{
		MessageBox("Can't open this photo", "ERROR", MB_ICONERROR);
		photoName = "";
	}
	else
		picName = name;
	picLoaded = 1;

} //browse

int PbDetails::ChangeContact()
{
	char tmp[1024];
	string details[10];
	ePbName.GetWindowTextA(tmp, 256);
	details[0] = tmp;
	eFirstName.GetWindowTextA(tmp, 256);
	details[1] = tmp;
	eLastName.GetWindowTextA(tmp, 256);
	details[2] = tmp;
	ePhoneNumber.GetWindowTextA(tmp, 256);
	details[3] = tmp;
	eAge.GetWindowTextA(tmp, 256);
	details[4] = "";
	details[5] = tmp;
	eEmail.GetWindowTextA(tmp, 256);
	details[6] = tmp;
	eOccupation.GetWindowTextA(tmp, 256);
	details[7] = tmp;
	eBirthDate.GetWindowTextA(tmp, 256);
	details[8] = tmp;
	eHomeAddress.GetWindowTextA(tmp, 256);
	details[9] = tmp;
	p->ContactList[contact].setFirstName(details[1]);
	p->ContactList[contact].setLastName(details[2]);
	p->ContactList[contact].setEmailAddress(details[6]);
	p->ContactList[contact].setHomeAddress(details[9]);
	p->ContactList[contact].setPhoneNumber(details[3]);
	p->ContactList[contact].setOccupation(details[7]);
	int age = atoi(details[5].c_str());
	p->ContactList[contact].setAge(age);
	this->EndDialog(IDOK);
	return SUCCESS;
}

void PbDetails::DisplayInfo()
{
	if(p->ContactList[contact].getContactType().compare("acquaintance") == 0)
		cbType.SetCurSel(0);
	else if(p->ContactList[contact].getContactType().compare("colleague") == 0)
		cbType.SetCurSel(1);
	else cbType.SetCurSel(2);
	this->SetWindowTextA("Contact Details");
	eFirstName.SetWindowTextA(p->ContactList[contact].getFirstName().c_str());
	eLastName.SetWindowTextA(p->ContactList[contact].getLastName().c_str());
	ePhoneNumber.SetWindowTextA(p->ContactList[contact].getPhoneNumber().c_str());
	eOccupation.SetWindowTextA(p->ContactList[contact].getOccupation().c_str());
	int age = p->ContactList[contact].getAge();
	char tmp[10]; 
	_itoa_s(age, tmp, 10);
	eAge.SetWindowTextA(tmp);
	eHomeAddress.SetWindowTextA(p->ContactList[contact].getHomeAddress().c_str());
	eEmail.SetWindowTextA(p->ContactList[contact].getEmailAddress().c_str());
	eBirthDate.SetWindowTextA(p->ContactList[contact].getBirthDate().toString().c_str());
}

void PbDetails::ViewContact()
{
	this->SetWindowTextA("Add Contact");
	::ShowWindow(PbName, 1);
	::SetWindowTextA(PbName, "Contact Type:");
	cbType.ShowWindow(1);
	bSave.EnableWindow(0);
	ePbName.ShowWindow(0);
	cbType.EnableWindow(0);
	DisplayInfo();
	::SetWindowTextA(PbName, "Contact Name:");
}

void PbDetails::AddContact()
{
		this->SetWindowTextA("Add Contact");
		::ShowWindow(PbName, 1);
		::SetWindowTextA(PbName, "Contact Type:");
		cbType.ShowWindow(1);
		ePbName.ShowWindow(0);
		cbType.EnableWindow(1);
		
}

void PbDetails::EditContact()
{
	cbType.EnableWindow(1);
	if(p->ContactList[contact].getContactType().compare("acquaintance") == 0)
		cbType.SetCurSel(0);
	else if(p->ContactList[contact].getContactType().compare("colleague") == 0)
		cbType.SetCurSel(1);
	else cbType.SetCurSel(2);
	this->SetWindowTextA("Edit Contact");
	::ShowWindow(PbName, 1);
	::SetWindowTextA(PbName, "Contact Type:");
	cbType.ShowWindow(1);
	ePbName.ShowWindow(0);
	DisplayInfo();
}

void PbDetails::AddPhonebook()
{
	bSave.ShowWindow(1);
	bClear.ShowWindow(1);
	bBrowse.ShowWindow(1);
	bCancel.SetWindowTextA("Cancel");
	eFirstName.SetReadOnly(0);
	eLastName.SetReadOnly(0);
	ePbName.SetReadOnly(0);
	ePhoneNumber.SetReadOnly(0);
	eOccupation.SetReadOnly(0);
	eAge.SetReadOnly(0);
	eHomeAddress.SetReadOnly(0);
	eEmail.SetReadOnly(0);
	eBirthDate.SetReadOnly(0);
	::ShowWindow(PbName, 1);
	::SetWindowTextA(PbName, "Phone Book Name:");
	cbType.ShowWindow(0);
}

void PbDetails::ViewPhonebook()
{
	cbType.ShowWindow(0);
	bSave.ShowWindow(0);
	bClear.ShowWindow(0);
	bBrowse.ShowWindow(0);
	bCancel.SetWindowTextA("Close");
	eFirstName.SetReadOnly(1);
	eLastName.SetReadOnly(1);
	ePbName.SetReadOnly(1);
	ePhoneNumber.SetReadOnly(1);
	eOccupation.SetReadOnly(1);
	eAge.SetReadOnly(1);
	eHomeAddress.SetReadOnly(1);
	eEmail.SetReadOnly(1);
	eBirthDate.SetReadOnly(1);
	string tmp[256];
	eFirstName.SetWindowTextA(ini.GetStringValue(PbSection, "Owner First Name", "").c_str());
	eLastName.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Last Name", "").c_str());
	ePbName.SetWindowTextA(ini.GetStringValue(PbSection, "Phone Book Name", "").c_str());
	ePhoneNumber.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Phone Number", "").c_str());
	eOccupation.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Occupation", "").c_str());
	eAge.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Age", "").c_str());
	eHomeAddress.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Home Address", "").c_str());
	eEmail.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Email Address", "").c_str());
	eBirthDate.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Birth Date", "").c_str());
	CString str = ini.GetStringValue(PbSection, "Owner Photo", "").c_str();
	::ShowWindow(PbName, 1);
	mPic.LoadFromFile(str);
	::SetWindowTextA(PbName, "Phone Book Name:");
}

void PbDetails::EditPhonebook()
{
	cbType.ShowWindow(0);
	bSave.ShowWindow(0);
	bClear.ShowWindow(0);
	bBrowse.ShowWindow(0);
	bCancel.SetWindowTextA("Close");
	eFirstName.SetReadOnly(1);
	eLastName.SetReadOnly(1);
	ePbName.SetReadOnly(1);
	ePhoneNumber.SetReadOnly(1);
	eOccupation.SetReadOnly(1);
	eAge.SetReadOnly(1);
	eHomeAddress.SetReadOnly(1);
	eEmail.SetReadOnly(1);
	eBirthDate.SetReadOnly(1);
	string tmp[256];
	eFirstName.SetWindowTextA(ini.GetStringValue(PbSection, "Owner First Name", "").c_str());
	eLastName.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Last Name", "").c_str());
	ePbName.SetWindowTextA(ini.GetStringValue(PbSection, "Phone Book Name", "").c_str());
	ePhoneNumber.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Phone Number", "").c_str());
	eOccupation.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Occupation", "").c_str());
	eAge.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Age", "").c_str());
	eHomeAddress.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Home Address", "").c_str());
	eEmail.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Email Address", "").c_str());
	eBirthDate.SetWindowTextA(ini.GetStringValue(PbSection, "Owner Birth Date", "").c_str());
	CString str = ini.GetStringValue(PbSection, "Owner Photo", "").c_str();
	::ShowWindow(PbName, 1);
	::SetWindowTextA(PbName, "Phone Book Name:");
	mPic.LoadFromFile(str);
}

BOOL PbDetails::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	picLoaded = 0;
	this->OnBnClickedButton1();
	mPic.FreeData();
	cbType.AddString("acquaintance");
	cbType.AddString("colleague");
	cbType.AddString("friend");
	cbType.SetCurSel(0);
	PbName = ::GetDlgItem(this->m_hWnd, IDC_STATICPBNAME);
	switch(mode)
	{
	case ADD_PHONEBOOK:
		AddPhonebook();
		break;
	case EDIT_PHONEBOOK:
		EditPhonebook();
		break;
	case VIEW_PHONEBOOK:
		ViewPhonebook();
		break;
	case ADD_CONTACT:
		AddContact();
		break;
	case EDIT_CONTACT:
		EditContact();
		break;
	case VIEW_CONTACT:
		ViewContact();
		break;
	}


	// TODO:  Add extra initialization here
	HICON hSave = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON6));
	HICON hClear = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5));

	
	//DWORD error = GetLastError();
	bSave.SetIcon(hSave);
	bClear.SetIcon(hClear);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//clear edit boxes
void PbDetails::OnBnClickedButton1() //clear function
{
	// TODO: Add your control notification handler code here
	eFirstName.SetWindowTextA("");
	eFirstName.SetWindowTextA("");
	eLastName.SetWindowTextA("");
	ePbName.SetWindowTextA("");
	ePhoneNumber.SetWindowTextA("");
	eOccupation.SetWindowTextA("");
	eAge.SetWindowTextA("");
	eHomeAddress.SetWindowTextA("");
	eEmail.SetWindowTextA("");
	eBirthDate.SetWindowTextA("");
}
//cancel button
void PbDetails::OnBnClickedButton4() //cancel
{
	// TODO: Add your control notification handler code here
	this->EndDialog(IDCANCEL);
}

int PbDetails::SaveContact()
{
	if(mode == EDIT_CONTACT)
		return ChangeContact();
	char tmp[1024];
	string details[10];
	int sel = cbType.GetCurSel();
	if(sel == CB_ERR)
		MessageBox("Choose a contact type", "ERROR", MB_ICONWARNING);
	else cbType.GetLBText(sel, tmp);
	details[0] = tmp;
	eFirstName.GetWindowTextA(tmp, 256);
	details[1] = tmp;
	eLastName.GetWindowTextA(tmp, 256);
	details[2] = tmp;
	ePhoneNumber.GetWindowTextA(tmp, 256);
	details[3] = tmp;
	eAge.GetWindowTextA(tmp, 256);
	details[4] = "";
	details[5] = tmp;
	eEmail.GetWindowTextA(tmp, 256);
	details[6] = tmp;
	eOccupation.GetWindowTextA(tmp, 256);
	details[7] = tmp;
	eBirthDate.GetWindowTextA(tmp, 256);
	details[8] = tmp;
	eHomeAddress.GetWindowTextA(tmp, 256);
	details[9] = tmp;
	int err = 0;
	if(details[0].compare("acquaintance") == 0)
		p->addAcquaintance(details);
	else
		if(details[0].compare("colleague") == 0)
			p->addColleague(details);
		else if(details[0].compare("friend") == 0)
			p->addFriend(details);
		else
			err = 1;
	if(!err)
	{
		MessageBox("Contact saved", 0, 0);
		return SUCCESS;
	}
	return SUCCESS;

}


int PbDetails::ValidateInputData()
{
	int Pb = theApp.PbNumber;
	/*Pb = ini.GetIntValue("Settings", "PbNo");*/
	char tmp[256], section[100];
	_itoa_s(Pb, section, 10);
	for(int i = 0; i < (int) chPb->size(); i++)
	{
		if(_stricmp(tmp, chPb[i].c_str()) == 0)
			return PB_ALREADY_EXISTS;	
	}
	//ini.CreateSection(section);
	string pbPath, Update;
	string details[15];
	Update = "Update ";
	int i = 0;
	ePbName.GetWindowTextA(tmp, 256);
	details[i++] = tmp;
	int err = 0;
	pbPath = details = tmp;
	//ini.WriteValue(section, "Phone Book Name", details);
	try
	{
		theApp.db->UpdateValueById(Pb, "Phonebooks",  "PbName", tmp);
		eFirstName.GetWindowTextA(tmp, 256);
		details = tmp;
		//ini.WriteValue(section, "Owner First Name", details);
		theApp.db->UpdateValueById(Pb, "Phonebooks", "OwnerFName", tmp);
		eLastName.GetWindowTextA(tmp, 256);
		details += " ";
		details += tmp;
		p->setOwner(details);   /*db->query("CREATE TABLE IF NOT EXISTS Phonebooks(id INTEGER, name VARCHAR(50), 
			OwnerFName VARCHAR(50), OwnerLName VARCHAR(50),  OwnerAddress VARCHAR(100), OwnerPhoneNo VARCHAR(20),
			OwnerEmail VARCHAR(50), OwnerAge INTEGER, OwnerOccupation VARCHAR(50) , BirthDate DATE, Directory VARCHAR(500),
			OwnerPhotoPath VARCHAR(500), OwnerPhotoName VARCHAR(50));");*/
		details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerLName", tmp);
		ePhoneNumber.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerPhoneNo", tmp);
		eOccupation.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerOccupation", tmp);
		eAge.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks","OwnerAge", tmp);
		eHomeAddress.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks","OwnerAddress", tmp);
		eEmail.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerEmail", tmp);
		eBirthDate.GetWindowTextA(tmp, 256); details = tmp;
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerBirthDate", tmp);
		details = picName.GetBuffer();
		theApp.db->UpdateValueById(Pb,"Phonebooks", "OwnerPhotoPath", tmp);
		vector<vector<string>> ret;
		ret = theApp.db->query("SELECT * FROM Phonebooks");
		//cout<<"ret[0][0]="<<ret.at(0).at(0)<<endl;
	}
	catch(string error)
	{
		MessageBox(error.c_str(), "ERROR", 0);
		cout<<"\nerror="<<error<<endl;
	}
	
	string photoPath = photoDir;
	if(picLoaded)
	{		
		photoPath += "\\";
		photoPath += photoName;
		if(CopyFile(details.c_str(), photoPath.c_str(), 0) == 0 && photoPath.size() != 0)
			MessageBox("Can't copy photo", "ERROR", MB_ICONERROR);
		cout<<"photo path="<<photoPath<<endl;
		picLoaded = 0;
	}
	Pb++;
	char pbNo[10];
	_itoa_s(Pb, pbNo, 10);
	theApp.PbNumber++;
	photoPath = photoDir;
	photoPath += pbPath;
	photoPath += ".txt";
	ofstream f(photoPath.c_str());
	if(!f)
		return FILE_ERROR;
	else
		f.close();
	PbSection = "";
	photoDir = "";
	photoPath = "";
	this->EndDialog(IDOK);
	return SUCCESS;
}
//save
void PbDetails::OnBnClickedButton2() //save
{
	// TODO: Add your control notification handler code here
	if(mode == ADD_CONTACT)
		SaveContact();
	else
		if(mode == EDIT_CONTACT)
			ChangeContact();
		else if(mode == VIEW_CONTACT)
			ViewContact();
		else
	switch(ValidateInputData())
	{
	case PB_ALREADY_EXISTS:
		MessageBox("Enter a different phone book name, this one already exists", "ERROR", MB_ICONERROR);
		break;
	case FILE_ERROR:
		MessageBox("Error creating phone book file", "ERROR", MB_ICONERROR);
		break;
	case SUCCESS:
		MessageBox("New Phone Book Saved Succesfully!", "Saved", MB_ICONINFORMATION);
		break;
	}

}

BOOL PbDetails::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->message == WM_KEYDOWN) && 
    (pMsg->wParam == VK_RETURN) )
	{
	   // Enter key was hit -> do whatever you want
		if(bSave.EnableWindow(0) == 0)
			OnBnClickedButton2();
		else bSave.EnableWindow(0);
	   return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void PbDetails::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int length;
	length = eFirstName.GetWindowTextLengthA();
	int lastname = eLastName.GetWindowTextLengthA();
	int pb = 1;
	if(mode >= 3)
		pb = ePbName.GetWindowTextLengthA();
	if((length > 0 && lastname > 0 && pb > 0) || save == 1)
		bSave.EnableWindow(1);
	else
		bSave.EnableWindow(0);
	// TODO:  Add your control notification handler code here
}


void PbDetails::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int length;
	length = eFirstName.GetWindowTextLengthA();
	int lastname = eLastName.GetWindowTextLengthA();
	int pb = 1;
	if(mode >= 3)
		pb = ePbName.GetWindowTextLengthA();
	if((length > 0 && lastname > 0 && pb > 0) || save == 1)
		bSave.EnableWindow(1);
	else
		bSave.EnableWindow(0);
	// TODO:  Add your control notification handler code here
}


void PbDetails::OnEnChangeEdit9()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	int length;
	length = eFirstName.GetWindowTextLengthA();
	int lastname = eLastName.GetWindowTextLengthA();
	int pb = 1;
	if(mode >= 3)
		pb = ePbName.GetWindowTextLengthA();
	if((length > 0 && lastname > 0 && pb > 0) || save == 1)
		bSave.EnableWindow(1);
	else
		bSave.EnableWindow(0);
	// TODO:  Add your control notification handler code here
}


INT_PTR PbDetails::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class

		
	return CDialogEx::DoModal();
}
