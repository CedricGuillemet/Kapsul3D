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
 * This file contains the implementation of the node class.
**/

#include "stdafx.h"

// definition include
#include "node.h"

// standard includes
#include <new>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

// libxml includes
#include <libxml/tree.h>

struct node::pimpl {
    xmlNodePtr xmlnode;
    bool owner;
    std::string tmp_string;

    pimpl (void) : xmlnode(0), owner(true) {}
    ~pimpl (void) {release();}
    void release (void) {
	if (xmlnode && owner) {
	    xmlFreeNode(xmlnode);
	}
    }

};

namespace {
    const xmlChar const_xml_version[] = "1.0";

    // exception safe wrapper around xmlChar*s that are returned from some of
    // the libxml functions that the user must free.
    class xmlchar_helper {
    public:
	xmlchar_helper (xmlChar *ptr) : ptr_(ptr)
	{ }
	
	~xmlchar_helper (void) 
	{ if (ptr_) xmlFree(ptr_); }

	const char* get (void) const 
	{ return reinterpret_cast<const char*>(ptr_); }
    private:
	xmlChar *ptr_;
    };
}

//####################################################################
node::node (void) {
    std::auto_ptr<pimpl> ap(pimpl_ = new pimpl);

    pimpl_->xmlnode = xmlNewNode(0, reinterpret_cast<const xmlChar*>("blank"));
    if (!pimpl_->xmlnode) throw std::bad_alloc();

    ap.release();
}
//####################################################################
node::node (const char *name) {
    std::auto_ptr<pimpl> ap(pimpl_ = new pimpl);

    pimpl_->xmlnode = xmlNewNode(0, reinterpret_cast<const xmlChar*>(name));
    if (!pimpl_->xmlnode) throw std::bad_alloc();

    ap.release();
}
//####################################################################
node::node (const char *name, const char *content) {
    std::auto_ptr<pimpl> ap(pimpl_ = new pimpl);

    pimpl_->xmlnode = xmlNewNode(0, reinterpret_cast<const xmlChar*>(name));
    if (!pimpl_->xmlnode) throw std::bad_alloc();

    xmlNodePtr content_node = xmlNewText(reinterpret_cast<const xmlChar*>(content));
    if (!content_node) throw std::bad_alloc();

    if (!xmlAddChild(pimpl_->xmlnode, content_node)) {
	xmlFreeNode(content_node);
	throw std::bad_alloc();
    }

    ap.release();
}
//####################################################################
node::node (const node &other) {
    std::auto_ptr<pimpl> ap(pimpl_ = new pimpl);

    pimpl_->xmlnode = xmlCopyNode(other.pimpl_->xmlnode, 1);
    if (!pimpl_->xmlnode) throw std::bad_alloc();

    ap.release();
}
//####################################################################
node& node::operator= (const node &other) {
    node tmp_node(other);
    swap(tmp_node);
    return *this;
}
//####################################################################
void node::swap (node &other) {
    std::swap(pimpl_, other.pimpl_);
}
//####################################################################
node::~node (void) {
    delete pimpl_;
}
//####################################################################
void node::set_node_data (void *data) {
    pimpl_->release();
    pimpl_->xmlnode = static_cast<xmlNodePtr>(data);
    pimpl_->owner = false;
}
//####################################################################
void* node::get_node_data (void) {
    return pimpl_->xmlnode;
}
//####################################################################
void node::set_name (const char *name) {
    xmlNodeSetName(pimpl_->xmlnode, reinterpret_cast<const xmlChar*>(name));
}
//####################################################################
const char* node::get_name (void) const {
    return reinterpret_cast<const char*>(pimpl_->xmlnode->name);
}
//####################################################################
void node::set_content (const char *content) {
    xmlNodeSetContent(pimpl_->xmlnode, reinterpret_cast<const xmlChar*>(content));
}
//####################################################################
const char* node::get_content (void) const {
    /*
     * If this node is not a text node then return the text from the first
     * child. If the first child is not a text node either then return zero.
     */
    if (!is_text()) {
	const_iterator first_child = begin();

	if (first_child != end() && first_child->is_text()) {
	    pimpl_->tmp_string = first_child->get_content();
	    return pimpl_->tmp_string.c_str();
	}

	return 0;
    }

    xmlchar_helper content(xmlNodeGetContent(pimpl_->xmlnode));
    if (!content.get()) return 0;

    pimpl_->tmp_string = content.get();
    return pimpl_->tmp_string.c_str();
}
//####################################################################
void node::set_attr (const char *name, const char *value) {
    xmlSetProp(pimpl_->xmlnode, reinterpret_cast<const xmlChar*>(name),
	    reinterpret_cast<const xmlChar*>(value));
}
//####################################################################
const char* node::get_attr (const char *name) const {
    xmlchar_helper value(xmlGetProp(pimpl_->xmlnode, reinterpret_cast<const xmlChar*>(name)));
    if (!value.get()) return 0;

    pimpl_->tmp_string = value.get();
    return pimpl_->tmp_string.c_str();
}
//####################################################################
bool node::get_attr (const char *name, std::string &value) const {
    const char *tmp = get_attr(name);
    if (!tmp) return false;

    value = tmp;
    return true;
}

bool node::get_attr (const char *name, char *value) const {
    const char *tmp = get_attr(name);
    if (!tmp) return false;

    strcpy(value ,tmp);
    return true;
}
//####################################################################
void node::remove_attr (const char *name) {
    xmlUnsetProp(pimpl_->xmlnode, reinterpret_cast<const xmlChar*>(name));
}
//####################################################################
bool node::is_text (void) const {
    return xmlNodeIsText(pimpl_->xmlnode);
}
//####################################################################
void node::push_back (const node &child) {
    xmlNodePtr node_to_add = xmlCopyNode(child.pimpl_->xmlnode, 1);
    if (!node_to_add) return;

    if (!xmlAddChild(pimpl_->xmlnode, node_to_add)) {
	xmlFreeNode(node_to_add);
    }
}
//####################################################################
node::iterator node::begin (void) {
    return iterator(pimpl_->xmlnode->children);
}
//####################################################################
node::const_iterator node::begin (void) const {
    return const_iterator(pimpl_->xmlnode->children);
}
//####################################################################
node::iterator node::end (void) {
    return iterator();
}
//####################################################################
node::const_iterator node::end (void) const {
    return const_iterator();
}
//####################################################################
void node::node_to_string (std::string &xml) const {
    xmlDocPtr doc = xmlNewDoc(const_xml_version);
    if (!doc) return;

    xmlDocSetRootElement(doc, pimpl_->xmlnode);

    xmlChar *xml_string;
    int xml_string_length;

    xmlDocDumpFormatMemory(doc, &xml_string, &xml_string_length, 1);
    xml.assign(reinterpret_cast<char*>(xml_string), xml_string_length);
    xmlFree(xml_string);

    // reset libxml data structures
    doc->children		= 0;
    doc->last			= 0;
    pimpl_->xmlnode->parent	= 0;
    pimpl_->xmlnode->doc	= 0;

    xmlFreeDoc(doc);
}
//####################################################################
std::ostream& operator<< (std::ostream &stream, const node &n) {
    std::string xmldata;
    n.node_to_string(xmldata);
    stream << xmldata;
    return stream;
}
