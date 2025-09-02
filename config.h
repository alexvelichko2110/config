#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>

#include <jsoncpp/json/json.h>

#include "value.h"
#include "node.h"

class Config
{
public:
    virtual ~Config()
    {
        // delete _root;
    }
    
    Config()
    {
        _root = new Node();
    }

    template <typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim)) {
            *result++ = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    Node* find(const std::string& path) {

        std::vector<std::string> x = split(path, '/');

        std::vector<std::string>::iterator it;

        Node *n = _root;

        for (it = x.begin(); it != x.end(); it++) {
            Node* sub = n->get_node(*it);

            if (sub) {
                n = sub;
            }
        }
       
        return n;
    }

    void load_from_file(const std::string& file_name) {

        Json::Value root;
        Json::Reader reader;

        std::ifstream f(file_name);
        
        bool successful = reader.parse(f, root );

        if (successful)
        {
            visit_value_json(root, "root", _root);
        }
    }

    // class JsonSaveVisitor : public Visitor
    // {
    // public:
    //     JsonSaveVisitor() : Visitor()
    //     {
    //         root = Json::Value(Json::objectValue); 

    //         parent = &root;
    //         //current = parent;
    //     }

    //     virtual void visit_node(const std::string& name) {

    //         std::cout << "node name " << name << std::endl;

    //         Json::Value object = Json::Value(Json::objectValue); 

    //         (*parent)[name] = object;
    //         current = &(*parent)[name];

    //         // top = parent;

    //         parent = current;
    //     }
        
    //     virtual void visit_value(const std::string& key, Value& val) {

    //         Json::Value object = Json::Value(Json::objectValue);
            
    //         object["val"] = val.as_str();

    //         (*current)[key] = object;
    //     }

    //     // virtual void end() {

    //     //     // parent = top;
    //     // }

    //     // Json::Value* top;
    //     Json::Value* current;
    //     Json::Value* parent;
    //     Json::Value root;
    // };


    void save_to_file(const std::string& file_name) {
        
        std::ofstream f;
        f.open(file_name);
    
        // JsonSaveVisitor visitor;

        // _root->visit(visitor);

        Json::Value root = _root->build_JSON_Value();

        Json::StyledWriter styledWriter;
        f << styledWriter.write(root);
    
        f.close();
    }

    // class PrintVisitor : public Visitor
    // {
    // public:

    //     virtual void visit_node(const std::string& name) {
    //         std::cout << " >>> node " << name << std::endl;
    //     }
        
    //     virtual void visit_value(const std::string& key, Value& val) {
    //         std::cout << "      key " << key << " val " << val.as_str() << std::endl;
    //     }
    // };

    // void print() {
    //     PrintVisitor visitor;
    //     _root->visit(visitor);
    // }

private:

    void visit_value_json(Json::Value& val, const std::string& key, Node *parent);
    
    Node* _root;
};


#endif // _CONFIG_H_
