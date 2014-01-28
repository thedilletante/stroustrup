#include <iostream>
#include <string>

struct Tnode
{
  std::string word;
  int count;
  Tnode* left;
  Tnode* rigth;
};

Tnode* insert(const std::string & word, Tnode* tree) {
  if (word == tree->word) {
    ++tree->count;
    return tree;
  }
  else if (word < tree->word) {
    if (tree->left == 0 || word > tree->left->word) {
      Tnode * node = new Tnode();
      node->word = word;
      node->count = 1;
      node->left = tree->left;
      node->rigth = tree;
      tree->left = node;
      if (node->left) {
        node->left->rigth = node;
      }
      return node;
    }
    else {
      return insert(word, tree->left);
    }
  }
  else if (word > tree->word) {
    if (tree->rigth == 0 || word < tree->rigth->word) {
      Tnode * node = new Tnode();
      node->word = word;
      node->count = 1;
      node->left = tree;
      node->rigth = tree->rigth;
      tree->rigth = node;
      if (node->rigth) {
        node->rigth->left = node;
      }
      return node;
    }
    else {
      return insert(word, tree->rigth);
    }
  }
}

void print(Tnode * tree, const Tnode * from = 0) {
  std::cout<<tree->word<<" : "<<tree->count<<std::endl;
  if (tree->left && tree->left != from) {
    print(tree->left, tree);
  }
  if (tree->rigth && tree->rigth != from) {
    print(tree->rigth, tree);
  }
}

void sortPrint(Tnode * tree, const Tnode * from = 0) {
  if (tree->left && tree->left != from) {
    sortPrint(tree->left, tree);
  }
  std::cout<<tree->word<<" : "<<tree->count<<std::endl;
  if (tree->rigth && tree->rigth != from) {
    sortPrint(tree->rigth, tree);
  }
}

int main() {
  Tnode * node = new Tnode();
  node->word = "hello";
  node->count = 1;

  insert("hello", node);
  insert("beu", node);
  insert("sdf", node);
  insert("beudf", node);
  insert("beu", node);
  insert("besdf", node);
  insert("asdsf", node);

  print(node);
  std::cout<<"______Sort Print______"<<std::endl;
  sortPrint(node);
  return 0;
}