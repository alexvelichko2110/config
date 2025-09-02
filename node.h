#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <map>

#include <jsoncpp/json/json.h>

#include "value.h"

// class Visitor
// {
// public:
//     virtual ~Visitor()
//     {}

//     Visitor()
//     {}

//     virtual void visit_node(const std::string& name) {}
//     virtual void visit_value(const std::string& key, Value& val) {}
//     // virtual void end() {}
// };

class Node
{
public:

    Value &get_value(const std::string &name)
    {
        return _values[name];
    }

    Node *get_node(const std::string &name)
    {
        if (_nodes.count(name) > 0) {
            // std::cout << "Ключ "<< name << "существует" << std::endl;

            return _nodes[name];
        }
        return nullptr;
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

    void append_value(const std::string &name, int val, int min, int max, int step)
    {
        _values.insert( std::make_pair(name, Value(val, min, max, step)) );
    }

    void append_value(const std::string &name, float val, float min, float max, float step)
    {
        std::cout << name << " val " << val << "min " << min << "max " << max << std::endl;

        _values.insert( std::make_pair(name, Value(val, min, max, step)) );
    }

    void append_value(const std::string &name, const std::string& val)
    {
        _values.insert( std::make_pair(name, Value(val)) );
    }

    Json::Value build_JSON_Value()//std::string & name, Visitor& visitor)
    {
        // std::cout << "node" << std::endl;

        std::map<std::string, Value>::iterator it;

        Json::Value current = Json::Value(Json::objectValue);

        // std::cout << "items:" << std::endl;
        for (it = _values.begin(); it != _values.end(); it++) {
            // std::cout << it->first << ':' << it->second.as_str() << std::endl;
            // visitor.visit_value(it->first, it->second);

            Json::Value item = Json::Value(Json::objectValue);


            Value& val = it->second;

            if (val.get_type() == "int")
            {
                item["type"] = "int";
                item["val"] = val.as_int();
                item["min"] = val.get_int_min();
                item["max"] = val.get_int_max();
                item["step"] = val.get_int_step();
            }
            else
            if (val.get_type() == "float")
            {
                item["type"] = "float";
                item["val"] = val.as_float();
                item["min"] = val.get_float_min();
                item["max"] = val.get_float_max();
                item["step"] = val.get_float_step();
            }
            else
            if (val.get_type() == "str")
            {
                item["type"] = "str";
                item["val"] = val.as_str();
            }

            current[it->first] = item;
        }

        // std::cout << "node name " << name << std::endl;
        std::map<std::string, Node *>::iterator in;
        // std::cout << "nodes:" << std::endl;
        for (in = _nodes.begin(); in != _nodes.end(); in++) {

            // Json::Value child = Json::Value(Json::objectValue);

            current[in->first] = in->second->build_JSON_Value();


            // in->second->visit(in->first, visitor);

            // visitor.visit_node(in->first);

            // visitor.end();

            // visitor.visit_node(in->first);
        }

        // current

        return current;
    }

    void set_parent(Node *node)
    {
        _parent = node;
    }

private:
    Node *_parent;

    std::map<std::string, Value> _values;
    std::map<std::string, Node *> _nodes;

};

#endif // _NODE_H_
