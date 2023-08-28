/*
 * If you modify this file, replace this with your own header
 * Otherwise, leave this file and this comment as-is
 */

#ifndef BINTREE_DATA_H
#define BINTREE_DATA_H

#include <string>
using std::string;

struct Data {
    int id;
    string information;
};

struct DataNode {
    Data data;
    DataNode *left, *right;
};

#endif /* DATA_H */
