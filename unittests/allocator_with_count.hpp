#include <cstring>
#include <limits>
#include <memory>
#include <type_traits>

template <class T>
class allocator_with_count {
 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;

  allocator_with_count(int& count) noexcept : m_allocated_count(count) {}

  allocator_with_count(const allocator_with_count&) noexcept = default;
  template <class U>
  struct rebind {
    using other = allocator_with_count<U>;
  };
  template <class>
  friend class allocator_with_count;
  template <class U>
  allocator_with_count(const allocator_with_count<U>& other) noexcept
      : m_allocated_count(other.m_allocated_count) {}

  pointer address(reference x) const { return &x; }
  const_pointer address(const_reference x) const { return &x; }

  T* allocate(std::size_t n) {
    if (n == 0) return nullptr;
    auto res = static_cast<pointer>(::operator new(n * sizeof(T)));
    ++m_allocated_count;
    return res;
  }

  void deallocate(T* p, std::size_t) { ::operator delete(p); }

  std::size_t max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }

  void construct(pointer p, const T& val) {
    new (static_cast<void*>(p)) T(val);
  }

  void destroy(pointer p) { p->~T(); }

  int& m_allocated_count;
};
