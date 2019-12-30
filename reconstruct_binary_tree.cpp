#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>

template<typename T>
class node final {
public:
  T data;
  node<T> *left;
  node<T> *right;

  explicit node(T data) : data(std::move(data)) {
    left = right = nullptr;
  }
};

enum class order {
  pre = 0, in, post, level
};

template<typename T, order order>
void treelist(node<T> *root, std::vector<T> &list) {
  if (!root) return;
  if constexpr (order == order::level) {
    std::queue<node<T> *> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto n = queue.front();
      queue.pop();
      list.push_back(n->data);
      if (n->left) queue.push(n->left);
      if (n->right) queue.push(n->right);
    }
  } else {
    //@formatter:off
    if constexpr  (order == order::pre)   list.push_back(root->data);
    if            (root->left)            treelist<T, order>(root->left, list);
    if constexpr  (order == order::in)    list.push_back(root->data);
    if            (root->right)           treelist<T, order>(root->right, list);
    if constexpr  (order == order::post)  list.push_back(root->data);
    //@formatter:on
  }
}

template<typename T, order order>
std::vector<T> treelist(node<T> *root) {
  std::vector<T> list;
  treelist<T, order>(root, list);
  return list;
}

template<typename T>
std::string join(std::vector<T> &elems) {
  std::ostringstream result;
  bool first = true;
  for (auto &e : elems) {
    if (first) first = false;
    else result << ", ";
    result << e;
  }
  return result.str();
}

template<typename T>
bool compare_tree(node<T> *a, node<T> *b) {
  if (a == b) return true;
  if (a == nullptr || b == nullptr) return false;
  if (a->data != b->data) return false;
  return compare_tree(a->left, b->left) && compare_tree(a->right, b->right);
}

template<typename T>
void print_tree_orders(node<T> *tree) {
  auto pre_order = treelist<T, order::pre>(tree);
  auto in_order = treelist<T, order::in>(tree);
  auto post_order = treelist<T, order::post>(tree);
  auto level_order = treelist<T, order::level>(tree);
  std::cout << "pre:   " << join(pre_order) << std::endl;
  std::cout << "in:    " << join(in_order) << std::endl;
  std::cout << "post:  " << join(post_order) << std::endl;
  std::cout << "level: " << join(level_order) << std::endl;
}

node<char> *challenge1(const std::vector<char> &preOrder, const std::vector<char> &inOrder);

node<char> *challenge2(const std::vector<char> &inOrder, const std::vector<char> &levelOrder);

int main() {
  auto root = new node<char>('A');
  root->left = new node<char>('B');
  root->right = new node<char>('C');
  root->left->left = new node<char>('D');
  root->left->right = new node<char>('E');
  root->right->left = new node<char>('F');
  root->right->right = new node<char>('G');

  print_tree_orders<char>(root);

  auto pre_order = treelist<char, order::pre>(root);
  auto in_order = treelist<char, order::in>(root);
  auto level_order = treelist<char, order::level>(root);

  std::cout << "== challenge1 output:" << std::endl;
  auto recon1 = challenge1(pre_order, in_order);
  print_tree_orders<char>(recon1);
  std::cout << "success: " << (compare_tree<char>(root, recon1) ? "true" : "false") << std::endl;

  std::cout << "== challenge2 output:" << std::endl;
  auto recon2 = challenge2(in_order, level_order);
  print_tree_orders<char>(recon2);
  std::cout << "success: " << (compare_tree<char>(root, recon2) ? "true" : "false") << std::endl;
}

// task: reconstruct tree from pre and in order output
//  assume a tree with distinct elements
node<char> *challenge1(const std::vector<char> &preOrder, const std::vector<char> &inOrder) {
  return nullptr;
}

// task: reconstruct tree from in and level order output
//  assume a tree with distinct elements
node<char> *challenge2(const std::vector<char> &inOrder, const std::vector<char> &levelOrder) {
  return nullptr;
}
