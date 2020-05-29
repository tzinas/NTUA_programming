#include <stdio.h>
#include <iostream>
#include<string.h>

using namespace std;

class lexicon {
private:
  struct node{
    string word;
    int num;
    node *left, *right;
  };
  node *root;
public:
  lexicon () {
    root = nullptr;
  }
  ~lexicon () {
    delete root;
  }

  void insert (const string &s) {
    if (root == nullptr) {
      root = new node;
      root -> word = s;
      root -> num = 1;
      root -> left = root -> right = nullptr;
    }
    else {
      node *q = root;
      while (1) {
        if (s.compare(q -> word) == 0) {
          q -> num += 1;
          break;
        }
        else if (s.compare(q -> word) < 0) {
          if (q -> left == nullptr) {
            q -> left = new node;
            node *j = q -> left;
            j -> word = s;
            j -> num = 1;
            j -> left = j -> right = nullptr;
            break;
          }
          q = q -> left;
        }
        else {
          if (q -> right == nullptr) {
            q -> right = new node;
            node *j = q -> right;
            j -> word = s;
            j -> num = 1;
            j -> left = j -> right = nullptr;
            break;
          }
          q = q -> right;
        }
      }
    }
  }
  int lookup (const string &s) const {
    node *q = root;
    while (q != nullptr) {
      if (s.compare(q -> word) == 0) {
        return q -> num;
      }
      else if (s.compare(q -> word) < 0) {
        q = q -> left;
      }
      else {
        q = q -> right;
      }
    }
    return 0;
  }
  int depth (const string &s) const {
    node *q = root;
    int depth = 1;
    while (q != nullptr) {
      if (s.compare(q -> word) == 0) {
        return depth;
      }
      else if (s.compare(q -> word) < 0) {
        depth ++;
        q = q -> left;
      }
      else {
        depth ++;
        q = q -> right;
      }
    }
    return 0;
  }
  void replace (const string &s1, const string &s2) {
    int num_s1 = 0;
    node *q = root;
    node *i = nullptr;
    bool is_left = false;
    while (q != nullptr) {
      if (s1.compare(q -> word) == 0) {
        num_s1 = q -> num;
        if (q -> left == nullptr && q -> right != nullptr) {
          if (i == nullptr) {
            root = q -> right;
            break;
          }
          if (is_left) {
            i -> left = q -> right;
          }
          else {
            i -> right = q -> right;
          }
          break;
        }
        else if (q -> left != nullptr && q -> right == nullptr) {
          if (i == nullptr) {
            root = q -> left;
            break;
          }
          if (is_left) {
            i -> left = q -> left;
          }
          else {
            i -> right = q -> left;
          }
          break;
        }
        else if (q -> left == nullptr && q -> right == nullptr) {
          if (is_left) {
            i -> left = nullptr;
          }
          else {
            i -> right = nullptr;
          }
          break;
        }
        node *j = q -> left;
        node *prev = q;
        while (1) {
          if (j -> right == nullptr) {
            break;
          }
          prev = j;
          j = j -> right;
        }
        if (prev == q) {
          prev -> left = nullptr;
        }
        else {
          prev -> right = nullptr;
        }
        q -> word = j -> word;
        q -> num = j -> num;
        break;
      }
      else if (s1.compare(q -> word) < 0) {
        i = q;
        is_left = true;
        q = q -> left;
      }
      else {
        i = q;
        is_left = false;
        q = q -> right;
      }
    }

    for (int k=1; k<=num_s1; k++) {
      this -> insert(s2);
    }
  }
  void print (ostream &out, node *q, int a = 1) const {
    if(a == 0){
      q = root;
    }
    if (q != nullptr) {
      if (q -> left != nullptr) {
        print(out, q -> left);
      }
      out << q -> word << " " << q -> num << '\n';
      if (q -> right != nullptr) {
        print(out, q -> right);
      }
    }
  }

  friend ostream & operator << (ostream &out, const lexicon &l) {
    l.print(out, nullptr, 0);
    return out;
  }
};
