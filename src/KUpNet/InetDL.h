#if !defined(INETDL__INCLUDED_)
#define INETDL__INCLUDED_

class CThInfo
{
public:
	CThInfo() 
	{
		m_sUserName="none";
		m_sPassword="none";
		jauge=NULL;
		Info=NULL;
	};
	~CThInfo() {};
	CString m_sURLToDownload;
	CString m_sFileToDownloadInto;
	CProgressCtrl *jauge;
	CStatic *Info;
	CString m_sUserName;
	CString m_sPassword;
	float Percent;
};

int DownloadThread(CThInfo *infos);

#endif