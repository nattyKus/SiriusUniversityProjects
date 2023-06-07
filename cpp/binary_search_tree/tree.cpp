#include <iostream>
#include "tree.h"

KeyValue::KeyValue(int k, int v){
    key = k;
    value = v;
}

bool KeyValue::operator>(const KeyValue &elem){
    if ((value > elem.value) || (value == elem.value) && (key > elem.key)) {
        return true;
    }
    else return false;
}
Node::Node(const KeyValue &new_value){
    left = right = nullptr;
    key = new_value.key;
    value = new_value.value;
}

Node* Node::addNode(Node *root, KeyValue new_value) {
    if (root == nullptr) 
        return new Node(new_value);

    if (new_value > KeyValue(root->key, root->value)){
        root->right = addNode(root->right, new_value);
        return root;
    }
    else if (KeyValue(root->key, root->value) > new_value) {
        root->left = addNode(root->left, new_value);
        return root;
    }
}

void Node::sort_tree(Node *root)
{
    if (!root) {
        return;
    }
    sort_tree(root->left);
    std::cout << "value = " << root->value << ", key = " << root->key << std::endl;
    sort_tree(root->right);
}

void Node::deleteTree(Node *root){
    if(root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
