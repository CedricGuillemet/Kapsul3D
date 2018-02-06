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
 * This file contains the definition of the xml::node class.
**/

#ifndef __xmlwrapp_node_h__
#define __xmlwrapp_node_h__
#ifdef KAPSUL_EXPORT
	#define KAPSUL_DESC __declspec(dllexport)
#else
	#define KAPSUL_DESC __declspec(dllimport)
#endif

#include <stddef.h>
// standard includes
#include <iosfwd>
#include <string>
#include <map>

//namespace xml {
    struct nipimpl; // forward declaration

/**
 * The xml::node class is used to hold information about one XML node. This
 * includes the name of the node, the namespace of the node and attributes
 * for the node. It also has an iterator whereby you can get to the children
 * nodes.
 *
 * It should be noted that any member function that returns a const char*
 * returns a temporary value. The pointer that is returned will change with
 * ANY operation to the xml::node. If you need the data to stick around a
 * little longer you should put it inside a std::string.
**/
class KAPSUL_DESC node {
public:
    /// a type for holding xml::node attributes.
    typedef std::map<std::string, std::string> attrs_type;

    //####################################################################
    /** 
     * Construct a new blank xml::node.
     *
     * @author Peter Jones
    **/
    //####################################################################
    node (void);

    //####################################################################
    /** 
     * Construct a new xml::node and set the name of the node.
     *
     * @param name The name of the new node.
     * @author Peter Jones
    **/
    //####################################################################
    explicit node (const char *name);

    //####################################################################
    /** 
     * Construct a new xml::node given a name and content. The content will
     * be used to create a new child text node.
     *
     * @param name The name of the new element.
     * @param content The text that will be used to create a child node.
     * @author Peter Jones
    **/
    //####################################################################
    node (const char *name, const char *content);

    //####################################################################
    /** 
     * Construct a new xml::node by coping another xml::node.
     *
     * @param other The other node to copy.
     * @author Peter Jones
    **/
    //####################################################################
    node (const node &other);

    //####################################################################
    /** 
     * Make this node equal to some other node via assignment.
     *
     * @param other The other node to copy.
     * @return A reference to this node.
     * @author Peter Jones
    **/
    //####################################################################
    node& operator= (const node &other);

    //####################################################################
    /** 
     * Class destructor
     *
     * @author Peter Jones
    **/
    //####################################################################
    ~node (void);

    //####################################################################
    /** 
     * Set the name of this xml::node.
     *
     * @param name The new name for this xml::node.
     * @author Peter Jones
    **/
    //####################################################################
    void set_name (const char *name);

    //####################################################################
    /** 
     * Get the name of this xml::node.
     *
     * @return The name of this node.
     * @author Peter Jones
    **/
    //####################################################################
    const char* get_name (void) const;

    //####################################################################
    /** 
     * Set the content of a node, to make this node a text node.
     *
     * @param content The content of the text node.
     * @author Peter Jones
    **/
    //####################################################################
    void set_content (const char *content);

    //####################################################################
    /** 
     * Get the content for this text node. If this node is not a text node
     * but it has one child node that is a text node, the content of that
     * child node will be returned. If there is no content or these
     * conditions do not apply, zero will be returned.
     *
     * @return The content or 0.
     * @author Peter Jones
    **/
    //####################################################################
    const char* get_content (void) const;

    //####################################################################
    /** 
     * Set the namespace for this xml::node.
     *
     * @param ns The namespace to set for this node.
     * @author Peter Jones
    **/
    //####################################################################
    void set_namespace (const char *ns);

    //####################################################################
    /** 
     * Get the namespace for this xml::node.
     *
     * @return The namespace for this node.
     * @author Peter Jones
    **/
    //####################################################################
    const char* get_namespace (void) const;

    //####################################################################
    /** 
     * Set the given node attribute to the given value.
     *
     * @param name The name of the attribute to set.
     * @param value The value of the attribute.
     * @author Peter Jones
    **/
    //####################################################################
    void set_attr (const char *name, const char *value);

    //####################################################################
    /** 
     * Get the value of the given attribute. If the attribute does not
     * exist, this member function will return 0.
     *
     * @param name The name of the attribute that you want the value of.
     * @return The value of the attribute or 0 if not found.
     * @author Peter Jones
    **/
    //####################################################################
    const char* get_attr (const char *name) const;

    //####################################################################
    /** 
     * Get the value of the given attribute. The value is stored in the
     * given string.
     *
     * @param name The name of the attribute you want the value of.
     * @param value A string to store the value in.
     * @return True is the attribute exists and was stored in value, false
     * otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool get_attr (const char *name, std::string &value) const;
	bool get_attr (const char *name, char *value) const;

    //####################################################################
    /** 
     * Remove the given attribute. If the attribute does not exist nothing
     * happens.
     *
     * @param name The name of the attribute to remove.
     * @author Peter Jones
    **/
    //####################################################################
    void remove_attr (const char *name);

    //####################################################################
    /** 
     * Find out if this node is a text node.
     *
     * @return True if this node is a text node; false otherwise.
     * @author Peter Jones
    **/
    //####################################################################
    bool is_text (void) const;

    //####################################################################
    /** 
     * Add a child xml::node to this node.
     *
     * @param child The child xml::node to add.
     * @author Peter Jones
    **/
    //####################################################################
    void push_back (const node &child);

    //####################################################################
    /** 
     * Swap this node with another one.
     *
     * @param other The other node to swap with.
     * @author Peter Jones
    **/
    //####################################################################
    void swap (node &other);

    class const_iterator; // forward declaration

    class KAPSUL_DESC iterator {
    public:
	typedef node value_type;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef std::forward_iterator_tag iterator_category;

	iterator  (void);
	iterator  (const iterator &other);
	iterator& operator= (const iterator& other);
	~iterator (void);

	reference operator*  (void) const;
	pointer   operator-> (void) const;

	iterator& operator++ (void);
	iterator  operator++ (int);

	friend bool operator== (const iterator &lhs, const iterator &rhs);
	friend bool operator!= (const iterator &lhs, const iterator &rhs);
    private:
	nipimpl *pimpl_;
	explicit iterator (void *data);
	void swap (iterator &other);
	friend class node;
	friend class const_iterator;
    };

    class KAPSUL_DESC const_iterator {
    public:
	typedef const node value_type;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef std::forward_iterator_tag iterator_category;

	const_iterator  (void);
	const_iterator  (const const_iterator &other);
	const_iterator  (const iterator &other);
	const_iterator& operator= (const const_iterator& other);
	~const_iterator (void);

	reference operator*  (void) const;
	pointer   operator-> (void) const;

	const_iterator& operator++ (void);
	const_iterator  operator++ (int);

	friend bool operator== (const const_iterator &lhs, const const_iterator &rhs);
	friend inline bool KAPSUL_DESC operator!= (const const_iterator &lhs, const const_iterator &rhs);
    private:
	nipimpl *pimpl_;
	explicit const_iterator (void *data);
	void swap (const_iterator &other);
	friend class node;
    };

    //####################################################################
    /** 
     * Get an iterator that points to the begining of this node's children.
     *
     * @return An iterator that points to the begining of the children.
     * @author Peter Jones
    **/
    //####################################################################
    iterator begin (void);

    //####################################################################
    /** 
     * Get a const_iterator that points to the begining of this node's
     * children.
     *
     * @return A const_iterator that points to the begining of the children.
     * @author Peter Jones
    **/
    //####################################################################
    const_iterator begin (void) const;

    //####################################################################
    /** 
     * Get an iterator that points one past the last child for this node.
     *
     * @return A "one past the end" iterator.
     * @author Peter Jones
    **/
    //####################################################################
    iterator end (void);

    //####################################################################
    /** 
     * Get a const_iterator that points one past the last child for this
     * node.
     *
     * @return A "one past the end" const_iterator
     * @author Peter Jones
    **/
    //####################################################################
    const_iterator end (void) const;

    //####################################################################
    /** 
     * Convert the node and all its children into XML text and set the given
     * string to that text.
     *
     * @param xml The string to set the node's XML data to.
     * @author Peter Jones
    **/
    //####################################################################
    void node_to_string (std::string &xml) const;

    //####################################################################
    /** 
     * Write a node and all of its children to the given stream.
     *
     * @param stream The stream to write the node as XML.
     * @param n The node to write to the stream.
     * @return The stream.
     * @author Peter Jones
    **/
    //####################################################################
    friend std::ostream& operator<< (std::ostream &stream, const node &n);
private:
    struct pimpl; pimpl *pimpl_;
    void set_node_data (void *data);
    void *get_node_data (void);
    friend class tree_parser;
    friend class node_iterator;
}; // end xml::node class

//} // end xml namespace
#endif
