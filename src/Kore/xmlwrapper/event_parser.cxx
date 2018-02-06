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
 * This file contains the implementation of the event_parser class for
 * the libxml XML parser.
**/

// definition include
#include "stdafx.h"
#include "event_parser.h"

// xmlwrapp includes
#include "node.h"

// libxml includes
#include <libxml/parser.h>

// standard includes
#include <new>
#include <cstring>
#include <iostream>
#include <fstream>

//####################################################################
namespace {
    const size_t const_buffer_size = 4096;

    extern "C" xmlEntityPtr cb_get_entity (void *, const xmlChar *name);
    extern "C" void cb_start_element (void *parser, const xmlChar *tag, const xmlChar **props);
    extern "C" void cb_end_element (void *parser, const xmlChar *tag);
    extern "C" void cb_text (void *parser, const xmlChar *text, int length);
    extern "C" void cb_error (void *parser, const char *, ...);
} // end anonymous namespace
//####################################################################
struct epimpl {
public:
    epimpl (event_parser &parent);
    ~epimpl (void);

    xmlSAXHandler sax_handler_;
    xmlParserCtxt *parser_context_;
    bool parser_status_;

    void event_start_element (const xmlChar *tag, const xmlChar **props);
    void event_end_element (const xmlChar *tag);
    void event_text (const xmlChar *text, int length);
    void event_error (void);
private:
    event_parser &parent_;

    epimpl (const epimpl&);
    epimpl& operator= (const epimpl&);
};
//####################################################################
event_parser::event_parser (void) {
    pimpl_ = new epimpl(*this);
}
//####################################################################
event_parser::~event_parser (void) {
    delete pimpl_;
}
//####################################################################
bool event_parser::parse_file (const char *filename) {
    std::ifstream file(filename); if (!file) return false;
    return parse_stream(file);
}
//####################################################################
bool event_parser::parse_stream (std::istream &stream) {
    char buffer[const_buffer_size];

    while (pimpl_->parser_status_ && (stream.read(buffer, const_buffer_size) || stream.gcount()))
	pimpl_->parser_status_ = parse_chunk(buffer, stream.gcount());

    if (!pimpl_->parser_status_) return false;
    if (!stream && !stream.eof()) return false;

    return parse_finish();
}
//####################################################################
bool event_parser::parse_chunk (const char *chunk, size_type length) {
    xmlParseChunk(pimpl_->parser_context_, chunk, length, 0);
    return pimpl_->parser_status_;
}
//####################################################################
bool event_parser::parse_finish (void) {
    xmlParseChunk(pimpl_->parser_context_, 0, 0, 0);
    return pimpl_->parser_status_;
}
//####################################################################
epimpl::epimpl (event_parser &parent)
    : parser_status_(true), parent_(parent)
{
    memset(&sax_handler_, 0, sizeof(sax_handler_));

    sax_handler_.startElement = cb_start_element;
    sax_handler_.endElement   = cb_end_element;
    sax_handler_.characters   = cb_text;
    sax_handler_.warning      = cb_error;
    sax_handler_.error        = cb_error;
    sax_handler_.fatalError   = cb_error;
    sax_handler_.cdataBlock   = cb_text;

    if ( (parser_context_ = xmlCreatePushParserCtxt(&sax_handler_, this, 0, 0, 0)) == 0) {
	throw std::bad_alloc();
    }
}
//####################################################################
epimpl::~epimpl (void) {
    xmlFreeParserCtxt(parser_context_);
}
//####################################################################
void epimpl::event_start_element (const xmlChar *tag, const xmlChar **props) {
    event_parser::attrs_type attrs;
    const xmlChar **attrp;

    for (attrp = props; attrp && *attrp; attrp += 2) {       
	attrs[reinterpret_cast<const char*>(*attrp)] = reinterpret_cast<const char*>(*(attrp+1));
    }       

    parser_status_ = parent_.start_element(reinterpret_cast<const char*>(tag), attrs);
}
//####################################################################
void epimpl::event_end_element (const xmlChar *tag) {
    parser_status_ = parent_.end_element(reinterpret_cast<const char*>(tag));
}
//####################################################################
void epimpl::event_text (const xmlChar *text, int length) {
    std::string contents(reinterpret_cast<const char*>(text), static_cast<std::string::size_type>(length));
    parser_status_ = parent_.text(contents);
}
//####################################################################
void epimpl::event_error (void) {
    parser_status_ = false;
}
//####################################################################
namespace {
    //####################################################################
    extern "C" xmlEntityPtr cb_get_entity (void *, const xmlChar *name)
    { return xmlGetPredefinedEntity(name); }
    //####################################################################
    extern "C" void cb_start_element (void *parser, const xmlChar *tag, const xmlChar **props)
    { static_cast<epimpl*>(parser)->event_start_element(tag, props); }
    //####################################################################
    extern "C" void cb_end_element (void *parser, const xmlChar *tag)
    { static_cast<epimpl*>(parser)->event_end_element(tag); }
    //####################################################################
    extern "C" void cb_text (void *parser, const xmlChar *text, int length)
    { static_cast<epimpl*>(parser)->event_text(text, length); }
    //####################################################################
    extern "C" void cb_error (void *parser, const char *, ...)
    { static_cast<epimpl*>(parser)->event_error(); }
} // end anonymous namespace
