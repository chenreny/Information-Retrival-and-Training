# Information-Retrival-and-Training
The goal is to read from large CSV/JSON file and train classifier based on that
<br>To be more specific:
<br>Importing data
<br>Cleaning data
<br>Splitting it into train sets/Pre-processing
<br>Calculating 
<br>Make prediction

### User defined type
```
using rowType = std::map<std::string, std::string>;
using countType = std::map<std::string, int>;
using Pair_type = std::pair<std::string, std::string>;

});
```

### Requesting data
Example:
```
function get(options) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            // JSON response assumed. Other APIs may have different responses.
            options.callback(JSON.parse(xhr.responseText));
            // green
            google_drive_flag = true;
        } else {
            if (xhr.status != 200 && xhr.status != 0) {
                google_drive_flag = false;
                console.log('get', xhr.readyState, xhr.status, xhr.responseText);
            }
        }
    };
    xhr.open("GET", options.url, true);
    xhr.send();
}
```
### Data strcture underneath(Map)
```

class Map {
    
private:
    // Type alias for an element, the combination of a key and mapped
    // value stored in a std::pair.
    // See http://www.cplusplus.com/reference/utility/pair/
    using Pair_type = std::pair<Key_type, Value_type>;
    
    // A custom comparator
    class PairComp {
    public:
        bool operator() (const Pair_type &lhs, const Pair_type &rhs){
            Key_compare keyCompare;
            return keyCompare(lhs.first, rhs.first);
        }
    };
    
public:
    

    
    // Type alias for iterator type. It is sufficient to use the Iterator
    // from BinarySearchTree<Pair_type> since it will yield elements of Pair_type
    // in the appropriate order for the Map.
    using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;
    
    // You should add in a default constructor, destructor, copy
    // constructor, and overloaded assignment operator, if appropriate.
    // If these operations will work correctly without defining them,
    // you should omit them. A user of the class must be able to create,
    // copy, assign, and destroy Maps.
    
    //default constructor
    Map() : tree(){}
    

    //copy constructor
    Map(const Map &other) : tree(other.tree){}
    
    //assignment operator
    Map & operator=(const Map &rhs){
        if(this == &rhs) return *this;
        tree = rhs.tree;
        return *this;
    }
    
    // EFFECTS : Returns whether this Map is empty.
    bool empty() const{
        return tree.empty();
    }
    
    // EFFECTS : Returns the number of elements in this Map.
    // NOTE : size_t is an integral type from the STL
    size_t size() const{
        return tree.size();
    }
    
    // EFFECTS : Searches this Map for an element with a key equivalent
    //           to k and returns an Iterator to the associated value if found,
    //           otherwise returns an end Iterator.
    //
    // HINT: Since Map is implemented using a BinarySearchTree that stores
    //       (key, value) pairs, you'll need to construct a dummy value
    //       using "Value_type()".
    Iterator find(const Key_type& k) const{
        return tree.find({k, Value_type()});
    }
    
    // MODIFIES: this
    // EFFECTS : Returns a reference to the mapped value for the given
    //           key. If k matches the key of an element in the
    //           container, the function returns a reference to its
    //           mapped value. If k does not match the key of any
    //           element in the container, the function inserts a new
    //           element with that key and a value-initialized mapped
    //           value and returns a reference to the mapped value.
    //           Note: value-initialization for numeric types guarantees the
    //           value will be 0 (rather than memory junk).
    //
    // HINT:     In the case the key was not found, and you must insert a
    //           new element, use the expression {k, Value_type()} to create
    //           that element. This ensures the proper value-initialization is done.
    //
    // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
    Value_type& operator[](const Key_type& k){
        Iterator i = find(k);
        if(i != tree.end()) return (*i).second;
        return (*tree.insert({k, Value_type()})).second;
    }
    
    // MODIFIES: this
    // EFFECTS : Inserts the given element into this Map if the given key
    //           is not already contained in the Map. If the key is
    //           already in the Map, returns an iterator to the
    //           corresponding existing element, along with the value
    //           false. Otherwise, inserts the given element and returns
    //           an iterator to the newly inserted element, along with
    //           the value true.
    std::pair<Iterator, bool> insert(const Pair_type &val){
        Iterator i = tree.find(val);
        if(i != tree.end()) return {i, false};
        return {tree.insert(val), true};
    }
    
    // EFFECTS : Returns an iterator to the first key-value pair in this Map.
    Iterator begin() const{
        return tree.begin();
    }
    
    // EFFECTS : Returns an iterator to "past-the-end".
    Iterator end() const{
        return tree.end();
    }
    
private:
    // Add a BinarySearchTree private member HERE.
    BinarySearchTree<Pair_type, PairComp> tree;
};
```
### Reference
Simplified HTTP request client.
<br> https://github.com/request/request
