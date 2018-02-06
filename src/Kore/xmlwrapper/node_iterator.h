/*
 * Copyright (C) 2001-2002 Peter J Jones (pjones@pmade.org)
 * All Rights Reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/** @file
 * This file defines the xml::node_iterator class for libxml2.
**/

#ifndef __xmlwrapp_node_iterator_h__
#define __xmlwrapp_node_iterator_h__
#ifdef KAPSUL_EXPORT
	#define KAPSUL_DESC __declspec(dllexport)
#else
	#define KAPSUL_DESC __declspec(dllimport)
#endif

// xmlwarpp includes
#include "node.h"

// libxml includes
#include <libxml/tree.h>

//namespace xml {


// base iterator class
class KAPSUL_DESC node_iterator {
public:
    node_iterator (void) : node_(0) {}
    node_iterator (node &parent) : node_(reinterpret_cast<xmlNodePtr>(parent.get_node_data())) {}
    node_iterator (xmlNodePtr xmlnode) : node_(xmlnode) {}
    node_iterator (const node_iterator &other) : node_(other.node_) {}
    node_iterator& operator= (const node_iterator &other) { node_ = other.node_; return *this;}

    node* get (void) const;
    
    node_iterator& operator++ (void);
    node_iterator  operator++ (int);

    friend bool KAPSUL_DESC operator== (const node_iterator &lhs, const node_iterator &rhs);
    bool operator!= (const node_iterator &rhs)
	{
		return !(node_ == rhs);
    }

private:
    mutable node fake_node_;
    xmlNodePtr node_;
}; // end xml::node_iterator class



inline bool KAPSUL_DESC operator!= (const node::const_iterator &lhs, const node::const_iterator  &rhs) {
	return !(lhs == rhs);
    }
//} // end xml namespace
#endif
