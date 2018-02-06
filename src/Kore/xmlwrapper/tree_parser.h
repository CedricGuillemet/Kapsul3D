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
 * This file contains the definition of the xml::tree_parser class.
**/

#ifndef __xmlwrapp_tree_parser_h__
#define __xmlwrapp_tree_parser_h__
#ifdef KAPSUL_EXPORT
	#define KAPSUL_DESC __declspec(dllexport)
#else
	#define KAPSUL_DESC __declspec(dllimport)
#endif

// include string to get std::size_t (FIXME)
#include <string>

//namespace xml {
    class node; // forward declaration

/**
 * The xml::tree_parser class is used to parse an XML document and generate
 * a tree like structure of xml::node objects. After constructing a
 * tree_parser, with either a file to parse or some in memory data to parse,
 * you can walk the tree using the xml::node interface.
**/
class KAPSUL_DESC tree_parser {
public:
    typedef size_t size_type;

    //####################################################################
    /** 
     * xml::tree_parser class constructor. Given the name of a file, this
     * constructor will parse that file. To see if the file was parsed
     * successfully use operator!.
     *
     * @param filename The name of the file to parse.
     * @author Peter Jones
    **/
    //####################################################################
    tree_parser (const char *filename);

    //####################################################################
    /** 
     * xml::tree_parser class constructor. Given some data and the size of
     * that data, parse that data as XML. To see if the data was parsed
     * successfully use operator!.
     *
     * @param data The XML data to parse.
     * @param size The size of the XML data to parse.
     * @author Peter Jones
    **/
    //####################################################################
    tree_parser (const char *data, size_type size);

    //####################################################################
    /** 
     * xml::tree_parser class destructor.
     *
     * @author Peter Jones
    **/
    //####################################################################
    ~tree_parser (void);

    //####################################################################
    /** 
     * Check to see if a xml::tree_parser class is vaild. That is, check to
     * see if parsing XML data was successful and the tree_parser holds a
     * good XML node tree.
     *
     * @return True if the tree_parser is NOT VAILD; false if it is vaild.
     * @author Peter Jones
    **/
    //####################################################################
    bool operator! (void) const;

    //####################################################################
    /** 
     * Get the root node of the tree. This member function is only vaild if
     * the XML data was parsed successfully. You can check this by using
     * operator!.
     *
     * @return The root node.
     * @author Peter Jones
    **/
    //####################################################################
    node& get_root_node (void);
private:
    struct pimpl; pimpl *pimpl_; // private implementation

    /* 
     * Don't allow anyone to copy construct a xml::tree_parser or allow the
     * assignment operator to be called. It is not very useful to copy a
     * parser that has already parsed half a document.
     */
    tree_parser (const tree_parser&);
    tree_parser& operator= (const tree_parser&);
}; // end xml::tree_parser class

//} // end xml namespace
#endif
