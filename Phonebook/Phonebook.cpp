#include "Phonebook.h"
#include <sstream>

bool Phonebook::mInstanceFlag = false;
Phonebook *Phonebook::mInstance = NULL;


Phonebook::Phonebook()
{
	ContactDB = new Database(mDbName);
}

int Phonebook::loadPhonebook()
{
	ifstream phb;//("c:\\l.txt",ios::app);
	if(!ContactDB->openDB())
	{
		MessageBox(0, "Can't open database", "ERROR", 0);
		return 0;
	}
	//ZeroMemory(&ContactList, sizeof(ContactList));
	ContactList.erase(ContactList.begin(), ContactList.end());
	vector<vector<string>> retVal;
	char Query[500];
	try
	{
		sprintf(Query, "SELECT * FROM %s;", mPbName.c_str());
		retVal = ContactDB->query(Query);
		int i, j;
		string info[20];
		string type;
		for(i = 0; i < retVal.size(); i++)
		{
			info[0] = retVal.at(i).at(10);
			info[1] = retVal.at(i).at(1);
			info[2] = retVal.at(i).at(2);
			info[3] = retVal.at(i).at(5);
			info[4] = retVal.at(i).at(3);
			info[5] = retVal.at(i).at(7);
			info[6] = retVal.at(i).at(6);
			info[7] = retVal.at(i).at(8);
			info[8] = retVal.at(i).at(9);
			info[9] = retVal.at(i).at(4);
			info[10] = retVal.at(i).at(0);
			
			if(info[0].compare("acquaintance") == 0)
				addAcquaintance(info);
			else if(info[0].compare("colleague") == 0)
					addColleague(info);
			else if(info[0].compare("friend") == 0)
					addFriend(info);
			else cout<<info[0]<<"\nThe phonebook file is corrupt\n";
			info->clear();
		}
	/*			cout<<"\nat["<<i<<"]["<<j<<"]="<<retVal.at(i).at(j);
			cout<<endl;
		}*/
	}
	catch(string error)
	{
		MessageBox(0, error.c_str(), "exception load pb", 0);
	}
	ContactDB->close();

	//int i, k = 0;
	//string str, tmp;
	//string infs[100];
	//while(phb)
	//{
	//	getline(phb,str);
	//	if(str.size() <= 0) 
	//		continue;
	//	i = 0;
	//	k = 0;
	//	for(i = 0; i <= (int)str.size(); i++)
	//	{
	//		tmp.clear();
	//		while(i < (int)str.size() && str[i] != '|')
	//		{
	//			tmp += str[i++];
	//		}
	//		infs[k++]=tmp;
	//		
	//	}
	//	if(infs[0].compare("acquaintance") == 0)
	//		addAcquaintance(infs);
	//	else if(infs[0].compare("colleague") == 0)
	//			addColleague(infs);
	//	else if(infs[0].compare("friend") == 0)
	//			addFriend(infs);
	//	else cout<<infs[0]<<"\nThe phonebook file is corrupt\n";
	//	infs->clear();
	//	str.clear();
	//}
	//phb.close();
	//memcpy(&tmpList, &ContactList, sizeof(ContactList));
	////mData.open(mDbName);
	//if(!mData)
	//	return 0;
	//return 1;
}

string Phonebook::getOwner() { return mOwner; }

void Phonebook::setOwner(string owner) { mOwner = owner; }

int Phonebook::addAcquaintance(string *s)
{
	Acquaintance tmp(s);
	ContactList.push_back(tmp);
	return 1;
}

int Phonebook::addColleague(string *s)
{
	Colleague col(s);
	ContactList.push_back(col);
	return 0;
}

int Phonebook::addFriend(string *s)
{
	Friend fr(s);
	ContactList.push_back(fr);
	return 0;
}

int Phonebook::displayContacts(deque<Contact> list)
{
	cout<<"\n\nContacts:\n\n";
	cout<<"size="<<list.size();
	for(int i = 0; i < (int)list.size(); i++)
	{
		cout<<"\nFirst Name:"<<list[i].getFirstName();
		cout<<"\nLast Name:"<<list[i].getLastName();
		cout<<"\nPhone number:"<<list[i].getPhoneNumber();
		cout<<"\nGender:"<<list[i].getGender()<<endl<<endl;
	}
	return 0;
}

void Phonebook::deleteContact(int nIndex)
{
	if(nIndex < 0 || nIndex > (int)ContactList.size())
		throw("Index out of range");
	else
	ContactList.erase(ContactList.begin() + nIndex);
}

deque<Contact> Phonebook::getContacts(deque<Contact> list, string contactType)
{
	if(!contactType.compare("all"))
		return list;
	deque<Contact> tmpList;
	for(int i = 0; i < (int)list.size(); i++)
		if(list[i].getContactType() == contactType)
			tmpList.push_back(list[i]);
	return tmpList;
}
//
//List Phonebook::search(string attribute, string crt, string contactType)
//{
//	List tmpList;
//	stringstream str;
//	int age;
//	str<<crt;
//str>>age;
//	for(int i = 0; i < ContactList.getSize(); i++)
//	{
//		if(attribute == "occupation" && ContactList[i].getOccupation().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "lastname" && ContactList[i].getLastName().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "firstname" && ContactList[i].getFirstName().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "gender" && ContactList[i].getGender().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "birth date" && ContactList[i].getBirthDate().toString() == crt)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "number" && ContactList[i].getPhoneNumber().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "email" && ContactList[i].getEmailAddress().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "address" && ContactList[i].getHomeAddress().find(crt) != string::npos)
//			tmpList.add(ContactList[i]);
//		else if(attribute == "age" && ContactList[i].getAge() == age)
//			tmpList.add(ContactList[i]);
//	}
//	return getContacts(tmpList, contactType);
//}





bool sortByLastName (Contact c1, Contact c2)
{
    /* a person is less than another person
     * - if the last name is less
     * - if the last name is equal and the first name is less
     */
    return c1.getLastName() < c2.getLastName();
}

bool sortByFirstName (Contact c1, Contact c2)
{
    return c1.getFirstName() < c2.getFirstName();
}

void Phonebook::Sort(int SortType)
{
	switch(SortType)
	{
	case SORT_BY_FIRST_NAME:
		sort(ContactList.begin(), ContactList.end(), sortByFirstName);
		break;
	case SORT_BY_LAST_NAME:
		sort(ContactList.begin(), ContactList.end(), sortByLastName);
		break;
	default:
		throw("Invalid type of sort");
	}
}

int Phonebook::savePhonebook(int save)
{
	//if(!save)
	//	memcpy(&ContactList, &tmpList, sizeof(tmpList));
	//int i = 0;
	//cout<<"\nfile pos="<<mData.tellp()<<endl;
	//for(i = 0; i < (int)ContactList.size(); i++)
	//{
	//	mData<<ContactList[i].getContactType()<<"|";
	//	mData<<ContactList[i].getFirstName()<<"|";
	//	mData<<ContactList[i].getLastName()<<"|";
	//	mData<<ContactList[i].getPhoneNumber()<<"|";
	//	mData<<ContactList[i].getGender();
	//	if(ContactList[i].getContactType().compare("colleague") == 0 )
	//		mData<<"|"<<ContactList[i].getAge()<<"|"<<ContactList[i].getEmailAddress()<<"|"<<ContactList[i].getOccupation();
	//	if(ContactList[i].getContactType().compare("friend") == 0)
	//		{
	//			mData<<"|"<<ContactList[i].getAge()<<"|"<<ContactList[i].getEmailAddress()<<"|"<<ContactList[i].getOccupation();
	//			mData<<"|"<<ContactList[i].getBirthDate().toString()<<"|"<<ContactList[i].getHomeAddress();
	//	}
	//	mData<<endl;
	//}
	//mData.close();
	return 0;
}

Phonebook::~Phonebook()
{
	//savePhonebook(1);
}

Iterator *Phonebook::createIterator() 
{
	return new Iterator(this);
}