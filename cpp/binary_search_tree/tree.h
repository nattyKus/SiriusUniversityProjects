struct KeyValue{
    int key;
    int value;

    public:
        KeyValue() = default;
        KeyValue(int k, int v);
        bool operator>(const KeyValue &elem);
};

class Node: public KeyValue{
    Node *left;
    Node *right;

    public:
        Node() = default;
        Node(const KeyValue &new_value);
        Node* addNode(Node *root, KeyValue new_value);
        void sort_tree(Node *root);
        void deleteTree(Node *root);
};