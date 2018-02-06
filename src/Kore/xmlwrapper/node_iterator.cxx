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
 * This file implements the node_iterator class for libxml2.
**/

//#include "stdafx.h"

// definition include
#include "node_iterator.h"

// xmlwrapp includes
#include "node.h"

// standard includes
#include <algorithm>

// libxml includes
#include <libxml/tree.h>

// node::iterator pimpl
struct nipimpl {
    node_iterator it;

    nipimpl (void) {};
    nipimpl (xmlNodePtr ptr) : it(ptr) {}
    nipimpl (const nipimpl &other) : it(other.it) {}
};

/*
 * node_iterator Real Iterator class
 */

//####################################################################
node* node_iterator::get (void) const {
    fake_node_.set_node_data(node_);
    return &fake_node_;
}
//####################################################################
node_iterator& node_iterator::operator++ (void) {
    node_ = node_->next;
    return *this;
}
//####################################################################
node_iterator node_iterator::operator++ (int) {
    node_iterator old(*this);
    ++(*this);
    return old;
}

/*
 * node::iterator wrapper iterator class.
 */

//####################################################################
node::iterator::iterator (void) {
    pimpl_ = new nipimpl;
}
//####################################################################
node::iterator::iterator (void *data) {
    pimpl_ = new nipimpl(static_cast<xmlNodePtr>(data));
}
//####################################################################
node::iterator::iterator (const iterator &other) {
    pimpl_ = new nipimpl(*(other.pimpl_));
}
//####################################################################
node::iterator& node::iterator::operator= (const iterator &other) {
    iterator tmp(other);
    swap(tmp);
    return *this;
}
//####################################################################
void node::iterator::swap (iterator &other) {
    std::swap(pimpl_, other.pimpl_);
}
//####################################################################
node::iterator::~iterator (void) {
    delete pimpl_;
}
//####################################################################
node::iterator::reference node::iterator::operator* (void) const {
    return *(pimpl_->it.get());
}
//####################################################################
node::iterator::pointer node::iterator::operator-> (void) const {
    return pimpl_->it.get();
}
//####################################################################
node::iterator& node::iterator::operator++ (void) {
    ++(pimpl_->it);
    return *this;
}
//####################################################################
node::iterator node::iterator::operator++ (int) {
    iterator tmp(*this);
    ++(*this);
    return tmp;
}

/*
 * node::const_iterator wrapper iterator class.
 */

//####################################################################
node::const_iterator::const_iterator (void) {
    pimpl_ = new nipimpl;
}
//####################################################################
node::const_iterator::const_iterator (void *data) {
    pimpl_ = new nipimpl(static_cast<xmlNodePtr>(data));
}
//####################################################################
node::const_iterator::const_iterator (const const_iterator &other) {
    pimpl_ = new nipimpl(*(other.pimpl_));
}
//####################################################################
node::const_iterator::const_iterator (const iterator &other) {
    pimpl_ = new nipimpl(*(other.pimpl_));
}
//####################################################################
node::const_iterator& node::const_iterator::operator= (const const_iterator &other) {
    const_iterator tmp(other);
    swap(tmp);
    return *this;
}
//####################################################################
void node::const_iterator::swap (const_iterator &other) {
    std::swap(pimpl_, other.pimpl_);
}
//####################################################################
node::const_iterator::~const_iterator (void) {
    delete pimpl_;
}
//####################################################################
node::const_iterator::reference node::const_iterator::operator* (void) const {
    return *(pimpl_->it.get());
}
//####################################################################
node::const_iterator::pointer node::const_iterator::operator-> (void) const {
    return pimpl_->it.get();
}
//####################################################################
node::const_iterator& node::const_iterator::operator++ (void) {
    ++(pimpl_->it);
    return *this;
}
//####################################################################
node::const_iterator node::const_iterator::operator++ (int) {
    const_iterator tmp(*this);
    ++(*this);
    return tmp;
}

//namespace xml {
bool __cdecl operator== (const node_iterator &lhs, const node_iterator &rhs) {
	return lhs.node_ == rhs.node_;
    }

bool __cdecl operator!= (const node_iterator &lhs, const node_iterator &rhs) {
	return !(lhs == rhs);
    }

bool __cdecl operator== (const node::iterator &lhs, const node::iterator &rhs) {
	return lhs.pimpl_->it == rhs.pimpl_->it;
    }

bool __cdecl operator!= (const node::iterator &lhs, const node::iterator &rhs) {
	return !(lhs == rhs);
    }

bool __cdecl operator== (const node::const_iterator &lhs, const node::const_iterator &rhs) {
	return lhs.pimpl_->it == rhs.pimpl_->it;
    }
/*
bool __cdecl operator!= (const node::const_iterator &lhs, const node::const_iterator &rhs) {
	return !(lhs == rhs);
    }
	*/
//}
