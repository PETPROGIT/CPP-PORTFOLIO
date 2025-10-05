# FlatMap

The `FlatMap<Key, Value>` template class is an associative container implemented using a sorted vector of key-value pairs. It provides logarithmic time complexity for search operations and linear time for insertion and deletion through binary search.

## Features

- **Sorted Storage**: All elements are stored in sorted order by key
- **Fast Lookup**: Binary search provides O(log n) access time
- **Exception Handling**: `At()` method throws `std::out_of_range` when key is not found

## Interface

### Constructors:

- `FlatMap()` - default constructor
- `FlatMap(std::initializer_list<Pair>)` - initialization with list of pairs
- Copy and move constructors

### Access Operations:

- `Value& operator[](const Key& key)` - access or create element (if key is missing, inserts it in the correct position with default value)
- `Value& At(const Key& key)` - access with bounds checking (throws exception if key is missing)
- `const Value& At(const Key& key) const` - const access with bounds checking (throws exception if key is missing)

### Modification:

- `bool Insert(const Pair&)` - insert key-value pair
- `bool Insert(const Key&, const Value&)` - insert using separate key and value
- `bool Erase(const Key&)` - remove element by key
- `void Clear()` - clear the container
- `void Swap(FlatMap&) noexcept` - exchange contents between two containers

### Container Information:

- `size_t Size() const noexcept` - current number of elements
- `bool Empty() const noexcept` - check if container is empty
- `bool Contains(const Key&) const` - check if key exists

### Comparison:

- `operator==`, `operator!=` - element-wise comparison

## Type Requirements

- Key type `Key` must support comparison operators `<`, `>`, `==`
- Both types must be copyable and/or movable

## Usage Example

```cpp
FlatMap<std::string, int> map;
map.Insert("one", 1);
map.Insert("two", 2);

std::cout << map.At("one") << std::endl; // 1
std::cout << map["three"] << std::endl;  // 0 (created with default value)

map.Erase("two");
std::cout << map.Size() << std::endl;    // 2
```

## Performance
- Search: O(log n)
- Insertion: O(n)
- Deletion: O(n)
