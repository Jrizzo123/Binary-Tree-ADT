#include "bintree.h"

BinTree::BinTree() {
	root = NULL;
    count = 0;
}

BinTree::~BinTree() {
    clear();
}

void BinTree::displayInOrder() { //public
	displayInOrder(root);
}

void BinTree::displayInOrder(DataNode* temproot) { //private overload
    if (temproot) {
        if (temproot->left) {
            displayInOrder(temproot->left);
        }
        cout << temproot->data.id << " " << temproot->data.information << endl;
        if (temproot->right) {
            displayInOrder(temproot->right);
        }
    }

    return;
}

void BinTree::displayPreOrder() { //public
    displayPreOrder(root);
}
void BinTree::displayPreOrder(DataNode* temproot) { //private
    if (temproot) {
        cout << temproot->data.id << " " << temproot->data.information << endl;
        if (temproot->left) {
            displayPreOrder(temproot->left);
        }
        if (temproot->right) {
            displayPreOrder(temproot->right);
        }
    }

    return;
}

void BinTree::displayPostOrder() { //public
    displayPostOrder(root);
}
void BinTree::displayPostOrder(DataNode* temproot) { //private
    if (temproot) {
        if (temproot->left) {
            displayPostOrder(temproot->left);
        }
        if (temproot->right) {
            displayPostOrder(temproot->right);
        }
        cout << temproot->data.id << " " << temproot->data.information << endl;
    }

    return;
}
int BinTree::getCount() {
    return count;
}

bool BinTree::isEmpty() {
    bool result{ false };
    if (!root) {
        result = true;
    }
    return result;
}

bool BinTree::getRootData(Data* tempdata) {

    bool result{ false };

    if (!root) {
        result = false;
        tempdata->id = -1;
        tempdata->information = "";
    }
    else {
        result = true;
        tempdata->id = root->data.id;
        tempdata->information = root->data.information;
    }

    return result;
}

bool BinTree::addNode(int id, string information) { //public
    bool result{ false };

    if (id > 0 && !information.empty()) {


        DataNode* newNode = new DataNode; //segmentation fault if it's not allocated
        newNode->data.id = id;
        newNode->data.information = information;

        if (addNode(newNode, &root)) {
            result = true;
            count = count + 1;
        }
        else {
            result = false;
        }
    }

    return result;
}
bool BinTree::addNode(DataNode* newNode, DataNode** temproot) { //private
    bool result{ false };

    if (!(*temproot)) { //if temproot is null
        (*temproot) = newNode;
        (*temproot)->left = NULL;
        (*temproot)->right = NULL;
        result = true;
    }
    else if (newNode->data.id < (*temproot)->data.id) { 
        addNode(newNode, &(*temproot)->left);
        result = true;
    }
    else if (newNode->data.id > (*temproot)->data.id) {
        addNode(newNode, &(*temproot)->right);
        result = true;
    }

    return result;
}

bool BinTree::contains(int id) { //public
    bool result{ false };
    if (id > 0) {
        result = contains(id, root);
    }
    else {
        result = false;
    }
    return result;
}
bool BinTree::contains(int id, DataNode* temproot) { //private
    bool result{ false };
    if (!temproot) {
        result = false;
    }
    else {
        if (id == temproot->data.id) {
            result = true;
        }
        else if (id < temproot->data.id) {
            result = contains(id, temproot->left); 
        }
        else if (id > temproot->data.id) {
            result = contains(id, temproot->right);

        }
    }
    return result;
}

bool BinTree::getNode(Data* tempdata, int id) { //public
    bool result{ false };

    if (id > 0) {
        result = getNode(tempdata, id, root);
    }
    else {
        result = false;
    }
    return result;
}
bool BinTree::getNode(Data* tempdata, int id, DataNode* temproot) { //private
    bool result{ false };
    if (!temproot) {
        result = false;
    }
    else {
        if (id == temproot->data.id) {
            result = true;
            tempdata->id = temproot->data.id;
            tempdata->information = temproot->data.information;
        }
        if (id < temproot->data.id) {
            result = getNode(tempdata, id, temproot->left);
        }
        if (id > temproot->data.id) {
            result = getNode(tempdata, id, temproot->right);
        }
    }
    return result;
}

int BinTree::getHeight() { //public
    return getHeight(root);
}
//getHeight is most likely longer than it needs to be, but I could not find another way without going too deeply into it
int BinTree::getHeight(DataNode* temproot) { //private
    int lh{ 0 };
    int rh{ 0 };
    int result{ 0 };

    if (!temproot) {
        result = 0;
    }
    else {
        lh = getHeight(temproot->left);
        rh = getHeight(temproot->right);
        if (lh > rh) {
            result = lh + 1;
        }
        else { //saving another conditional, if lh is not > rh, than either rh is greater, or they're equal, either way return rh
            result = rh + 1;
        }
    }
    return result;
}

//sets root to NULL because private overload would not delete the actual root, and would give errors in code
void BinTree::clear() { //public
    clear(root);
    root = NULL;
    count = 0;
}
void BinTree::clear(DataNode* temproot) { //private
    if (!temproot) {
        return;
    }
    else {
        clear(temproot->left);
        clear(temproot->right);
        temproot->left = NULL;
        temproot->right = NULL;
        delete temproot;
    }
}
bool BinTree::removeNode(int id) { //private
    int tempcount{ count };
    bool result{ false };
    root = removeNode(id, root);
    if (count < tempcount) {
        result = true;
    }
    else {
        result = false;
    }
    return result;
}
DataNode* BinTree::removeNode(int id, DataNode* temproot) { //public
    if (temproot) {
        if (id < temproot->data.id) {
            temproot->left = removeNode(id, temproot->left);
        }
        else if (id > temproot->data.id) {
            temproot->right = removeNode(id, temproot->right);
        }
        else {
            DataNode* temp;
            if (temproot->left == NULL) {
                temp = temproot->right;

                delete temproot;

                temproot = temp;
                count--;
            }
            else if (temproot->right == NULL) {
                temp = temproot->left;

                delete temproot;

                temproot = temp;
                count--;
            }
            else {
                temp = minValueNode(temproot->right);
                temproot->data.id = temp->data.id;
                temproot->data.information = temp->data.information;

                temproot->right = removeNode(temp->data.id, temproot->right);
            }
        }
    }
    return temproot;
}

DataNode* BinTree::minValueNode(DataNode* node) { //private helper method
    DataNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

void BinTree::displayTree() { //public display tree method calls other public display methods
    cout << "DISPLAY TREE" << endl << "==============================================" << endl;

    if (isEmpty()) {
        cout << "Tree is empty";
    }
    else {
        cout << "Tree is not empty";
    }
    cout << endl << "Height " << getHeight();
    cout << endl << "Node count: " << getCount() << endl << endl;
    cout << "Pre-Order Traversal" << endl << endl;
    displayPreOrder();
    cout << endl << "In-Order Traversal" << endl << endl;
    displayInOrder();
    cout << endl <<"Post-Order Traversal" << endl << endl;
    displayPostOrder();
    cout << endl;

}
