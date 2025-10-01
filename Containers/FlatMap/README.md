FlatMap - C++ Sorted Associative Container
Overview
FlatMap is a C++ template class that implements an associative container using a sorted std::vector for storing key-value pairs. The container maintains automatic sorting by keys and provides efficient lookup, insertion, and deletion operations through binary search.

Key Features
Sorted Storage: All elements are stored in sorted order by key

Fast Lookup: Binary search with O(log n) complexity

STL-Compatible: Follows Standard Library idioms and conventions

Type-Safe: Strong typing for keys and values

Exception-Safe: Proper exception handling for access errors

Class Interface
Constructors and Assignment
cpp
// Default constructor
FlatMap<Key, Value>()

// Initializer list constructor
FlatMap<Key, Value>(std::initializer_list<Pair>)

// Copy and move constructors
FlatMap(const FlatMap&)
FlatMap(FlatMap&&) noexcept

// Copy and move assignment operators
FlatMap& operator=(const FlatMap&)
FlatMap& operator=(FlatMap&&) noexcept
Element Access
cpp
// Unsafe access - creates element if key doesn't exist
Value& operator[](const Key& key)

// Safe access - throws exception if key doesn't exist
Value& At(const Key& key)
const Value& At(const Key& key) const
Comparison Operators
cpp
bool operator==(const FlatMap&) const  // Element-wise equality
bool operator!=(const FlatMap&) const  // Element-wise inequality
Modifiers
cpp
// Insertion operations
bool Insert(const Pair& pairKeyValue)
bool Insert(const Key& key, const Value& value)

// Deletion operations
bool Erase(const Key& key)
void Clear()

// Utility operations
void Swap(FlatMap& other) noexcept
Capacity and Lookup
cpp
// Capacity
size_t Size() const noexcept
bool Empty() const noexcept

// Lookup
bool Contains(const Key& key) const
Usage Examples
Basic Operations
cpp
FlatMap<std::string, int> map;

// Insert elements
map.Insert("one", 1);
map.Insert("two", 2);
map.Insert("three", 3);

// Access elements safely
std::cout << map.At("one") << std::endl; // Output: 1

// Check key existence
if (map.Contains("two")) {
    std::cout << "Key 'two' exists" << std::endl;
}

// Remove elements
map.Erase("three");
Initialization
cpp
// Initializer list construction
FlatMap<int, std::string> map = {
    {1, "one"},
    {2, "two"}, 
    {3, "three"}
};
Unsafe Access with Operator[]
cpp
FlatMap<std::string, int> scores;

// Creates elements with default values if keys don't exist
scores["Alice"] = 95;
scores["Bob"] = 87;

// Automatically creates element with Value{} (0 for int)
int charlie_score = scores["Charlie"];
Error Handling
cpp
try {
    int value = map.At("nonexistent"); // Throws std::out_of_range
} catch (const std::out_of_range& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
Type Requirements
Key Type: Must support comparison operators (<, >, ==)

Value Type: Must be default-constructible

Performance Characteristics
Operation	Complexity	Notes
Lookup	O(log n)	Binary search
Insertion	O(n)	Due to vector element shifting
Deletion	O(n)	Due to vector element shifting
Memory	Compact	Minimal overhead
Implementation Details
Elements are always maintained in sorted order by key

Binary search determines insertion positions

operator[] creates default-constructed elements for missing keys

At() throws exceptions for missing keys

Automatic sorting on every insertion

Exception Safety
std::out_of_range: Thrown by At() when accessing non-existent keys

Strong exception guarantee for most operations

No-throw guarantee for move operations

Best Practices
Use At() when key existence should be validated

Use operator[] when default-constructed values are acceptable

Prefer batch operations when possible due to O(n) insertion cost

Consider key types with efficient comparison operations

Compatibility
C++11 or later required

Header-only implementation

No external dependencies beyond Standard Library
