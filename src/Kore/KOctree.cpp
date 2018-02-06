// KOctree.cpp: implementation of the CKOctree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KOctree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKOctree::~CKOctree()
{

}

void CKOctree::WriteToDisk(FILE *fp)
{

}

void CKOctree::LoadFromDisk(FILE *fp)
{

}

CKOctree::CKOctree(Vertex MinWS,Vertex MaxWS)
{
    WorldMin=MinWS;
    WorldMax=MaxWS;
    WorldMin.SetNextPower2();
    WorldMax.SetNextPower2();

    Root=new CKOctreeNode;
    wbox.pta=WorldMin;
    wbox.ptb=WorldMax;
    wbox.len=WorldMax-WorldMin;

    Root=new CKOctreeNode;
    Root->Bound.len=wbox.len;
    Root->Bound.pta=wbox.pta;
    Root->Bound.ptb=wbox.ptb;
}

CKOctreeNode * CKOctree::AddFace(Vertex a, Vertex b, Vertex c)
{
    // build the bounding box

    Vertex min=a;
    Vertex max=a;

    min.GetMinOf(b);
    min.GetMinOf(c);

    max.GetMaxOf(b);
    max.GetMaxOf(c);
/*
    min.SetNextPower2();
    max.SetNextPower2();
*/
    Vertex Dif=max-min;
    if ((Dif.x>Dif.y)&&(Dif.x>Dif.z)) 
    {   
        Dif.y=Dif.x;
        Dif.z=Dif.x;
    }
    else
    {
        if ((Dif.y>Dif.x)&&(Dif.y>Dif.z)) 
        {   
            Dif.x=Dif.y;
            Dif.z=Dif.y;
        }
        else
        {
            Dif.x=Dif.z;
            Dif.y=Dif.z;
        }
    }
    if (Dif.x==0) 
    {
        Dif.x=1;
        Dif.y=1;
        Dif.z=1;
    }
    CKBoundBox mbox(min,min+Dif,Dif);

    // root

    return FindBestNode(Root,mbox);
}

CKOctreeNode * CKOctree::FindBestNode(CKOctreeNode *Node,CKBoundBox &box)
{
    int value;
    Vertex tmp,tmp2,sta;
    tmp=(Node->Bound.len/2);
    tmp2=Node->Bound.pta;

    if (Node->Bound.len.x==4) return Node;

    if (BoxFitIn(box,tmp2,tmp)) value=0;
    else
    {
        sta=tmp2;
        sta.x+=tmp.x;
        if (BoxFitIn(box,sta,tmp)) value=1;
        else 
        {
            sta=tmp2;
            sta.y+=tmp.y;
            if (BoxFitIn(box,sta,tmp)) value=2;
            else 
            {
                sta=tmp2;
                sta.y+=tmp.y;
                sta.x+=tmp.x;
                if (BoxFitIn(box,sta,tmp)) value=3;
                else 
                {
                    sta=tmp2;
                    sta.z+=tmp.z;
                    if (BoxFitIn(box,sta,tmp)) value=4;
                    else 
                    {
                        sta=tmp2;
                        sta.z+=tmp.z;
                        sta.x+=tmp.x;
                        if (BoxFitIn(box,sta,tmp)) value=5;
                        else 
                        {
                            sta=tmp2;
                            sta.z+=tmp.z;
                            sta.y+=tmp.y;
                            if (BoxFitIn(box,sta,tmp)) value=6;
                            else 
                            {
                                sta=tmp2;
                                sta.z+=tmp.z;
                                sta.y+=tmp.y;
                                sta.x+=tmp.x;
                                if (BoxFitIn(box,sta,tmp)) value=7;
                                    else return Node;
                            }
                        }
                    }
                }
            }
        }
    }

    if (Node->Childs[value]==NULL)
    {
        Node->Childs[value]=new CKOctreeNode;
        Node->Childs[value]->Bound.pta=sta;//=BuildBound(Node->Bound,value);
        Node->Childs[value]->Bound.ptb=sta+tmp;
        Node->Childs[value]->Bound.len=tmp;
    }
    return FindBestNode(Node->Childs[value],box);

    //return NULL;
}
inline bool CKOctree::BoxFitIn(CKBoundBox &cb,Vertex &Start,Vertex &Len)
{
    if ( (cb.pta.x>=Start.x) && (cb.ptb.x<=(Start.x+Len.x)) &&
        (cb.pta.y>=Start.y) && (cb.ptb.y<=(Start.y+Len.y)) &&
        (cb.pta.z>=Start.z) && (cb.ptb.z<=(Start.z+Len.z)) )
        return true;

    return false;
}