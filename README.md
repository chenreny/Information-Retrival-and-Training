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
        } else {
            if (xhr.status != 200 && xhr.status != 0) {
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
    // value stored in a std::pair
    using Pair_type = std::pair<Key_type, Value_type>;
    
    // A custom comparator
    class PairComp {
    public:
        bool operator() (const Pair_type &lhs, const Pair_type &rhs){}
    };
    
public:
    // Type alias for iterator type
    using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;
        
    //default constructor
    Map() : tree(){}
    
    //copy constructor
    Map(const Map &other) : tree(other.tree){}
    
    //assignment operator
    Map & operator=(const Map &rhs){}

    // Searches this Map for an element with a key equivalent
    Iterator find(const Key_type& k) const{}
    
    // Returns a reference to the mapped value for the given
    // key. If k matches the key of an element in the
    // container, the function returns a reference to its
    // mapped value. If k does not match the key of any
    // element in the container, the function inserts a new
    // element with that key and a value-initialized mapped
    // value and returns a reference to the mapped value
    Value_type& operator[](const Key_type& k){}
    
    // Inserts the given element into this Map if the given key
    // is not already contained in the Map. If the key is
    // already in the Map, returns an iterator to the
    // corresponding existing element, along with the value
    // false. Otherwise, inserts the given element and returns
    // an iterator to the newly inserted element, along with
    // the value true.
    std::pair<Iterator, bool> insert(const Pair_type &val){}

private:
    BinarySearchTree<Pair_type, PairComp> tree;
};
```
### Reference
Simplified HTTP request client.
<br> https://github.com/request/request
