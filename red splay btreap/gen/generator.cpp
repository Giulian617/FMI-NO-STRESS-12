#include <bits/stdc++.h>

using namespace std;

/**
 * RedBlackTree class
 * Author: Bogdan Ioan Popa
 */
class RedBlackTree {
private:
    struct RedBlackTreeNode {
        RedBlackTreeNode *left, *right, *parent;
        int key;
        bool color; /// true -> red, false -> black
        RedBlackTreeNode (RedBlackTreeNode *l, RedBlackTreeNode *r, RedBlackTreeNode *p, int k = INT_MAX, bool col = false) : key(k), color(col) {
            left = l;
            right = r;
            parent = p;
        }
    };

    RedBlackTreeNode *root, *NIL;
    size_t countNodes;

    void rotateLeft(RedBlackTreeNode * &node) {
        if(node -> right == NIL) {
            cout << "CAN'T PERFORM LEFT ROTATION\n";
            return;
        }

        RedBlackTreeNode *parent = node -> parent;
        bool nilParent = parent == NIL;
        int key = node -> key;
        RedBlackTreeNode **A;

        if(key < parent -> key && !nilParent) {
            A = &parent -> left;
        }

        if(key > parent -> key && !nilParent) {
            A = &parent -> right;
        }

        RedBlackTreeNode *rightNode = node -> right;
        RedBlackTreeNode *rightNodeleft = node -> right -> left;

        node -> right = rightNodeleft;

        if(rightNodeleft != NIL) {
            rightNodeleft -> parent = node;
        }

        node -> parent = rightNode;
        node -> right = rightNodeleft;
        rightNode -> left = node;
        rightNode -> parent = parent;
        node = rightNode;

        if(!nilParent)
            *A = node;
    }

    void rotateRight(RedBlackTreeNode * &node) {
        if(node -> left == NIL) {
            cout << "CAN'T PERFORM RIGHT ROTATION\n";
            return;
        }

        RedBlackTreeNode *parent = node -> parent;
        bool nilParent = parent == NIL;
        int key = node -> key;
        RedBlackTreeNode **A;

        if(key < parent -> key && !nilParent) {
            A = &parent -> left;
        }

        if(key > parent -> key && !nilParent) {
            A = &parent -> right;
        }

        RedBlackTreeNode *leftNode = node -> left;
        RedBlackTreeNode *leftNodeRight = node -> left -> right;

        if(leftNodeRight != NIL) {
            leftNodeRight -> parent = node;
        }

        node -> parent = leftNode;
        node -> left = leftNodeRight;
        leftNode -> right = node;
        leftNode -> parent = parent;
        node = leftNode;

        if(!nilParent)
            *A = node;
    }

    void fixUp(RedBlackTreeNode *node) {
        if(node == root) {
            node -> color = false;
            return;
        }

        if(node -> color == true && node -> parent -> color == true) {
            RedBlackTreeNode *parent = node -> parent;
            RedBlackTreeNode *grandParent = parent -> parent;

            bool grandParentIsRoot = grandParent == root;

            if(grandParent == NIL) {
                cout << "DURING FIXUP, GRANDPARENT IS NIL\n";
                return;
            }

            if(grandParent -> left -> color && grandParent -> right -> color) {
                grandParent -> color = true;
                grandParent -> left -> color = false;
                grandParent -> right -> color = false;
                fixUp(grandParent);
                return;
            }

            RedBlackTreeNode *uncle;

            if(grandParent -> left -> color == false) {
                uncle = grandParent -> left;
            } else {
                uncle = grandParent -> right;
            }

            if(parent -> key < grandParent -> key) {
                if(node -> key > parent -> key) {
                    rotateLeft(parent);
                    node = parent -> left;
                }
                rotateRight(grandParent);
                grandParent -> color = false;
                grandParent -> right -> color = true;
                if(grandParentIsRoot) {
                    root = grandParent;
                }
                return;
            }

            if(parent -> key > grandParent -> key) {
                if(node -> key < parent -> key) {
                    rotateRight(parent);
                    node = parent -> right;
                }
                rotateLeft(grandParent);
                grandParent -> color = false;
                grandParent -> left -> color = true;
                if(grandParentIsRoot) {
                    root = grandParent;
                }
                return;
            }
        }
    }

    RedBlackTreeNode *LOWER_BOUND(int key) {
        RedBlackTreeNode *node = root;
        RedBlackTreeNode *ret = NIL;
        while(node != NIL) {
            if(key == node -> key)
                return node;
            if(key < node -> key) {
                if(ret -> key > node -> key) {
                    ret = node;
                }
                node = node -> left;
            }
            else
                node = node -> right;
        }

        return ret;
    }

    void doubleBlack(RedBlackTreeNode *node) {
        if(node == root) {
            return;
        }

        RedBlackTreeNode *parent = node -> parent;
        RedBlackTreeNode *sibling = (parent -> left == node ? parent -> right : parent -> left);

        if(sibling == NIL) {
            cout << "SIBLING IS NIL\n";
            return;
        }

        bool parentIsRoot = parent == root;

        if(sibling -> color) {
            if(parent -> right == sibling) {
                rotateLeft(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> color = false;
                parent -> left -> color = true;
                doubleBlack(node);
                return;
            }

            if(parent -> left == sibling) {
                rotateRight(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> color = false;
                parent -> right -> color = true;
                doubleBlack(node);
                return;
            }
            cout << "PARENT DOESNT HAVE SIBLING AS SON\n";
            return;
        }

        bool siblingHasReds = false;
        bool hasGrandParent = false;

        if(parent -> right == sibling) {
            if(sibling -> right -> color) {
                siblingHasReds = true;
                rotateLeft(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> right -> color = false;

            } else if(sibling -> left -> color) {
                siblingHasReds = true;
                rotateRight(sibling);
                sibling -> color = false;
                sibling -> right -> color = true;
                rotateLeft(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> right -> color = false;
            }

        }

        if(parent -> left == sibling) {
            if(sibling -> left -> color) {
                siblingHasReds = true;
                rotateRight(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> left -> color = false;

            } else if(sibling -> right -> color) {
                siblingHasReds = true;
                rotateLeft(sibling);
                sibling -> color = false;
                sibling -> left -> color = true;
                rotateRight(parent);
                if(parentIsRoot) {
                    root = parent;
                }
                parent -> left -> color = false;
            }

        }

        if(!siblingHasReds) {
            sibling -> color = true;
            if(parent -> color == true) {
                parent -> color = false;
            } else {
                doubleBlack(parent);
            }
            return;
        }
    }

    void inorder(RedBlackTreeNode *node, ofstream &fout, int X = INT_MIN, int Y = INT_MAX) {
        if(node == NIL) {
            return;
        }
        inorder(node -> left, fout, X, Y);
        if(node -> key >= X && node -> key <= Y) {
            fout << node -> key << " ";
        }
        inorder(node -> right, fout, X, Y);
    }

    void DFS(RedBlackTreeNode *node, vector <pair <int, int>>& edges) {
        if(node == NIL) {
            return;
        }
        if (node -> left != NIL) {
            edges.push_back({node->key, node->left->key});
            DFS(node -> left, edges);
        }
        // else {
        //     edges.push_back({node->key, countNodes++});
        // }
        if (node -> right != NIL) {
            edges.push_back({node->key, node->right->key});
            DFS(node -> right, edges);
        }
        // else {
        //     edges.push_back({node->key, countNodes++});
        // }
    }
public:
    RedBlackTree() {
        NIL = new RedBlackTreeNode(NULL, NULL, NULL);
        root = NIL;
        countNodes = 0;
    }

    bool empty() {
        return countNodes == 0;
    }

    size_t size() {
        return countNodes;
    }

    void insert(int key) {
        if(root == NIL) {
            root = new RedBlackTreeNode(NIL, NIL, NIL, key);
            countNodes++;
        } else {
            RedBlackTreeNode *node = root;
            while(true) {
                if(node -> key == key) {
                    return;
                }

                if(node -> key > key) {
                    if(node -> left == NIL) {
                        break;
                    }
                    node = node -> left;
                }

                if(node -> key < key) {
                    if(node -> right == NIL) {
                        break;
                    }
                    node = node -> right;
                }
            }

            if(node -> key > key) {
                node -> left = new RedBlackTreeNode(NIL, NIL, node, key, true);
                fixUp(node -> left);
            }

            if(node -> key < key) {
                node -> right = new RedBlackTreeNode(NIL, NIL, node, key, true);
                fixUp(node -> right);
            }

            countNodes++;
        }
    }

    int lower_bound(int key) {
        return LOWER_BOUND(key) -> key;
    }

    int upper_bound(int key) {
        return lower_bound(key + 1);
    }

    void erase(int key) {
        RedBlackTreeNode *node = root;

        while(node != NIL) {
            if(node -> key == key) {
                if(node -> left != NIL && node -> right != NIL) {
                    RedBlackTreeNode *succ = LOWER_BOUND(key + 1);
                    node -> key = succ -> key;
                    node = succ;
                }

                RedBlackTreeNode *son = NIL;
                RedBlackTreeNode *parent = node -> parent;

                if(node -> left != NIL) {
                    son = node -> left;
                }

                if(node -> right != NIL) {
                    son = node -> right;
                }

                if(node -> left != NIL && node -> right != NIL) {
                    cout << "NODE TO BE DELETED HAS TWO NON-NIL SONS\n";
                    return;
                }

                if(son == NIL) {
                    if(parent == NIL) {
                        if(node != root) {
                            cout << "??????????\n";
                        }
                        delete root;
                        root = NIL;
                        countNodes = 0;
                        return;
                    }

                    if(parent -> left == node) {
                        node -> parent -> left = NIL;
                    }

                    if(parent -> right == node) {
                        node -> parent -> right = NIL;
                    }

                    bool dd = false;

                    if(node -> color == false) {
                        NIL -> parent = parent;
                        dd = true;
                    }

                    delete node;
                    countNodes--;
                    if(dd) {
                        doubleBlack(NIL);
                    }
                    return;
                }

                bool dd = false;
                if(node -> color == false && son -> color == false) {
                    dd = true;
                    cout << "FALSE CONJECTURE\n";
                }

                node -> key = son -> key;
                node -> left = son -> left;
                node -> right = son -> right;

                if(node -> left != NIL) {
                    node -> left -> parent = node;
                }

                if(node -> right != NIL) {
                    node -> right -> parent = node;
                }

                delete son;
                countNodes--;

                if(dd) {
                    doubleBlack(node);
                }
                return;
            }

            if(node -> key < key) {
                node = node -> right;
            } else {
                node = node -> left;
            }
        }
    }

    bool find(int key) {
        return lower_bound(key) == key;
    }

    int highestLower(int key) {
        int ret = INT_MIN;
        RedBlackTreeNode *node = root;
        while(node != NIL) {
            if(node -> key == key) {
                return key;
            }
            if(node -> key < key) {
                ret = max(ret, node -> key);
                node = node -> right;
            } else {
                node = node -> left;
            }
        }
        return ret;
    }

    void print(int X, int Y, ofstream &fout) {
        inorder(root, fout, X, Y);
    }
    vector <pair <int, int>> getEdges() {
        vector <pair <int, int>> edges;
        DFS(root, edges);
        return edges;
    }

    int getRootKey() {
        return root->key;
    }
};

using Edge = pair<int, int>;
using Graph = vector<vector<int>>;

void populate_DS(RedBlackTree& DS, const int N) {
  vector<int> values(N);
  iota(values.begin(), values.end(), 0);
  srand(time(nullptr));
  random_shuffle(values.begin(), values.end());
  for (const int x : values) {
    DS.insert(x);
  }
}

void replace_root_with_0(vector<Edge>& edges, const int root) {
  function<void(int&, int)> replace_values = [&](int& a, int root) -> void {
    if (a == 0) {
      a = root;
    } else if (a == root) {
      a = 0;
    }
  };

  for (auto& [a, b] : edges) {
    replace_values(a, root);
    replace_values(b, root);
  }
}

Graph build_tree(const vector<Edge>& edges) {
  int N = edges.size() + 1;
  Graph G(N);
  for (const auto& [a, b] : edges) {
    G[a].push_back(b);
    G[b].push_back(a);
  }

  Graph T(N);
  function<void(int, int)> dfs = [&](int u, int parrent) -> void {
    for (const int v : G[u]) {
      if (v != parrent) {
        dfs(v, u);
        T[u].push_back(v);
      }
    }
  };
  dfs(0, -1);
  return T;
}

vector<Edge> repair_tree(const vector<Edge>& edges) {
  int N = edges.size() + 1;
  auto G = build_tree(edges);
  auto answer = edges;
  function<void(int)> dfs = [&](int u) -> void {
    for (const int v : G[u]) {
      dfs(v);
    }
    if (G[u].size() == 1) {
      answer.emplace_back(u, N++);
    }
  };
  dfs(0);
  return answer;
}

int main(int argc, char** argv) {
  int N = atoi(argv[1]);

  RedBlackTree DS;
  populate_DS(DS, N);

  auto edges = DS.getEdges();
  replace_root_with_0(edges, DS.getRootKey());
  edges = repair_tree(edges);

  cout << edges.size() + 1 << "\n";
  for (const auto& [a, b] : edges) {
    cout << a + 1 << " " << b + 1 << "\n";
  }

  return 0;
}