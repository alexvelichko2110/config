// #include "mainwindow.h"

// #include <QApplication>

#include "config.h"

int main(int argc, char *argv[])
{
    // Node *root = new Node();

    // root->append_value("item1", 5);
    // root->append_value("item2", 4.0f);

    // Node *node1 = new Node();

    // node1->append_value("item1", 3);
    // node1->append_value("item2", 8.0f);

    // Node *node2 = new Node();

    // node2->append_value("item1", 6);
    // node2->append_value("item2", 12.0f);

    // root->append_node("node1", node1);
    // root->append_node("node2", node2);

    // root->visit();

    Config config;

    config.load_from_file("./config.json");

    Node* node5 = config.find("/node1/node5");

    std::cout << "node5 " << node5->get_value("item1").as_int() << std::endl;

    Node* node2 = config.find("/node2");

    std::cout << "node2 " << node2->get_value("item1").as_int() << std::endl;


    // config.print();
    config.save_to_file("./config.json");

    return 0;

    // QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    // return a.exec();
}
