// Option.h: interface for the CKOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_)
#define AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
enum {OPT_INT,OPT_BOOL,OPT_STRING,OPT_COLOR};

typedef struct
{
	char *Name;
	int Type;
	void *Dest;
} OptEntry;


class KAPSUL_DESC CKOption  
{
private:
    vector<CString> OptMapDirs;
	vector<CString> PrefabDirs;

	int nbMapDir;
	int nbPrefabDir;

public:
	CKOption(CWinApp *theApp);
	virtual ~CKOption();

    void AddMapDir(CString daMapDir);
    void DelAllMapDir(void);
    int GetnbMapDir(void);
    CString GetMapDir(int Number);

    void AddPrefabDir(CString daPrefabDir);
    void DelAllPrefabDir(void);
    int GetnbPrefabDir(void);
    CString GetPrefabDir(int Number);

	void BuildXmlOptions(CString &Target);
	void ReadUserFileValue(char *Name,char *Value);
	void ReadColor(char *Value,RGB *Dest);
	void ReadInt(char *Value,int *Dest);
	void ReadString(char *Value,char *Dest);
	void ReadBool(char *Value,bool *Dest);
	void WriteOptions(void);

	int GetInt(char *Name);
	DWORD GetColor(char *Name);
	bool GetBool(char *Name);
	char* GetString(char *Name);
	DWORD GetDWORDColor(RGB *Dest);
	int FindByName(char *Name);

public:
	CString m_AppDir;
	static OptEntry OptValues[];
	// options values
	
	bool OpenEmpty();
	RGB *GridColor1();
	RGB *GridColor2();
	RGB *ActiveBackColor();
	RGB *NActiveBackColor();
	RGB *HandlesRoundColor();
	RGB *HandlesColor();
	RGB *ColorMesh(int MeshNb);
	int Precision();
	int GridSpace(int GridSnapNb);
	int AngleSnap(int AngleSnapNb);
	bool ActivateMouseOver();
	bool GridBehindIso();
	bool GridBehindCamera();
	int DefaultSpamLevel();
	int MinimumSpamLevel();
	bool LogToFile();
	char* LogFileName();
	bool InvertedFly();
	int MotionValue();
	int MotionIncValue();
	int NbUndos();
	char *EntityXMLLocation();
	char *EntityDLLLocation();
	bool ShowSplash();
	bool DrawFontBack();
	RGB *FontBackColor();
	bool GenerateUV();
	bool RecursePrefab();
	int CameraFov();
	bool GetShowHandlesCamera();
	bool GetShowGridCamera();
	bool GetEnableAutoSave();
	char *GetAutoSaveDir();
	int GetAutoSaveDelay();
	RGB *GetCentroid();
	char *GetDefaultTexture();
	char *GetRenderer();

	static RGB m_GridColor1;
	static RGB m_GridColor2;
	static RGB m_ActiveBackColor;
	static RGB m_NActiveBackColor;
	static RGB m_HandlesRoundColor;
	static RGB m_HandlesColor;
	static RGB m_ColorMesh1;
	static RGB m_ColorMesh2;
	static RGB m_ColorMesh3;
	static RGB m_ColorMesh4;
	static RGB m_ColorMesh5;
	static RGB m_ColorMesh6;
	static RGB m_ColorMesh7;
	static RGB m_ColorMesh8;
	static RGB m_ColorMesh9;
	static RGB m_ColorMesh10;
	static int m_Precision;
	static int m_GridSpace1;
	static int m_GridSpace2;
	static int m_GridSpace3;
	static int m_GridSpace4;
	static int m_GridSpace5;
	static int m_Angle1;
	static int m_Angle2;
	static int m_Angle3;
	static int m_Angle4;
	static int m_Angle5;
	static bool m_ActivateMouseOver;
	static bool m_OpenEmpty;
	static bool m_GridBehindIso;
	static bool m_GridBehindCamera;
	static int m_DefaultSpamLevel;
	static int m_MinimumSpamLevel;
	static bool m_LogToFile;
	static char m_LogFileName[MAX_PATH];
	static bool m_InvertedFly;
	static int m_MotionValue;
	static int m_MotionIncValue;
	static int m_NbUndos;
	static char m_EntityXMLLocation[MAX_PATH];
	static bool m_ShowSplash;
	static bool m_DrawFontBack;
	static RGB m_FontBackColor;
	static char m_EntityDLLLocation[MAX_PATH];
	static bool m_GenerateUV;
	static int m_CameraFov;
	static bool m_RecursePrefab;
	static char m_TTFFont[MAX_PATH];
	static int m_FontSize;
	static bool m_ShowHandlesCamera;
	static bool m_ShowGridCamera;
	static bool m_EnableAutoSave;
	static char m_AutoSaveDir[MAX_PATH];
	static int m_AutoSaveDelay;
	static RGB m_Centroid;
	static char m_DefTex[MAX_PATH];
	static char m_Renderer[MAX_PATH];
	char *GetFont();
	int GetFontSize();

	
};	
//CKOption __declspec( dllexport ) KOption;

#endif // !defined(AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_)
