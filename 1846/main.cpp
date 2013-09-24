
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( Storages& s ) { return false; };
    virtual void output( const Storages& s ) const {};
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer_reference_count.cpp>
namespace misc {
  class SmartPointerReferenceCount {
  public:
    void add() { count ++; }
    int release() { return -- count; }
  private:
    int count;
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer.cpp>
namespace misc {
  template <typename Type> class SmartPointer {
  public:
    SmartPointer(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointer() {
      if ( reference->release() == 0 ) {
        delete[] pointer;
        delete[] reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointer<Type>& operator = ( const SmartPointer<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete[] pointer;
          delete[] reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }
  private:
    Type* pointer;
    misc::SmartPointerReferenceCount* reference;
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef misc::SmartPointer<ValueType> Pointer;
    VectorClass() { data = Pointer(new ValueType[SIZE]); }
    ValueType& operator [] ( const int& index ) { return *(data + index); }
    const ValueType& operator [] ( const int& index ) const { return *(data + index); }
  private:
    Pointer data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_Z> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

namespace math {
  template <class T> T gcd( T a, T b ) {
    if ( a == 0 )
      return b;
    if ( b == 0 )
      return a;
    T i, j;
    for ( i = 0; ! ( a & 1 ); ++ i ) a >>= 1;
    for ( j = 0; ! ( b & 1 ); ++ j ) b >>= 1;
    while ( b != a ) {
      b -= a;
      if ( b < 0 ) a += b, b = -b;
      while ( ! ( b & 1 ) ) b >>= 1;
    }
    return a << std::min( i, j );
  }
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  struct Query {
    String type;
    Int value;
    
    friend std::ostream& operator <<( std::ostream& os, const Query& q ) {
      os << "{";
      os << q.type << ", ";
      os << q.value << ", ";
      os << "}";
      return os;
    }
    
    friend std::istream& operator >>( std::istream& is, Query& q ) {
      return is >> q.type >> q.value;
    }
  };
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int TREE_SIZE = 4 * SIZE + 11;
  
}

namespace solution {
  struct Node {
    Int value;
    Int gcd_value;
    
    void merge( const Node& a, const Node& b ) {
      this->gcd_value = math::gcd(this->value, math::gcd(a.gcd_value, b.gcd_value));
    }
    
    friend std::ostream& operator <<( std::ostream& os, const Node& node ) {
      os << "{";
      os << node.value << ", ";
      os << node.gcd_value << ", ";
      os << "}";
      return os;
    }
  };
  
  Node NODE_IDENTITY = {0, 0};
  
  struct Tree {
    void init( const int& N ) {
      this->N = 1;
      while ( this->N < N )
        this->N *= 2;
    }
    
    Node range_query( const int& root, const int& left_most_leaf, const int& right_most_leaf, const int& u, const int& v ) {
      if ( u <= left_most_leaf && right_most_leaf <= v )
        return list[root];
      int mid = ( left_most_leaf + right_most_leaf ) / 2;
      int left_child = root * 2;
      int right_child = left_child + 1;
      Node l = NODE_IDENTITY;
      Node r = NODE_IDENTITY;
      if ( u < mid )
        l = range_query(left_child, left_most_leaf, mid, u, v);
      if ( mid < v )
        r = range_query(right_child, mid, right_most_leaf, u, v);
      Node res;
      res.merge(l, r);
      return res;
    }

    Node query_all() {
      return range_query(1, N, 2 * N, N, 2 * N);
    }
    
    void update_single_node( const int& node_id, const Node& new_node ) {
      list[node_id] = new_node;
    }
    
    void range_update( const int& root, const int& left_most_leaf, const int& right_most_leaf, const int& u, const int& v, const Node& new_node ) {
      if ( u <= left_most_leaf && right_most_leaf <= v )
        return update_single_node(root, new_node);
      int mid = ( left_most_leaf + right_most_leaf ) / 2;
      int left_child = root * 2;
      int right_child = left_child + 1;
      if ( u < mid )
        range_update(left_child, left_most_leaf, mid, u, v, new_node);
      if ( mid < v )
        range_update(right_child, mid, right_most_leaf, u, v, new_node);
      list[root].merge(list[left_child], list[right_child]);
    }
    
    void update( const int& pos, const Node& new_node ) {
      return range_update(1, N, 2 * N, N + pos, N + pos + 1, new_node);
    }
    
    Node list[TREE_SIZE];
    int N;
  };
  
}

namespace solution {
  typedef storage::Vector<Query, SIZE>::Type Queries;
  typedef storage::Vector<Int, SIZE>::Type QueryResults;

  typedef std::vector <int> Positions;
  typedef std::map <Int, Positions> ValuePositions;
  
  // TODO: 分ける（InputStorage, DataStorage, OutputStorage）
  class Storages {
  public:
    Int Q;
    Queries queries;
    
    int left_most;
    int set_num;
    Tree tree;
    ValuePositions pos;
    
    QueryResults results;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.left_most = 0;
      s.set_num = 0;
      s.pos.clear();
      s.tree = init_tree();
      s.results = proc_queries(s.Q, s.queries, s.tree, s.left_most, s.pos, s.set_num);
    }
    
  protected:
    static Tree init_tree() {
      Tree tree;
      tree.init(SIZE);
      return tree;
    }
    
    static QueryResults proc_queries( const int& queries_num, const Queries& queries, Tree& tree, int& left_most, ValuePositions& pos, int& set_num ) {
      QueryResults res;
      for ( int i = 0; i < queries_num; ++ i ) {
        res[i] = proc_query(queries[i], tree, left_most, pos, set_num);
      }
      return res;
    }
    
    static Int proc_query( const Query& query, Tree& tree, int& left_most, ValuePositions& pos, int& set_num ) {
      if ( query.type == "+" ) {
        Node node = {query.value, query.value};
        tree.update(left_most, node);
        pos[query.value].push_back(left_most);
        left_most ++;
        set_num ++;
      } else {
        Positions& list = pos[query.value];
        int last_pos = list.back();
        list.pop_back();
        tree.update(last_pos, NODE_IDENTITY);
        set_num --;
      }
      return set_num == 0 ? 1 : tree.query_all().gcd_value;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }
    
    bool input( Storages& s ) {
      if ( ! ( std::cin >> s.Q ) )
        return false;
      for ( int i = 0; i < s.Q; ++ i )
        std::cin >> s.queries[i];
      return true;
    }
    
    void output( const Storages& s ) const {
      for ( int i = 0; i < s.Q; ++ i )
        std::cout << s.results[i] << endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif



