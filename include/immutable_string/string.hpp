#include <string>

#include <boost/smart_ptr/allocate_shared_array.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace immutable_string {

template <class CharT, class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
class basic_string {
 public:
  using traits_type = Traits;
  using value_type = typename traits_type::char_type;
  using allocator_type = Allocator;
  using size_type = typename allocator_type::size_type;
  using difference_type = typename allocator_type::difference_type;
  using reference = typename allocator_type::reference;
  using const_reference = typename allocator_type::const_reference;
  using pointer = typename allocator_type::pointer;
  using const_pointer = typename allocator_type::const_pointer;
  using iterator = const char*;
  using const_iterator = const char*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  static const size_type npos = -1;

  basic_string();
  explicit basic_string(const Allocator& alloc);
  basic_string(size_type count, CharT ch, const Allocator& alloc = Allocator());
  basic_string(const CharT* s, const Allocator& alloc = Allocator());
  basic_string(const CharT* s, size_type count,
               const Allocator& alloc = Allocator());

  const_reference operator[](size_type pos) const noexcept;
  const_reference at(size_type pos) const;
  const_reference front() const noexcept { return (*this)[0]; }
  const_reference back() const noexcept { return (*this)[size() - 1]; }
  const CharT* data() const noexcept { return m_data.get(); }
  const CharT* c_str() const noexcept { return data(); }

  bool empty() const noexcept { return m_size == 0; }
  size_type size() const noexcept { return m_size; }
  size_type length() const noexcept { return size(); }

  iterator begin() const noexcept;
  iterator end() const noexcept;
  reverse_iterator rbegin() const noexcept;
  reverse_iterator rend() const noexcept;

  iterator cbegin() const noexcept { return begin(); }
  iterator cend() const noexcept { return end(); }
  reverse_iterator crbegin() const noexcept { return rbegin(); }
  reverse_iterator crend() const noexcept { return rend(); }

 private:
  void _throw_out_of_range() const { throw std::out_of_range("basic_string"); }

 private:
  boost::shared_ptr<CharT[]> m_data;
  size_type m_size;
};

using string = basic_string<char>;
using wstring = basic_string<wchar_t>;

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>::basic_string() : basic_string("") {}

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>::basic_string(size_type count, CharT ch,
                                                     const Allocator& alloc)
    : m_data(boost::allocate_shared<CharT[]>(alloc, count + 1)), m_size(count) {
  Traits::assign(m_data.get(), count, ch);
}

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>::basic_string(const Allocator& alloc)
    : basic_string("", alloc) {}

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>::basic_string(const CharT* s,
                                                     const Allocator& alloc)
    : basic_string(s, Traits::length(s), alloc) {}

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>::basic_string(const CharT* s,
                                                     size_type count,
                                                     const Allocator& alloc)
    : m_data(boost::allocate_shared<CharT[]>(alloc, count + 1)), m_size(count) {
  // allocate_shared returns value initialized array
  // so, we don't need to fill last element with zero
  Traits::copy(m_data.get(), s, count);
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::const_reference
    basic_string<CharT, Traits, Allocator>::operator[](size_type pos) const
    noexcept {
  return data()[pos];
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::const_reference
basic_string<CharT, Traits, Allocator>::at(size_type pos) const {
  if (pos >= size()) _throw_out_of_range();
  return (*this)[pos];
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::iterator
basic_string<CharT, Traits, Allocator>::begin() const noexcept {
  return m_data.get();
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::iterator
basic_string<CharT, Traits, Allocator>::end() const noexcept {
  return m_data.get() + size();
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::reverse_iterator
basic_string<CharT, Traits, Allocator>::rbegin() const noexcept {
  return reverse_iterator{end()};
}

template <class CharT, class Traits, class Allocator>
typename basic_string<CharT, Traits, Allocator>::reverse_iterator
basic_string<CharT, Traits, Allocator>::rend() const noexcept {
  return reverse_iterator{begin()};
}

}  // namespace immutable_string
