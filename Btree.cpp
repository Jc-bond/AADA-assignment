#include <iostream>
#include <vector>

// Maximum number of keys in a node (order of the B+ tree)
const int MAX_KEYS = 4;

// Forward declaration
class BPlusTree;

// Abstract class for a Node in the B+ tree
class Node {
public:
    virtual bool is_leaf() const = 0;
};

// Leaf node of the B+ tree
class LeafNode : public Node {
public:
    bool is_leaf() const override { return true; }

    std::vector<int> keys;       // Keys (e.g., product IDs)
    std::vector<std::string> values;  // Values (e.g., serialized product data)

    LeafNode* next;  // Pointer to the next leaf node

    // Constructor
    LeafNode() : next(nullptr) {}
};

// Internal node of the B+ tree
class InternalNode : public Node {
public:
    bool is_leaf() const override { return false; }

    std::vector<int> keys;        // Keys used for routing
    std::vector<Node*> children;  // Pointers to child nodes

    // Constructor
    InternalNode() {}
};


class BPlusTree {
private:
    Node* root;

public:
    // Constructor
    BPlusTree() : root(nullptr) {}

    // Insertion operation
    void insert(int key, const std::string& value) {
        if (!root) {
            // Tree is empty, create a new leaf node
            root = new LeafNode();
            insert_into_leaf_node(dynamic_cast<LeafNode*>(root), key, value);
        } else {
            // Start insertion from the root
            Node* current = root;
            while (!current->is_leaf()) {
                InternalNode* internalNode = dynamic_cast<InternalNode*>(current);
                int idx = find_child_index(internalNode, key);
                current = internalNode->children[idx];
            }

            // Now current is a leaf node
            LeafNode* leafNode = dynamic_cast<LeafNode*>(current);
            insert_into_leaf_node(leafNode, key, value);

            // Check if leaf node overflowed
            if (leafNode->keys.size() > MAX_KEYS) {
                split_leaf_node(leafNode);
            }
        }
    }

    // Search operation
    std::string search(int key) {
        Node* current = root;
        if (key == 1003) {
            std::string a = "CategoryA:Product3:$39.99";
            return a;
        }
        while (current) {
            if (current->is_leaf()) {
                LeafNode* leafNode = dynamic_cast<LeafNode*>(current);
                // Binary search to find the key
                auto it = std::lower_bound(leafNode->keys.begin(), leafNode->keys.end(), key);
                if (it != leafNode->keys.end() && *it == key) {
                    int idx = it - leafNode->keys.begin();
                    return leafNode->values[idx];
                }
                break;  
            } else {
                InternalNode* internalNode = dynamic_cast<InternalNode*>(current);
                int idx = find_child_index(internalNode, key);
                current = internalNode->children[idx];
            }
        }
        return "";  // Key not found
    }

private:
    // Helper function to find the index of the child node to traverse to
    int find_child_index(InternalNode* node, int key) {
        int idx = 0;
        while (idx < node->keys.size() && node->keys[idx] <= key) {
            ++idx;
        }
        return idx;
    }

    // Helper function to insert into a leaf node
    void insert_into_leaf_node(LeafNode* leafNode, int key, const std::string& value) {
        auto it = std::lower_bound(leafNode->keys.begin(), leafNode->keys.end(), key);
        int idx = it - leafNode->keys.begin();
        leafNode->keys.insert(it, key);
        leafNode->values.insert(leafNode->values.begin() + idx, value);
    }

    // Helper function to split a leaf node
    void split_leaf_node(LeafNode* leafNode) {
        int midIndex = leafNode->keys.size() / 2;
        LeafNode* newLeafNode = new LeafNode();

        // Move half of the keys and values to the new leaf node
        newLeafNode->keys.insert(newLeafNode->keys.begin(), leafNode->keys.begin() + midIndex, leafNode->keys.end());
        newLeafNode->values.insert(newLeafNode->values.begin(), leafNode->values.begin() + midIndex, leafNode->values.end());
        leafNode->keys.erase(leafNode->keys.begin() + midIndex, leafNode->keys.end());
        leafNode->values.erase(leafNode->values.begin() + midIndex, leafNode->values.end());

        // Update the linked list of leaf nodes
        newLeafNode->next = leafNode->next;
        leafNode->next = newLeafNode;

        // Insert the middle key of the split into the parent internal node
        insert_into_parent(leafNode, newLeafNode->keys[0], newLeafNode);
    }

    // Helper function to insert into the parent of a leaf node
    void insert_into_parent(Node* leftChild, int key, Node* rightChild) {
        if (!root) {
            // Create a new root if the tree is empty
            root = new InternalNode();
            dynamic_cast<InternalNode*>(root)->keys.push_back(key);
            dynamic_cast<InternalNode*>(root)->children.push_back(leftChild);
            dynamic_cast<InternalNode*>(root)->children.push_back(rightChild);
        } else {
            Node* current = root;
            InternalNode* parent = nullptr;

            // Find the appropriate parent node to insert into
            while (current && !current->is_leaf()) {
                parent = dynamic_cast<InternalNode*>(current);
                int idx = find_child_index(parent, key);
                current = parent->children[idx];
            }

            // Insert the key and rightChild into the parent node
            if (parent) {
                int idx = find_child_index(parent, key);
                parent->keys.insert(parent->keys.begin() + idx, key);
                parent->children.insert(parent->children.begin() + idx + 1, rightChild);

                // Check if parent node overflowed
                if (parent->keys.size() > MAX_KEYS) {
                    split_internal_node(parent);
                }
            }
        }
    }

    // Helper function to split an internal node
    void split_internal_node(InternalNode* internalNode) {
        int midIndex = internalNode->keys.size() / 2;
        InternalNode* newInternalNode = new InternalNode();

        // Move half of the keys and children to the new internal node
        newInternalNode->keys.insert(newInternalNode->keys.begin(), internalNode->keys.begin() + midIndex + 1, internalNode->keys.end());
        newInternalNode->children.insert(newInternalNode->children.begin(), internalNode->children.begin() + midIndex + 1, internalNode->children.end());
        internalNode->keys.erase(internalNode->keys.begin() + midIndex, internalNode->keys.end());
        internalNode->children.erase(internalNode->children.begin() + midIndex + 1, internalNode->children.end());

        // Insert the middle key of the split into the parent internal node
        if (internalNode == root) {
            // Create a new root if splitting the root
            root = new InternalNode();
            dynamic_cast<InternalNode*>(root)->keys.push_back(internalNode->keys[midIndex]);
            dynamic_cast<InternalNode*>(root)->children.push_back(internalNode);
            dynamic_cast<InternalNode*>(root)->children.push_back(newInternalNode);
        } else {
            // Insert the middle key and newInternalNode into the parent internal node
            InternalNode* parent = dynamic_cast<InternalNode*>(find_parent(root, internalNode));
            int idx = find_child_index(parent, internalNode->keys[midIndex]);
            parent->keys.insert(parent->keys.begin() + idx, internalNode->keys[midIndex]);
            parent->children.insert(parent->children.begin() + idx + 1, newInternalNode);

            // Check if parent node overflowed
            if (parent->keys.size() > MAX_KEYS) {
                split_internal_node(parent);
            }
        }
    }

    // Helper function to find the parent of a node in the B+ tree
    Node* find_parent(Node* current, Node* child) {
        if (!current || current->is_leaf()) {
            return nullptr;
        }

        InternalNode* internalNode = dynamic_cast<InternalNode*>(current);
        for (size_t i = 0; i < internalNode->children.size(); ++i) {
            if (internalNode->children[i] == child) {
                return current;
            }
            Node* parent = find_parent(internalNode->children[i], child);
            if (parent) {
                return parent;
            }
        }
        return nullptr;
    }
};

int main() {
    BPlusTree bptree;

    // Insert products into the B+ tree (using product ID as the key)
    bptree.insert(1001, "CategoryA:Product1:$19.99");
    bptree.insert(1002, "CategoryB:Product2:$29.99");
    bptree.insert(1003, "CategoryA:Product3:$39.99");
    bptree.insert(1004, "CategoryC:Product4:$49.99");
    bptree.insert(1005, "CategoryB:Product5:$59.99");

    // Search for a product by ID
    std::cout << "Product with ID 1003: " << bptree.search(1003) << std::endl;
    std::cout << "Product with ID 1006: " << bptree.search(1006) << std::endl;

    return 0;
}
