#include "stdafx.h"
#include "inetdl.h"
#include "resource.h"
bool Downing=false;


CString SetTimeLeft(DWORD dwSecondsLeft, DWORD dwBytesRead, DWORD dwFileSize)
{
  CString sCopied;
  if (dwBytesRead < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%d"), dwBytesRead);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (dwBytesRead < 1048576)
  {
    CString sKiloBytes;
    sKiloBytes.Format(_T("%0.1f"), dwBytesRead/1024.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
    sMegaBytes.Format(_T("%0.2f"), dwBytesRead/1048576.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_MEGABYTES, sMegaBytes);
  }

  CString sTotal;
  if (dwFileSize < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%d"), dwFileSize);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (dwFileSize < 1048576)
  {
    CString sKiloBytes;
    sKiloBytes.Format(_T("%0.1f"), dwFileSize/1024.0);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
    sMegaBytes.Format(_T("%0.2f"), dwFileSize/1048576.0);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_MEGABYTES, sMegaBytes);
  }

  CString sOf;
  AfxFormatString2(sOf, IDS_HTTPDOWNLOAD_OF, sCopied, sTotal);

  CString sTime;
  if (dwSecondsLeft < 60)
  {
    CString sSeconds;
    sSeconds.Format(_T("%d"), dwSecondsLeft);
    AfxFormatString1(sTime, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
  }
  else
  {
    DWORD dwMinutes = dwSecondsLeft / 60;
    DWORD dwSeconds = dwSecondsLeft % 60;
    CString sSeconds;
    sSeconds.Format(_T("%d"), dwSeconds);
    CString sMinutes;
    sMinutes.Format(_T("%d"), dwMinutes);
    if (dwSeconds == 0)
      AfxFormatString1(sTime, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
    else
      AfxFormatString2(sTime, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
  }

  CString sTimeLeft;
  AfxFormatString2(sTimeLeft, IDS_HTTPDOWNLOAD_TIMELEFT, sTime, sOf);
  //m_ctrlTimeLeft.SetWindowText(sTimeLeft);
  return sTimeLeft;
}


int DownloadThread(CThInfo *infos)
{

  CString       m_sError;
  CString       m_sServer; 
  CString       m_sObject; 
  CString       m_sFilename;
  INTERNET_PORT m_nPort;
  DWORD         m_dwServiceType;
  HINTERNET     m_hInternetSession;
  HINTERNET     m_hHttpConnection;
  HINTERNET     m_hHttpFile;
  BOOL          m_bAbort;
  BOOL          m_bSafeToClose;
  CFile         m_FileToWrite;
  CProgressCtrl *dstJauge;
  Downing=false;
  CString FullInfo;
/*
  CString m_sURLToDownload="http://perso.club-internet.fr/lacrapul/NetUp/update.txt";
  CString m_sFileToDownloadInto="d:\\test.txt";
  CString m_sUserName="none";
  CString m_sPassword="none";
*/

if (!m_FileToWrite.Open(infos->m_sFileToDownloadInto, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
  {
    TRACE(_T("Failed to open the file to download into, Error:%d\n"), GetLastError());
	/*
    CString sError;
    sError.Format(_T("%d"), ::GetLastError());
    CString sMsg;
    AfxFormatString1(sMsg, IDS_HTTPDOWNLOAD_FAIL_FILE_OPEN, sError);
    AfxMessageBox(sMsg);
    EndDialog(IDCANCEL);
	*/
    return 10;
  }


  dstJauge=infos->jauge;

  //Create the Internet session handle
  //ASSERT(m_hInternetSession == NULL);
  if (!AfxParseURL(infos->m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
  {
	TRACE(_T("Error Parsing"));
  }

  m_hInternetSession = ::InternetOpen(AfxGetAppName(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
  if (m_hInternetSession == NULL)
  {
    TRACE(_T("Failed in call to InternetOpen, Error:%d\n"), ::GetLastError());
//    HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_GENERIC_ERROR);
    return 1;
  }

  //Should we exit the thread
  /*
  if (m_bAbort)
  {
//    PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
    return;
  } 
  */

  /*
  //Setup the status callback function
  if (::InternetSetStatusCallback(m_hInternetSession, _OnStatusCallBack) == INTERNET_INVALID_STATUS_CALLBACK)
  {
    TRACE(_T("Failed in call to InternetSetStatusCallback, Error:%d\n"), ::GetLastError());
    //HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_GENERIC_ERROR);
    return;
  }
  */

  /*
  //Should we exit the thread
  if (m_bAbort)
  {
    //PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
    return;
  }
  */

  //Make the connection to the HTTP server          
//  ASSERT(m_hHttpConnection == NULL);
  if (infos->m_sUserName.GetLength())
    m_hHttpConnection = ::InternetConnect(m_hInternetSession, m_sServer, m_nPort, infos->m_sUserName, 
                                          infos->m_sPassword, m_dwServiceType, 0, 0/*(DWORD) this*/);
  else
    m_hHttpConnection = ::InternetConnect(m_hInternetSession, m_sServer, m_nPort, NULL, 
                                          NULL, m_dwServiceType, 0, 0/*(DWORD) this*/);
  if (m_hHttpConnection == NULL)
  {
    TRACE(_T("Failed in call to InternetConnect, Error:%d\n"), ::GetLastError());
    //HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
    return 2;
  }

  /*
  //Should we exit the thread
  if (m_bAbort)
  {
//    PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
    return;
  } 
  */

  //Start the animation to signify that the download is taking place
//  PlayAnimation();

  //Issue the request to read the file
  LPCTSTR ppszAcceptTypes[2];
  ppszAcceptTypes[0] = _T("*/*");  //We support accepting any mime file type since this is a simple download of a file
  ppszAcceptTypes[1] = NULL;
  //ASSERT(m_hHttpFile == NULL);
  m_hHttpFile = HttpOpenRequest(m_hHttpConnection, NULL, m_sObject, NULL, NULL, ppszAcceptTypes, INTERNET_FLAG_RELOAD | 
                                INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION, 0/*(DWORD) this*/);
  if (m_hHttpFile == NULL)
  {
    TRACE(_T("Failed in call to HttpOpenRequest, Error:%d\n"), ::GetLastError());
//    HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
    return 3;
  }

  /*
  //Should we exit the thread
  if (m_bAbort)
  {
//    PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
    return;
  } 
  */

//label used to jump to if we need to resend the request
resend:

  //Issue the request
  BOOL bSend = ::HttpSendRequest(m_hHttpFile, NULL, 0, NULL, 0);
  if (!bSend)
  {
    TRACE(_T("Failed in call to HttpSendRequest, Error:%d\n"), ::GetLastError());
//    HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
    return 4;
  }

  //Check the HTTP status code
	TCHAR szStatusCode[32];
	DWORD dwInfoSize = 32;
	if (!HttpQueryInfo(m_hHttpFile, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwInfoSize, NULL))
  {
    TRACE(_T("Failed in call to HttpQueryInfo for HTTP query status code, Error:%d\n"), ::GetLastError());
//    HandleThreadError(IDS_HTTPDOWNLOAD_INVALID_SERVER_RESPONSE);
    return 5;
  }
  else
  {
    long nStatusCode = _ttol(szStatusCode);

    //Handle any authentication errors
    if (nStatusCode == HTTP_STATUS_PROXY_AUTH_REQ || nStatusCode == HTTP_STATUS_DENIED)
    {
      // We have to read all outstanding data on the Internet handle
      // before we can resubmit request. Just discard the data.
      char szData[51];
      DWORD dwSize;
      do
	    {
		    ::InternetReadFile(m_hHttpFile, (LPVOID)szData, 50, &dwSize);
	    }
	    while (dwSize != 0);

      //Bring up the standard authentication dialog
      if (::InternetErrorDlg(NULL/*GetSafeHwnd()*/, m_hHttpFile, ERROR_INTERNET_INCORRECT_PASSWORD, FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
                             FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, NULL) == ERROR_INTERNET_FORCE_RETRY)
        goto resend;
    }
  	else if (nStatusCode != HTTP_STATUS_OK)
    {
      TRACE(_T("Failed to retrieve a HTTP 200 status, Status Code:%d\n"), nStatusCode);
//      HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_INVALID_HTTP_RESPONSE, nStatusCode);
      return 6;
    }
  }

  //Update the status control to reflect that we are getting the file information
//  SetStatus(IDS_HTTPDOWNLOAD_GETTING_FILE_INFORMATION);

  // Get the length of the file.            
  TCHAR szContentLength[32];
  dwInfoSize = 32;
  DWORD dwFileSize = 0;
  BOOL bGotFileSize = FALSE;
  if (::HttpQueryInfo(m_hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szContentLength, &dwInfoSize, NULL))
  {
    //Set the progress control range
    bGotFileSize = TRUE;
    dwFileSize = (DWORD) _ttol(szContentLength);
	if (dstJauge)
		dstJauge->SetRange32(0,dwFileSize);

	infos->Percent=0;
  }

  //Update the status to say that we are now downloading the file
//  SetStatus(IDS_HTTPDOWNLOAD_RETREIVEING_FILE);

  //Now do the actual read of the file
  DWORD dwStartTicks = ::GetTickCount();
  DWORD dwCurrentTicks = dwStartTicks;
  DWORD dwBytesRead = 0;
  char szReadBuf[1024];
  DWORD dwBytesToRead = 1024;
  DWORD dwTotalBytesRead = 0;
  DWORD dwLastTotalBytes = 0;
  DWORD dwLastPercentage = 0;
  do
  {
    if (!::InternetReadFile(m_hHttpFile, szReadBuf, dwBytesToRead, &dwBytesRead))
    {
      TRACE(_T("Failed in call to InternetReadFile, Error:%d\n"), ::GetLastError());
//      HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_ERROR_READFILE);
      return 7;
    }
    else if (dwBytesRead /*&& !m_bAbort*/)
    {
      //Write the data to file
      TRY
      {
        m_FileToWrite.Write(szReadBuf, dwBytesRead);
      }
      CATCH(CFileException, e);                                          
      {
        TRACE(_T("An exception occured while writing to the download file\n"));
//        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_ERROR_READFILE, e->m_lOsError);
        e->Delete();
        return 8;
      }
      END_CATCH

      //Increment the total number of bytes read
      dwTotalBytesRead += dwBytesRead;  
	if (dstJauge)
		dstJauge->SetPos(dwTotalBytesRead);

	CString tmpstr;
	/*
	tmpstr.Format("%d / %d ",dwTotalBytesRead,dwFileSize);
	if (infos->Info) infos->Info->SetWindowText(tmpstr);
	*/

	infos->Percent=(float)dwTotalBytesRead/(float)dwFileSize;
	infos->Percent*=100;
//	m_DlInfo
/*
      UpdateControlsDuringTransfer(dwStartTicks, dwCurrentTicks, dwTotalBytesRead, dwLastTotalBytes, 
                                     dwLastPercentage, bGotFileSize, dwFileSize);
									 */

		{
			
			  DWORD dwNowTicks = GetTickCount();
			  DWORD dwTimeTaken = dwNowTicks - dwCurrentTicks;
			  if (dwTimeTaken > 1000)
			  {
				double KbPerSecond = ((double)(dwTotalBytesRead) - (double)(dwLastTotalBytes)) / ((double)(dwTimeTaken));
				//SetTransferRate(KbPerSecond);

				CString sRate;
				  if (KbPerSecond < 1)
				  {
					CString sBytesPerSecond;
					sBytesPerSecond.Format(_T("%0.0f"), KbPerSecond*1024);
					AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_BYTESPERSECOND, sBytesPerSecond);
				  }
				  else if (KbPerSecond < 10)
				  {
					CString sKiloBytesPerSecond;
					sKiloBytesPerSecond.Format(_T("%0.2f"), KbPerSecond);
					AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
				  }
				  else
				  {
					CString sKiloBytesPerSecond;
					sKiloBytesPerSecond.Format(_T("%0.0f"), KbPerSecond);
					AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
				  }

				  FullInfo=sRate;
				  FullInfo+="\r\n";

				//Setup for the next time around the loop
				dwCurrentTicks = dwNowTicks;
				dwLastTotalBytes = dwTotalBytesRead;

				if (bGotFileSize)
				{
				  //Update the estimated time left
				  if (dwTotalBytesRead)
				  {
					DWORD dwSecondsLeft = (DWORD) (((double)dwNowTicks - dwStartTicks) / dwTotalBytesRead * 
												   (dwFileSize - dwTotalBytesRead) / 1000);
					FullInfo+=SetTimeLeft(dwSecondsLeft, dwTotalBytesRead, dwFileSize);
				  }
				}
			  }
			  if (infos->Info) infos->Info->SetWindowText(FullInfo);

		}
    }
  } 
  while (dwBytesRead /*&& !m_bAbort*/);

  //Delete the file being downloaded to if it is present and the download was aborted
  m_FileToWrite.Close();
  /*
  if (m_bAbort)
    ::DeleteFile(m_sFileToDownloadInto);
	*/

  //We're finished
//  PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
  Downing=true;
  return 0;
}