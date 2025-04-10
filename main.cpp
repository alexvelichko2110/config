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
    config.print();
    config.save_to_file("./save.json");

    return 0;

    // QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    // return a.exec();
}
