#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>

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

    Node* find(std::string& path) {
        return nullptr;
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

    class JsonSaveVisitor : public Visitor
    {
    public:
        JsonSaveVisitor() : Visitor()
        {
            root = Json::Value(Json::objectValue); 

            parent = &root;
            current = parent;
        }

        virtual void visit_node(const std::string& name) {
            Json::Value object = Json::Value(Json::objectValue); 

            (*parent)[name] = object;
            current = &(*parent)[name];
        }
        
        virtual void visit_value(const std::string& key, Value& val) {

            (*current)[key] = val.as_str();
        }

        Json::Value* current;
        Json::Value* parent;
        Json::Value root;
    };


    void save_to_file(const std::string& file_name) {
        
        std::ofstream f;
        f.open(file_name);
    
        JsonSaveVisitor visitor;

        _root->visit(visitor);

        Json::StyledWriter styledWriter;
        f << styledWriter.write(visitor.root);
    
        f.close();
    }

    class PrintVisitor : public Visitor
    {
    public:

        virtual void visit_node(const std::string& name) {
            std::cout << " >>> node " << name << std::endl;
        }
        
        virtual void visit_value(const std::string& key, Value& val) {
            std::cout << "      key " << key << " val " << val.as_str() << std::endl;
        }
    };

    void print() {
        PrintVisitor visitor;
        _root->visit(visitor);
    }

private:

    void visit_value_json(Json::Value& val, const std::string& key, Node *parent);
    
    Node* _root;
};


#endif // _CONFIG_H_
