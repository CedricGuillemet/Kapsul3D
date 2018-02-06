// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef CKSegmentH
#define CKSegmentH

#include "Kapsul3D.h"

class KAPSUL_DESC CKSegment
{
    public:
		// -- Methods ---------------------------------------------------------

        inline CKSegment(CKSegment *daPrev,CKSegment *daNext)
		{
			Prev=daPrev;
			Next=daNext;
			Selected=false;
			SegSelected=false;
		}
        inline ~CKSegment()
		{
		}

		inline void IsCopyOf(CKSegment *cmpt)
		{
			Selected=false;
			SegSelected=false;
			Dot=cmpt->Dot;
		}

		// -- Datas -----------------------------------------------------------

        CKSegment *Next;
        CKSegment *Prev;

        bool Selected;
        bool SegSelected;
        Vertex Dot;
		int Tag;
};
//---------------------------------------------------------------------------
#endif
