#include "config.h"

void Config::visit_value_json(Json::Value& node, const std::string& key, Node *parent)
{
    // std::cout << "type " << node.type() << std::endl;

    switch (node.type()) {
        case Json::nullValue: {
            std::cout << "null" << std::endl;
        }
        break;
        case Json::booleanValue: {
            // std::cout << (val.asBool() ? "true" : "false");
        }
        break;
        case Json::intValue: {
            // std::cout << "intVal " << val.asInt();

            // parent->append_value(key, val.asInt());
        }
        break;
        // case Json::uintValue: std::cout << val.asUInt();
        // break;
        case Json::realValue: {
            // std::cout << "dblVal " << val.asDouble();

            // parent->append_value(key, (float)val.asDouble());
        }
        break;

        case Json::stringValue: {
            // std::cout << '"' << val.asString() << '"';
        }
        break;

        // case Json::arrayValue: {
        //     Json::ArrayIndex size = node.size();
        //     if (size == 0) {
        //         // std::cout << "[]";
        //     }
        //     else
        //     {
        //         // std::cout << "[\n";
        //         for (Json::ArrayIndex i=0; i<size; i++) {
                    
        //             visit_value_json(node[i], "", parent);
                    
        //             // std::cout << (i + 1 == size ? "\n" : ",\n");
        //         }
        //         // std::cout << ']';
        //     }
        // }
        // break;

        case Json::objectValue: {

            if (node.empty() == false)
            {
                // std::cout << "{" << std::endl;
                
                for (Json::Value::iterator it=node.begin(); it!=node.end(); ++it) {

                    std::string str = it.key().asString();

                    if (it->isMember("type"))
                    {
                        Json::Value& typ = (*it)["type"];

                        std::cout << typ.asString() << std::endl;

                        if (typ.asString() == "int")
                        {
                            Json::Value& val = (*it)["val"];
                            Json::Value& min = (*it)["min"];
                            Json::Value& max = (*it)["max"];
                            Json::Value& step = (*it)["step"];
                            parent->append_value(str,val.asInt(), min.asInt(), max.asInt(), step.asInt());    
                        }
                        else
                        if (typ.asString() == "float")
                        {
                            // Json::Value& val = (*it)["val"];
                            // parent->append_value(str,(float)val.asDouble());    

                            Json::Value& val = (*it)["val"];
                            Json::Value& min = (*it)["min"];
                            Json::Value& max = (*it)["max"];
                            Json::Value& step = (*it)["step"];
                            parent->append_value(str, (float)val.asDouble(), (float)min.asDouble(), (float)max.asDouble(), (float)step.asDouble());    

                        }
                        else
                        if (typ.asString() == "str")
                        {
                            Json::Value& val = (*it)["val"];
                            parent->append_value(str,val.asString());    
                        }


                        // Json::Value& val = (*it)["val"];
                            
                        // if (val.type() == Json::intValue)
                        //     parent->append_value(str,val.asInt());
                        // else
                        // if (val.type() == Json::realValue)
                        //     parent->append_value(str,(float)val.asDouble());                        
                    }
                    else
                    {
                        // std::cout << "\"" << str << "\"" << std::endl;

                        Node *n = new Node();

                        // std::cout << "\"" << str << "\"" << std::endl;

                        visit_value_json(*it, str, n);

                        parent->append_node(str, n);    
                    }
                }
    
                // std::cout << '}' << std::endl;

                // parent->append_node(key, n);
            }
        }
        break;

        default : {
            std::cout << "Wrong type!" << std::endl;
        }
    }
}
