#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <map>

#include "value.h"

class Visitor
{
public:
    virtual ~Visitor()
    {}

    Visitor()
    {}

    virtual void visit_node(const std::string& name) {}
    virtual void visit_value(const std::string& key, Value& val) {}
    // virtual void end(const std::string& key, Value& val) {}
};

class Node
{
public:

    Value &get_value(const std::string &name)
    {
        return _values[name];
    }

    Node *get_node(const std::string &name)
    {
        return _nodes[name];
    }

    void append_node(const std::string &name, Node *node)
    {
        node->set_parent(this);

        _nodes.insert( std::make_pair(name, node) );
    }

    void remove_node(const std::string &name)
    {
        _nodes.erase(name);
    }

    void append_value(const std::string &name, int val)
    {
        _values.insert( std::make_pair(name, Value(val, 0, 5, 1)) );
    }

    void append_value(const std::string &name, float val)
    {
        _values.insert( std::make_pair(name, Value(val, 0.0, 5.0, 1.0)) );
    }

    void append_value(const std::string &name, const std::string& val)
    {
        _values.insert( std::make_pair(name, Value(val)) );
    }

    void visit(Visitor& visitor)
    {
        // std::cout << "node" << std::endl;

        std::map<std::string, Value>::iterator it;

        // std::cout << "items:" << std::endl;
        for (it = _values.begin(); it != _values.end(); it++) {
            // std::cout << it->first << ':' << it->second.as_str() << std::endl;
            visitor.visit_value(it->first, it->second);
        }

        std::map<std::string, Node *>::iterator in;
        // std::cout << "nodes:" << std::endl;
        for (in = _nodes.begin(); in != _nodes.end(); in++) {
            visitor.visit_node(in->first);

            in->second->visit(visitor);

            // visitor.visit_node(in->first);
        }
    }

    void set_parent(Node *node)
    {
        _parent = node;
    }

private:
    Node *_parent;

    std::map<std::string, Node *> _nodes;
    std::map<std::string, Value> _values;
};

#endif // _NODE_H_
