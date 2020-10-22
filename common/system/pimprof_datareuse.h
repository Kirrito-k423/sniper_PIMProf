//===- [Yizhou]                                      ------------*- C++ -*-===//
//
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//
#ifndef __DATAREUSE_H__
#define __DATAREUSE_H__

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <algorithm>

namespace PIMProf
{
/* ===================================================================== */
/* Typedefs and constants */
/* ===================================================================== */
typedef uint32_t CACHE_STATS;
typedef double COST;
typedef uint32_t BBLID;
typedef std::pair<uint64_t, uint64_t> UUID;

enum CostSite {
    CPU, PIM, MAX_COST_SITE,
    INVALID = 0x3fffffff // a placeholder that does not count as a cost site
};

enum ACCESS_TYPE
{
    ACCESS_TYPE_LOAD,
    ACCESS_TYPE_STORE,
    ACCESS_TYPE_NUM
};

/* ===================================================================== */
/* DataReuseSegment */
/* ===================================================================== */
typedef std::pair<BBLID, ACCESS_TYPE> BBLOP;

class DataReuseSegment {
  friend class DataReuse;
  private:
    BBLID _headID;
    std::set<BBLID> _set;
    int _count;

  public:
    inline DataReuseSegment() {
        _headID = -1;
        _count = 1;
    }

    inline size_t size() const {
        return _set.size();
    }

    inline void insert(BBLID bblid) {
        if (_set.empty())
            _headID = bblid;
        _set.insert(bblid);
    }

    inline void insert(DataReuseSegment &seg) {
        _set.insert(seg._set.begin(), seg._set.end());
    }

    inline std::vector<BBLID> diff(DataReuseSegment &seg) {
        std::vector<BBLID> result;
        std::set_difference(
            _set.begin(), _set.end(),
            seg.begin(), seg.end(),
            std::inserter(result, result.end())
        );
        return result;
    }

    inline void clear() {
        _headID = -1;
        _set.clear();
        _count = 1;
    }

    inline std::set<BBLID>::iterator begin() {
        return _set.begin();
    }

    inline std::set<BBLID>::iterator end() {
        return _set.end();
    }

    inline void setHead(BBLID head) {
        _headID = head;
    }

    inline BBLID getHead() const {
        return _headID;
    }

    inline void setCount(int count) {
        _count = count;
    }

    inline int getCount() const {
        return _count;
    }

    inline bool operator == (DataReuseSegment &rhs) {
        return (_headID == rhs._headID && _set == rhs._set);
    }

    inline std::ostream &print(std::ostream &out) {
        out << "{ ";
        out << _headID << " | ";
        for (auto it = _set.begin(); it != _set.end(); it++) {
            out << *it << ", ";
        }
        out << "}";
        out << std::endl;
        return out;
    }

    
};

/* ===================================================================== */
/* TrieNode */
/* ===================================================================== */
class TrieNode {
  public:
    // the leaf node stores the head of the segment
    bool _isLeaf;
    std::map<BBLID, TrieNode *> _children;
    BBLID _curID;
    TrieNode *_parent;
    int64_t _count;
  public:
    inline TrieNode() {
        _isLeaf = false;
        _parent = NULL;
        _count = 0;
    }
};



/* ===================================================================== */
/* DataReuse */
/* ===================================================================== */
/// We split a reuse chain into multiple segments that starts
/// with a W and ends with a W, for example:
/// A reuse chain: R W R R R R W R W W R R W R
/// can be splitted into: R W | R R R R W | R W | W | R R W | R
/// this is stored as segments that starts with a W and ends with a W:
/// R W; W R R R R W; W R W; W W; W R R W; W R

/// If all BB in a segment are executed in the same place,
/// then there is no reuse cost;
/// If the initial W is on PIM and there are subsequent R/W on CPU,
/// then this segment contributes to a flush of PIM and data fetch from CPU;
/// If the initial W is on CPU and there are subsequent R/W on PIM,
/// then this segment contributes to a flush of CPU and data fetch from PIM.
class DataReuse {
  private:
    TrieNode *_root;
    std::vector<TrieNode *> _leaves;

  public:
    DataReuse();
    ~DataReuse();

  public:
    void UpdateTrie(TrieNode *root, DataReuseSegment &seg);
    void DeleteTrie(TrieNode *root);
    void ExportSegment(DataReuseSegment &seg, TrieNode *leaf);
    void PrintTrie(std::ostream &out, TrieNode *root, int parent, int &count);
    std::ostream &print(std::ostream &out, TrieNode *root);

    inline TrieNode *getRoot() {
        return _root;
    }

    inline std::vector<TrieNode *> &getLeaves() {
        return _leaves;
    }
};
} // namespace PIMProf


#endif // __DATAREUSE_H__