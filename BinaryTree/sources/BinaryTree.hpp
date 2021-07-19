#pragma once
#include<iostream>
#include <queue>
#include<array>


using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
        /* Node struct */
        struct Node
        {
            T data;
            Node* parent;
            Node* left;
            Node* right;

            Node(T d, Node* p=nullptr):data(d), left(nullptr), right(nullptr), parent(p){}
        };

    private:
        Node* root;
        /* help method for: add_left, add_right */
        Node& find_node(T d){
            queue<Node*> q;
            q.push(root);
            Node* n = nullptr;
            while (!q.empty())
            {
                n = q.front();
                q.pop();
                if (n != nullptr){
                    if (n->data == d){break;}
                    q.push(n->left);
                    q.push(n->right);
                }
            }
            return *n;
        }

    public:
        BinaryTree():root(nullptr){}
        BinaryTree(const BinaryTree &tree) {
            root = new Node{tree.root->data};
            set_tree(root, tree.root);
        }

        BinaryTree(BinaryTree &&tree) noexcept{
            root = tree.root;
            tree.root = nullptr;
        }

        ~BinaryTree(){
            for (auto it=(*this).begin_preorder(); it!=(*this).end_preorder(); ++it) {
                delete it.get_node();
            }
        }

        /* add root for the tree */
        BinaryTree& add_root(T r){
            if (root == nullptr){root = new Node(r);}
            else{root->data = r;}
            return *this;
        }

        BinaryTree& operator=( BinaryTree tree){
            if(this == &tree){return *this;}
            if(root != nullptr){
                for (auto it=(*this).begin_preorder(); it!=(*this).end_preorder(); ++it) {
                    delete it.get_node();
                }
            }
            root = nullptr;
            if (tree.root != nullptr){
                root = new Node(tree.root->data);
                set_tree(root, tree.root);
            }
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& tree) noexcept{
            for (auto it=(*this).begin_preorder(); it!=(*this).end_preorder(); ++it) {
                delete it.get_node();
            }

            root = tree.root;
            tree.root = nullptr;
            return *this;
        }

        void set_tree(Node* n1, Node* n2){
            if (n2->left != nullptr){
                n1->left = new Node(n2->left->data);
                set_tree(n1->left, n2->left);
            }
            if (n2->right != nullptr){
                n1->right = new Node(n2->right->data);
                set_tree(n1->right, n2->right);
            }
        }


        /* add left child for the patent */
        BinaryTree& add_left(T parent, T child){
            if (root == nullptr){throw invalid_argument("there is no root");}

            Node* n = &find_node(parent);
            if (n == nullptr){throw invalid_argument("there is no parent");}

            if (n->left == nullptr){n->left = new Node(child);}
            else{n->left->data = child;}

            return *this;
        }

        /* add right child for the patent */
        BinaryTree& add_right(T parent, T child){
            if (root == nullptr){throw invalid_argument("there is no root");}

            Node* n = &find_node(parent);
            if (n == nullptr){throw invalid_argument("there is no parent");}

            if (n->right == nullptr){n->right = new Node(child);}
            else{n->right->data = child;}

            return *this;
        }

        /* =============================== */
        /*     preorder iterator class     */
        /* =============================== */
        class iterator_preorder
        {
        private:
            vector<Node*> vec;
            size_t count = 0;
            Node* node;

        public:

            iterator_preorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
                node = vec.at(count);
            }

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    vec.push_back(n);
                    set_vec(n->left);
                    set_vec(n->right);
                }
            }

            T &operator*() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return node->data;
            }
            T *operator->() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return &(node->data);
            }

            // ++i;
            iterator_preorder &operator++(){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                ++count;
                node = vec.at(count);
                return *this;
            }
            // i++;
            iterator_preorder operator++(int){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                iterator_preorder it = *this;
                count++;
                node = vec.at(count);
                return it;
            }
            bool operator==(const iterator_preorder &rhs) const {
                return node == rhs.node;
            }
            bool operator!=(const iterator_preorder &rhs) const {
                return node != rhs.node;
            }
            Node* get_node(){return node;}

        };


        /* =============================== */
        /*      inorder iterator class     */
        /* =============================== */
        class iterator_inorder
        {

        private:
            vector<Node*> vec;
            size_t count = 0;
            Node* node;

        public:

            iterator_inorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
                node = vec.at(count);
            }

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    set_vec(n->left);
                    vec.push_back(n);
                    set_vec(n->right);
                }
            }

            T &operator*() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return node->data;
            }
            T *operator->() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return &(node->data);
            }

            // ++i;
            iterator_inorder &operator++(){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                ++count;
                node = vec.at(count);
                return *this;
            }
            // i++;
            iterator_inorder operator++(int){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                iterator_inorder it = *this;
                count++;
                node = vec.at(count);
                return it;
            }
            bool operator==(const iterator_inorder &rhs) const {
                return node == rhs.node;
            }
            bool operator!=(const iterator_inorder &rhs) const {
                return node != rhs.node;
            }
            Node* get_node(){return node;}

        };


        /* =============================== */
        /*     postorder iterator class    */
        /* =============================== */
        class iterator_postorder
        {
        private:
            vector<Node*> vec;
            size_t count = 0;
            Node* node;

        public:

            iterator_postorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
                node = vec.at(count);
            }

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    set_vec(n->left);
                    set_vec(n->right);
                    vec.push_back(n);
                }
            }

            Node* get_node(){return node;}

            T &operator*() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return node->data;
            }
            T *operator->() const {
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                return &(node->data);
            }

            // ++i;
            iterator_postorder &operator++(){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                ++count;
                node = vec.at(count);
                return *this;
            }
            // i++;
            iterator_postorder operator++(int){
                if (node == nullptr){throw invalid_argument("unit not exeist");}
                iterator_postorder it = *this;
                count++;
                node = vec.at(count);
                return it;
            }
            bool operator==(const iterator_postorder &rhs) const {
                return node == rhs.node;
            }
            bool operator!=(const iterator_postorder &rhs) const {
                return node != rhs.node;
            }
        };


        /* begin & end preorder */
        iterator_preorder begin_preorder(){
            return iterator_preorder{root};
        }
        iterator_preorder end_preorder(){
            return iterator_preorder{nullptr};
        }

        /* begin & end inorder */
        iterator_inorder begin_inorder(){
            return iterator_inorder{root};
        }
        iterator_inorder end_inorder(){
            return iterator_inorder{nullptr};
        }

        /* begin & end postorder */
        iterator_postorder begin_postorder(){
            return iterator_postorder{root};
        }
        iterator_postorder end_postorder(){
            return iterator_postorder{nullptr};
        }

        /* General begin & end */
        iterator_inorder begin(){return this->begin_inorder();}
        iterator_inorder end(){return this->end_inorder();}

        friend std::ostream &operator<<(std::ostream &out, BinaryTree<T> &t) {
            return out;
        }

    };

}