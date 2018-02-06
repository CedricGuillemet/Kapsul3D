// KHashTable.cpp: implementation of the CKHashTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KHashTable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKHashTable::CKHashTable()
{

}

CKHashTable::~CKHashTable()
{
	for (vector<CKHashEntry*>::iterator i = m_Entries.begin(); i != m_Entries.end(); i++)
	{
		delete *i;	
	}
}

CKHashEntry* CKHashTable::FindEntry(CString Name)
{
	for (vector<CKHashEntry*>::iterator i = m_Entries.begin(); i != m_Entries.end(); i++)
	{
		if ((*i)->GetName()==Name)
			return *i;
	}
	return NULL;
}

void CKHashTable::SetEntry(CString Name,CString Value)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		tmpEnt->SetEntry(Value);
	}
	else
	{
		tmpEnt=new CKHashEntry(Name);
		tmpEnt->SetEntry(Value);
		m_Entries.push_back(tmpEnt);
	}
}

void CKHashTable::SetEntry(CString Name,float Value)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		tmpEnt->SetEntry(Value);
	}
	else
	{
		tmpEnt=new CKHashEntry(Name);
		tmpEnt->SetEntry(Value);
		m_Entries.push_back(tmpEnt);
	}
}

void CKHashTable::SetEntry(CString Name,DWORD Value)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		tmpEnt->SetEntry(Value);
	}
	else
	{
		tmpEnt=new CKHashEntry(Name);
		tmpEnt->SetEntry(Value);
		m_Entries.push_back(tmpEnt);
	}
}

void CKHashTable::SetEntry(CString Name,int Value)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		tmpEnt->SetEntry(Value);
	}
	else
	{
		tmpEnt=new CKHashEntry(Name);
		tmpEnt->SetEntry(Value);
		m_Entries.push_back(tmpEnt);
	}
}

CString CKHashTable::GetString(CString Name)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		return tmpEnt->GetString();
	}
	return CString("");
}

float CKHashTable::GetFloat(CString Name)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		return tmpEnt->GetFloat();
	}
	return 0;
}


DWORD CKHashTable::GetDWord(CString Name)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		return tmpEnt->GetDWord();
	}
	return 0;
}

int CKHashTable::GetInt(CString Name)
{
	tmpEnt=FindEntry(Name);
	if (tmpEnt!=NULL)
	{
		return tmpEnt->GetInt();
	}
	return 0;
}
	
void CKHashTable::WriteToDisk(CString FileName,void *pObj,int PlugType)
{
	FILE *fp;
	fp=fopen(FileName.GetBuffer(1),"wt");
	if (fp!=NULL)
	{
		WriteToDisk(fp,pObj,PlugType);
		fclose(fp);
	}
}
	
void CKHashTable::WriteToDisk(FILE *fp,void *pObj,int PlugType)
{
	
	CString fmt;
	if (pObj==NULL)
	{
		fputs("{\n",fp);
		for (vector<CKHashEntry*>::iterator i = m_Entries.begin(); i != m_Entries.end(); i++)
		{
			fmt.Format("%s=\"%s\"\n",(*i)->GetName(),(*i)->GetString());

			fputs(fmt,fp);
		}
		fputs("}\n",fp);
	}
	else
	{
		CKCamera *pCam;
		CKMesh *pMesh;
		CKSkeleton *pSkel;
		CKShape *pShape;
		CKPatch *pPatch;

		fputs("{\n",fp);
		//Shape/mesh/camera/patch/skeleton
		switch(PlugType)
		{
		case PLUGIN_MESH:
			pMesh=(CKMesh*)pObj;
			fmt.Format("Name=\"%s\"\n",pMesh->Name);
			fputs(fmt,fp);
			fmt.Format("Color=\"0x%X\"\n",(pMesh->Color.GetDW()&0xFFFFFF));
			fputs(fmt,fp);

			fmt.Format("AutoUV=\"%d\"\n",(pMesh->GetAutoTexRecalc()?1:0));
			fputs(fmt,fp);
			fmt.Format("PrefabName=\"%s\"\n",pMesh->PrefabName);
			fputs(fmt,fp);
			break;
		case PLUGIN_SHAPE:
			pShape=(CKShape*)pObj;
			fmt.Format("Name=\"%s\"\n",pShape->Name);
			fputs(fmt,fp);
			fmt.Format("Color=\"0x%X\"\n",(pShape->Color.GetDW()&0xFFFFFF));
			fputs(fmt,fp);
			fmt.Format("DrawSpline=\"%d\"\n",(pShape->DrawSpline?1:0));
			fputs(fmt,fp);
			break;
		case PLUGIN_SKELETON:
			pSkel=(CKSkeleton*)pObj;
			fmt.Format("Name=\"%s\"\n",pSkel->Name);
			fputs(fmt,fp);
			fmt.Format("Color=\"0x%X\"\n",(pSkel->Color.GetDW()&0xFFFFFF));
			fputs(fmt,fp);
			break;
		case PLUGIN_CAMERA:
			pCam=(CKCamera*)pObj;
			fmt.Format("Name=\"%s\"\n",pCam->Name);
			fputs(fmt,fp);
			fmt.Format("Color=\"0x%X\"\n",(pCam->Color.GetDW()&0xFFFFFF));
			fputs(fmt,fp);
			fmt.Format("FOV=\"%d\"\n",pCam->Fov);
			fputs(fmt,fp);
			fmt.Format("ResoX=\"%d\"\n",pCam->ResoX);
			fputs(fmt,fp);
			fmt.Format("ResoY=\"%d\"\n",pCam->ResoY);
			fputs(fmt,fp);
			break;
		case PLUGIN_PATCH:
			pPatch=(CKPatch*)pObj;
			fmt.Format("Name=\"%s\"\n",pPatch->Name);
			fputs(fmt,fp);
			fmt.Format("Color=\"0x%X\"\n",(pPatch->Color.GetDW()&0xFFFFFF));
			fputs(fmt,fp);
			break;

		}
		for (vector<CKHashEntry*>::iterator i = m_Entries.begin(); i != m_Entries.end(); i++)
		{
			fmt.Format("%s=\"%s\"\n",(*i)->GetName(),(*i)->GetString());

			fputs(fmt,fp);
		}
		fputs("}\n",fp);


	}
}

bool CKHashTable::ReadHash(CString strRead,CString &dName,CString &dValue)
{
	dName="";
	dValue="";
	int i=0;
	while (strRead[i]!=' '&&strRead[i]!='=')
	{
		dName+=strRead[i];
		i++;
	}

	while (strRead[i]!='\"') i++;
	i++;

	while (strRead[i]!='\"')
	{
		dValue+=strRead[i];
		i++;
	}
	return true;
}

void CKHashTable::SetReadValue(CString dName,CString dValue)
{
	tmpEnt=FindEntry(dName);
	if (tmpEnt==NULL)
	{
		tmpEnt=new CKHashEntry(dName);
		tmpEnt->SetEntry(dValue);
		m_Entries.push_back(tmpEnt);
	}
	else
		tmpEnt->SetEntry(dValue);
}

void CKHashTable::ReadFromDisk(CString FileName,void *pObj,int PlugType)
{
	FILE *fp;
	fp=fopen(FileName.GetBuffer(1),"rt");
	if (fp!=NULL)
	{
		ReadFromDisk(fp,pObj,PlugType);
		fclose(fp);
	}
}

void CKHashTable::ReadFromDisk(FILE *fp,void *pObj,int PlugType)
{
	static char dafmt[10000];
	static char Name[5000],Value[5000];
	CString dName,dValue;

	fgets(dafmt,10000,fp);
	if (dafmt[0]=='{')
	{
		if (pObj==NULL)
		{
			bool RunOk=true;
			while (RunOk)
			{
				fgets(dafmt,10000,fp);
				if (dafmt[0]=='}')
				{
					RunOk=false;
				}
				else
				{
					
					ReadHash(dafmt,dName,dValue);
					SetReadValue(dName,dValue);
				}
			}
		}
		else
		{
			//Shape/mesh/camera/patch/skeleton

			CKCamera *pCam;
			CKMesh *pMesh;
			CKSkeleton *pSkel;
			CKShape *pShape;
			CKPatch *pPatch;
			int Tmpi;


			bool RunOk=true;
			while (RunOk)
			{
				fgets(dafmt,10000,fp);
				if (dafmt[0]=='}')
				{
					RunOk=false;
				}
				else
				{
					ReadHash(dafmt,dName,dValue);

					switch(PlugType)
					{
					case PLUGIN_MESH:
						pMesh=(CKMesh*)pObj;

						if (dName=="Name") pMesh->Name=dValue;
						else
						if (dName=="Color") sscanf(dValue,"0x%X",&pMesh->Color);
						else
						if (dName=="AutoUV")
						{
							 sscanf(dValue,"%d",&Tmpi);
							 pMesh->SetAutoTexRecalc((Tmpi==1));
						}
						else
						if (dName=="PrefabName") pMesh->PrefabName=dValue;
						else
							SetReadValue(dName,dValue);

						break;
					case PLUGIN_SHAPE:
						pShape=(CKShape*)pObj;
						if (dName=="Name") pShape->Name=dValue;
						else
						if (dName=="Color") sscanf(dValue,"0x%X",&pShape->Color);
						else
						if (dName=="DrawSpline")
						{
							 sscanf(dValue,"%d",&Tmpi);
							 pShape->DrawSpline=((Tmpi==1));
						}
						else
							SetReadValue(dName,dValue);
						break;
					case PLUGIN_SKELETON:
						pSkel=(CKSkeleton*)pObj;
						if (dName=="Name") pSkel->Name=dValue;
						else
						if (dName=="Color") sscanf(dValue,"0x%X",&pSkel->Color);
						else
							SetReadValue(dName,dValue);
						break;
					case PLUGIN_CAMERA:
						pCam=(CKCamera*)pObj;
						
						if (dName=="Name") pCam->Name=dValue;
						else
						if (dName=="Color") sscanf(dValue,"0x%X",&pCam->Color);
						else
						if (dName=="FOV") sscanf(dValue,"%d",&pCam->Fov);
						else
						if (dName=="ResoX") sscanf(dValue,"%d",&pCam->ResoX);
						else
						if (dName=="ResoY") sscanf(dValue,"%d",&pCam->ResoY);
						else
							SetReadValue(dName,dValue);
						break;
					case PLUGIN_PATCH:
						pPatch=(CKPatch*)pObj;
						if (dName=="Name") pPatch->Name=dValue;
						else
						if (dName=="Color") sscanf(dValue,"0x%X",&pPatch->Color);
						else
							SetReadValue(dName,dValue);
						break;

					}
				}

			}
			
			



		}
	}
	
}

inline void CKHashTable::IsCopyOf(CKHashTable &kht)
{
	CKHashEntry *pent;

	m_Entries.erase(m_Entries.begin(),m_Entries.end());

	for (int i=0;i<kht.GetNbEntries();i++)
	{
		tmpEnt=new CKHashEntry();
		pent=kht.GetEntry(i);
	
		tmpEnt->m_Name=pent->m_Name;
		tmpEnt->vals=pent->vals;

		m_Entries.push_back(tmpEnt);
	}

}
bool CKHashTable::EntryExists(CString Name)
{
	tmpEnt=FindEntry(Name);
	return (tmpEnt!=NULL);
}

void CKHashTable::EraseAll(void)
{
	m_Entries.erase(m_Entries.begin(),m_Entries.end());
}

