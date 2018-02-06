// TextureSpace.cpp: implementation of the CKTextureSpace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
/*
#include "TextureSpace.h"
#include <stdio.h>
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKTextureSpace::~CKTextureSpace()
{
    delete [] lpBits;
    delete Entry;    
}

CKTextureSpace::CKTextureSpace(int _SizeX, int _SizeY)
{
    SizeX=_SizeX;
    SizeY=_SizeY;
    lpBits=new BYTE[SizeX*SizeY*3];
    memset(lpBits,0xcc,(SizeX*SizeY*3));
    Entry=NULL;
    Next=NULL;
    Surface=SizeX*SizeY;
}

bool CKTextureSpace::FindPlace(int _SizeX, int _SizeY, BYTE *Bits,float &tu,float &tv,float &stu,float &stv,bool Boxed)
{
    if ((_SizeX>SizeX)||(_SizeY>SizeY)) return false;
    
    if ((_SizeX*_SizeY)>(Surface)) 
        return false;

    // first entry

    if (Entry==NULL)
    {
        Entry=new CKTextureSpaceEntry(0,0,_SizeX,_SizeY);
        
        CopyBits(Entry,Bits,Boxed);
        tu=0;
        tv=0;
        stu=((float)_SizeX/(float)SizeX);
        stv=((float)_SizeY/(float)SizeY);
        return true;
    }

    // recurs

    if(RecursFindPlace(Entry,_SizeX,_SizeY,Bits,/*tu,tv,stu,stv,*/0,0,SizeX,SizeY,Boxed))
    {
        tu=Currenttu;
        tv=Currenttv;
        stu=Currentstu;
        stv=Currentstv;
        return true;
    }
    return false;
}

bool CKTextureSpace::RecursFindPlace(CKTextureSpaceEntry *Node,int _SizeX, int _SizeY, BYTE *Bits/*,float &tu,float &tv,float &stu,float &stv*/,int dax,int day,int dasx,int dasy,bool Boxed)
{
    /*
    if (Node->Left!=NULL)
    {
        if (RecursFindPlace(Node->Left,_SizeX,_SizeY,Bits,tu,tv,stu,stv,dax+Node->sx,day,dasx-Node->sx,Node->sy,Boxed))
            return true;
    }
    else
    {
        if ( (_SizeX<=(dasx-Node->sx)) && (_SizeY<=(Node->sy)) )
        {
            Node->Left=new CKTextureSpaceEntry(dax+Node->sx,day,_SizeX,_SizeY);
            CopyBits(Node->Left,Bits,Boxed);
            return true;
        }
    }

    if (Node->Down!=NULL)
    {
        if (RecursFindPlace(Node->Down,_SizeX,_SizeY,Bits,tu,tv,stu,stv,dax,day+Node->sy,Node->sx,dasy-Node->sy,Boxed))
            return true;
    }
    else
    {
        if ( (_SizeX<=(Node->sx)) && (_SizeY<=(dasy-Node->sy)) )
        {
            Node->Down=new CKTextureSpaceEntry(dax,day+Node->sy,_SizeX,_SizeY);
            CopyBits(Node->Down,Bits,Boxed);
            return true;
        }
    }

    if (Node->Other!=NULL)
    {
        if (RecursFindPlace(Node->Other,_SizeX,_SizeY,Bits,tu,tv,stu,stv,dax+Node->sx,day+Node->sy,dasx-Node->sx,dasy-Node->sy,Boxed))
            return true;
    }
    else
    {
        if ( (_SizeX<=(dasx-Node->sx)) && (_SizeY<=(dasy-Node->sy)) )
        {
            Node->Other=new CKTextureSpaceEntry(dax+Node->sx,day+Node->sy,_SizeX,_SizeY);
            CopyBits(Node->Other,Bits,Boxed);
            return true;
        }
        
    }
*/


    if (Node->Left!=NULL)
    {
        if ((_SizeY<=Node->sy)&&(_SizeX<=dasx-Node->sx))
            if (RecursFindPlace(Node->Left,_SizeX,_SizeY,Bits,dax+Node->sx,day,dasx-Node->sx,Node->sy,Boxed))
                return true;
    }
    else
    {
        if ( (_SizeX<=(dasx-Node->sx)) && (_SizeY<=(Node->sy)) )
        {
            Node->Left=new CKTextureSpaceEntry(dax+Node->sx,day,_SizeX,_SizeY);
            CopyBits(Node->Left,Bits,Boxed);
            return true;
        }
    }

    if (Node->Down!=NULL)
    {
        if ((_SizeX<=Node->sx)&&(_SizeY<=dasy-Node->sy))
            if (RecursFindPlace(Node->Down,_SizeX,_SizeY,Bits,dax,day+Node->sy,Node->sx,dasy-Node->sy,Boxed))
                return true;
    }
    else
    {
        if ( (_SizeX<=(Node->sx)) && (_SizeY<=(dasy-Node->sy)) )
        {
            Node->Down=new CKTextureSpaceEntry(dax,day+Node->sy,_SizeX,_SizeY);
            CopyBits(Node->Down,Bits,Boxed);
            return true;
        }
    }

    if (Node->Other!=NULL)
    {
        if ((_SizeX<=(dasx-Node->sx))&&(_SizeY<=(dasy-Node->sy)))
            if (RecursFindPlace(Node->Other,_SizeX,_SizeY,Bits,dax+Node->sx,day+Node->sy,dasx-Node->sx,dasy-Node->sy,Boxed))
                return true;
    }
    else
    {
        if ( (_SizeX<=(dasx-Node->sx)) && (_SizeY<=(dasy-Node->sy)) )
        {
            Node->Other=new CKTextureSpaceEntry(dax+Node->sx,day+Node->sy,_SizeX,_SizeY);
            CopyBits(Node->Other,Bits,Boxed);
            return true;
        }
        
    }
    return false;

}

inline void CKTextureSpace::CopyBits(CKTextureSpaceEntry *Node,BYTE *bits,bool Boxed)
{
    BYTE *Dest;
    int i,j;

    Surface-=(Node->sx*Node->sy);

    if (Boxed)
    {
        for (i=0;i<Node->sy;i++)
        {
            Dest=lpBits;
            Dest+=(((i+Node->y)*SizeX+Node->x)*3);

            for (j=0;j<Node->sx;j++)
            {
                if ( (i==0)||(j==0)||(i==(Node->sy-1))||(j==(Node->sx-1)) )
                {
                    (*Dest++)=255;
                    (*Dest++)=255;
                    (*Dest++)=255;
                    bits+=3;
                }
                else
                {
                    (*Dest++)=(*bits++);
                    (*Dest++)=(*bits++);
                    (*Dest++)=(*bits++);
                }
            }
        }
    }
    else
    {
		/*
        for (i=0;i<Node->sy;i++)
        {
            Dest=lpBits;
            Dest+=(((i+Node->y)*SizeX+Node->x)*3);
            memcpy(Dest,bits,Node->sx*3);
            bits+=(Node->sx*3);
        }
		*/
		
		int iX,iY,iZ,iCurLumel,dstLumel;
		int Sum,Divit;

		for (iX = 0; iX<Node->sx ; iX++)
		{
			for (iY = 0; iY<Node->sy ; iY++)
			{
				for (iZ=0;iZ<3;iZ++)
				{
					iCurLumel = (iY * (Node->sx) + iX)*3 + iZ;
					dstLumel=((((iY+Node->y)*SizeX+Node->x))+iX)*3+iZ;

					Sum=bits[iCurLumel];
					Divit=1;

					

					if (iY<(Node->sy-1))
					{
						if (iX<(Node->sx-1))
						{
							Sum+=bits[((iY + 1) * (Node->sx) + (iX + 1))*3 + iZ];
							Divit++;
						}
						bits[((iY + 1) * (Node->sx) + iX)*3 + iZ];
						Divit++;
						
					}

					if (iY>0)
					{
						
						if (iX>0)
						{
							Sum+=bits[((iY - 1) * (Node->sx) + (iX - 1))*3 + iZ];
							Divit++;

						}
						Sum+=bits[((iY - 1) * (Node->sx) + iX)*3 + iZ];
						Divit++;
					}

					if (iX>0)
					{
						Sum+=bits[(iY * (Node->sx) + (iX - 1))*3 + iZ];
						Divit++;
						if (iY<(Node->sy-1))
						{
							Sum+=bits[((iY + 1) * (Node->sx) + (iX - 1))*3 + iZ];
							Divit++;
						}

					}

					if (iX<(Node->sx-1))
					{
						if (iY>0)
						{
							Sum+=bits[((iY - 1) * (Node->sx) + (iX + 1))*3 + iZ];
							Divit++;
						}

						Sum+=bits[(iY * (Node->sx) + (iX + 1))*3 + iZ];
						Divit++;
					}
					lpBits[dstLumel]=(unsigned char)(Sum/Divit);
					

				}
			}
		}
		
    }



    Currenttv=((float)Node->y)/(float)SizeY;
    Currenttu=((float)Node->x)/(float)SizeX;

    Currentstv=((float)Node->sy)/(float)SizeY;
    Currentstu=((float)Node->sx)/(float)SizeX;
    
}

void CKTextureSpace::WriteToFile(char *FileName)
{

/*

    FILE *fp=fopen(FileName,"wb");
    if (fp)
    {
        fwrite(lpBits,SizeX*SizeY,3,fp);
        fclose(fp);
    }
*/


	CKImage tmpImg;
/*
	tmpImg.InitRawBits(lpBits,SizeX,SizeY);
	tmpImg.SaveFile(FileName);
	*/
	tmpImg.InitRawBits(lpBits,SizeX,SizeY);
/*
    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(tmpImg.m_hDib);			
    BYTE *lpBitsd = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);
    memcpy(lpBitsd,lpBits,(SizeX,SizeY*3));
	*/
	
	tmpImg.SaveFile(FileName);
	//GlobalUnlock(BiDest);
}

void CKTextureSpace::CopyBitsTo(BYTE *Dest)
{
	memcpy(Dest,lpBits,(SizeX*SizeY*3));
}
