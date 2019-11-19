#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>

namespace fefu
{

    template<typename T>
    class allocator {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<const T>::type;
        using value_type = T;

        allocator() noexcept = default;

        allocator(const allocator&) noexcept = default;

        template <class U>
        allocator(const allocator<U>& other) noexcept;

        ~allocator() = default;

        pointer allocate(size_type n = 1) {
            auto p = ::operator new(n * sizeof(value_type));
            return static_cast<pointer>(p);
        }

        void deallocate(pointer p, size_type n) noexcept {
            ::operator delete(p, n);
        }
    };

    template<typename ValueType>
    class hash_map_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = ValueType&;
        using pointer = ValueType*;

        hash_map_iterator() noexcept = default;
        hash_map_iterator(const hash_map_iterator& other) noexcept : p(other.p) { }
        hash_map_iterator(const pointer p, const std::vector<char>* m_set_ptr, size_t bucket_ind) :
            p(p),
            m_set_ptr(m_set_ptr),
            bucket_ind(bucket_ind) { }

        reference operator*() const
        {
            return *p;
        }
        pointer operator->() const
        {
            return p;
        }

        // prefix ++
        hash_map_iterator& operator++()
        {
            if (bucket_ind == (*m_set_ptr).size())
            {
                throw std::runtime_error("cannot increment end map iterator");
            }
            while (bucket_ind < (*m_set_ptr).size() && (*m_set_ptr)[bucket_ind] == 0)
            {
                p++;
                bucket_ind++;
            }
            if (bucket_ind == (*m_set_ptr).size())
            {
                p++;
            }
        }
        // postfix ++
        hash_map_iterator operator++(int num)  //how do it faster?
        {
            for (int i = 0; i < num; i++)
            {
                (*this)++;
            }
        }

        template<typename K, typename T,
            typename Hash = std::hash<K>,
            typename Pred = std::equal_to<K>,
            typename Alloc = allocator<std::pair<const K, T>>>
            friend class hash_map;

        friend bool operator==(const hash_map_iterator<ValueType>&, const hash_map_iterator<ValueType>&);
        friend bool operator!=(const hash_map_iterator<ValueType>&, const hash_map_iterator<ValueType>&);
    
    private:
        pointer p;
        std::vector<char>* m_set_ptr; //���� ������� ������ ���������� �� ��������. ����� �������� ++ ����� ������� (� ������ ������ ���-�� ��-�� - �������), �� �������� ������� ������� ������ ��-��. +�������� ��� �������� ����� �������?
        size_t bucket_ind;
    };
    template<typename ValueType>
    bool operator==(const hash_map_iterator<ValueType>& lhs, const hash_map_iterator<ValueType>& rhs)
    {
        return *lhs == *rhs;
    }
    template<typename ValueType>
    bool operator!=(const hash_map_iterator<ValueType>& lhs, const hash_map_iterator<ValueType>& rhs)
    {
        return *lhs != *rhs;
    }

    template<typename ValueType>
    class hash_map_const_iterator {
        // Shouldn't give non const references on value
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = const ValueType&;
        using pointer = const ValueType*;

        hash_map_const_iterator() noexcept = default;
        hash_map_const_iterator(const hash_map_const_iterator& other) noexcept : p(other.p) { }
        hash_map_const_iterator(const hash_map_iterator<ValueType>& other) noexcept : p(other.p) { }
        hash_map_const_iterator(const pointer p, const std::vector<char>* m_set_ptr, size_t bucket_ind) :
            p(p),
            m_set_ptr(m_set_ptr),
            bucket_ind(bucket_ind) { }

        reference operator*() const
        {
            return *p;
        }
        pointer operator->() const
        {
            return p;
        }

        // prefix ++
        hash_map_const_iterator& operator++()
        {
            if (bucket_ind == (*m_set_ptr).size())
            {
                throw std::runtime_error("cannot increment end map iterator");
            }
            while (bucket_ind < (*m_set_ptr).size() && (*m_set_ptr)[bucket_ind] == 0)
            {
                p++;
                bucket_ind++;
            }
            if (bucket_ind == (*m_set_ptr).size())
            {
                p++;
            }
        }
        // postfix ++
        hash_map_const_iterator operator++(int num)
        {
            for (int i = 0; i < num; i++)
            {
                (*this)++;
            }
        }

        template<typename K, typename T,
            typename Hash = std::hash<K>,
            typename Pred = std::equal_to<K>,
            typename Alloc = allocator<std::pair<const K, T>>>
            friend class hash_map;

        friend bool operator==(const hash_map_const_iterator<ValueType>&, const hash_map_const_iterator<ValueType>&);
        friend bool operator!=(const hash_map_const_iterator<ValueType>&, const hash_map_const_iterator<ValueType>&);
    
    private:
        pointer p;
        std::vector<char>* m_set_ptr;
        size_t bucket_ind;
    };
    template<typename ValueType>
    bool operator==(const hash_map_const_iterator<ValueType>& lhs, const hash_map_const_iterator<ValueType>& rhs)
    {
        return *lhs == *rhs;
    }
    template<typename ValueType>
    bool operator!=(const hash_map_const_iterator<ValueType>& lhs, const hash_map_const_iterator<ValueType>& rhs)
    {
        return *lhs == *rhs;
    }


    template<typename K, typename T,
        typename Hash = std::hash<K>,
        typename Pred = std::equal_to<K>,
        typename Alloc = allocator<std::pair<const K, T>>>
        class hash_map
    {
    public:
        using key_type = K;
        using mapped_type = T;
        using hasher = Hash;
        using key_equal = Pred;
        using allocator_type = Alloc;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = hash_map_iterator<value_type>;
        using const_iterator = hash_map_const_iterator<value_type>;
        using size_type = std::size_t;

        /// Default constructor.
        hash_map() = default;

        /**
         *  @brief  Default constructor creates no elements.
         *  @param n  Minimal initial number of buckets.
         */
        explicit hash_map(size_type n) :
            m_data(m_alloc.allocate(n)),
            m_set(n, 0),
            m_size(0),
            m_bucket_count(n) { }

        /**
         *  @brief  Builds an %hash_map from a range.
         *  @param  first  An input iterator.
         *  @param  last  An input iterator.
         *  @param  n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements from
         *  [first,last).  This is linear in N (where N is
         *  distance(first,last)).
         */
        template<typename InputIterator>
        hash_map(InputIterator first, InputIterator last, size_type n = 0) :
            m_data(m_alloc.allocate(n)),
            m_set(n, 0),
            m_size(0),
            m_bucket_count(n)
        {
            insert(first, last);
        }

        /// Copy constructor.
        hash_map(const hash_map& other) :
            m_alloc(other.m_alloc),
            m_data(m_alloc.allocate(other.m_bucket_count)),
            m_set(other.m_set),
            m_size(other.m_size),
            m_bucket_count(other.m_bucket_count),
            m_hash(other.m_hash),
            m_key_eq(other.m_key_eq),
            m_max_load_factor(other.m_max_load_factor)
        {
            for (int i = 0; i < m_bucket_count; i++)
            {
                if (m_set[i])
                {
                    new (m_data + i) value_type{ other.m_data[i].first, other.m_data[i].second };
                }
            }
        }

        /// Move constructor.
        hash_map(hash_map&& other) :
            m_alloc(std::move(other.m_alloc)),
            m_data(std::exchange(other.m_data, nullptr)),
            m_set(std::move(other.m_set)),
            m_size(std::move(other.m_size)),
            m_bucket_count(std::move(other.m_bucket_count)),
            m_hash(std::move(other.m_hash)),
            m_key_eq(std::move(other.m_key_eq)),
            m_max_load_factor(std::move(other.m_max_load_factor)) { }

        /**
         *  @brief Creates an %hash_map with no elements.
         *  @param a An allocator object.
         */
        explicit hash_map(const allocator_type& a) :
            m_alloc(a),
            m_data(m_alloc.allocate(4)),
            m_set(4, 0),
            m_size(0),
            m_bucket_count(4) { }

        /*
        *  @brief Copy constructor with allocator argument.
        * @param  uset  Input %hash_map to copy.
        * @param  a  An allocator object.
        */
        hash_map(const hash_map& umap, const allocator_type& a) :
            m_alloc(a),
            m_data(m_alloc.allocate(umap.m_bucket_count)),
            m_set(umap.m_bucket_count, 0),
            m_size(umap.m_size),
            m_bucket_count(umap.m_bucket_count),
            m_key_eq(umap.m_key_eq),
            m_hash(umap.m_hash),
            m_max_load_factor(umap.m_max_load_factor)
        {
            for (int i = 0; i < m_bucket_count; i++)
            {
                if (m_set[i])
                {
                    new (m_data + i) value_type{ umap.m_data[i].first, umap.m_data[i].second };
                }
            }
        }


        /*
        *  @brief  Move constructor with allocator argument.
        *  @param  uset Input %hash_map to move.
        *  @param  a    An allocator object.
        */
        hash_map(hash_map&& umap, const allocator_type& a) :
            m_alloc(std::move(a)),
            m_data(std::exchange(umap.m_data, nullptr)),
            m_set(std::move(umap.m_set)),
            m_size(std::move(umap.m_size)),
            m_bucket_count(std::move(umap.m_bucket_count)),
            m_key_eq(std::move(umap.m_key_eq)),
            m_hash(std::move(umap.m_hash)),
            m_max_load_factor(std::move(umap.m_max_load_factor)) { }

        /**
         *  @brief  Builds an %hash_map from an initializer_list.
         *  @param  l  An initializer_list.
         *  @param n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements in the
         *  list. This is linear in N (where N is @a l.size()).
         */
        hash_map(std::initializer_list<value_type> l, size_type n = 0) :
            m_data(m_alloc.allocate(n)),
            m_set(n, 0),
            m_size(0),
            m_bucket_count(n)
        {
            insert(l);
        }

        /// Copy assignment operator.
        hash_map& operator=(const hash_map& other)
        {
            hash_map tmp(other);
            std::swap(*this, tmp);
            return *this;
        }

        /// Move assignment operator.
        hash_map& operator=(hash_map&& other)
        {
            m_alloc = std::move(other.m_alloc);
            delete[] m_data;
            m_data = std::move(other.m_data);
            m_set = std::move(other.m_set);
            m_size = std::move(other.m_size);
            m_bucket_count = std::move(other.m_bucket_count);
            m_hash = std::move(other.m_hash);
            m_key_eq = std::move(other.m_key_eq);
            m_max_load_factor = std::move(other.m_max_load_factor);
            return *this;
        }

        /**
         *  @brief  %hash_map list assignment operator.
         *  @param  l  An initializer_list.
         *
         *  This function fills an %hash_map with copies of the elements in
         *  the initializer list @a l.
         *
         *  Note that the assignment completely changes the %hash_map and
         *  that the resulting %hash_map's size is the same as the number
         *  of elements assigned.
         */
        hash_map& operator=(std::initializer_list<value_type> l)
        {
            hash_map tmp(l, l.size());
            std::swap(*this, tmp);
            return *this;
        }

        ///  Returns the allocator object used by the %hash_map.
        allocator_type get_allocator() const noexcept
        {
            return m_alloc;
        }

        // size and capacity:

        ///  Returns true if the %hash_map is empty.
        bool empty() const noexcept;

        ///  Returns the size of the %hash_map.
        size_type size() const noexcept;

        ///  Returns the maximum size of the %hash_map.
        size_type max_size() const noexcept;

        // iterators.

        /**
         *  Returns a read/write iterator that points to the first element in the
         *  %hash_map.
         */
        iterator begin() noexcept;

        //@{
        /**
         *  Returns a read-only (constant) iterator that points to the first
         *  element in the %hash_map.
         */
        const_iterator begin() const noexcept;

        const_iterator cbegin() const noexcept;

        /**
         *  Returns a read/write iterator that points one past the last element in
         *  the %hash_map.
         */
        iterator end() noexcept;

        //@{
        /**
         *  Returns a read-only (constant) iterator that points one past the last
         *  element in the %hash_map.
         */
        const_iterator end() const noexcept;

        const_iterator cend() const noexcept;
        //@}

        // modifiers.

        /**
         *  @brief Attempts to build and insert a std::pair into the
         *  %hash_map.
         *
         *  @param args  Arguments used to generate a new pair instance (see
         *	        std::piecewise_contruct for passing arguments to each
        *	        part of the pair constructor).
        *
        *  @return  A pair, of which the first element is an iterator that points
        *           to the possibly inserted pair, and the second is a bool that
        *           is true if the pair was actually inserted.
        *
        *  This function attempts to build and insert a (key, value) %pair into
        *  the %hash_map.
        *  An %hash_map relies on unique keys and thus a %pair is only
        *  inserted if its first element (the key) is not already present in the
        *  %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        template<typename... _Args>
        std::pair<iterator, bool> emplace(_Args&&... args);

        /**
         *  @brief Attempts to build and insert a std::pair into the
         *  %hash_map.
         *
         *  @param k    Key to use for finding a possibly existing pair in
         *                the hash_map.
         *  @param args  Arguments used to generate the .second for a
         *                new pair instance.
         *
         *  @return  A pair, of which the first element is an iterator that points
         *           to the possibly inserted pair, and the second is a bool that
         *           is true if the pair was actually inserted.
         *
         *  This function attempts to build and insert a (key, value) %pair into
         *  the %hash_map.
         *  An %hash_map relies on unique keys and thus a %pair is only
         *  inserted if its first element (the key) is not already present in the
         *  %hash_map.
         *  If a %pair is not inserted, this function has no effect.
         *
         *  Insertion requires amortized constant time.
         */
        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(const key_type& k, _Args&&... args);

        // move-capable overload
        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(key_type&& k, _Args&&... args);

        //@{
        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param x Pair to be inserted (see std::make_pair for easy
         *	     creation of pairs).
        *
        *  @return  A pair, of which the first element is an iterator that
        *           points to the possibly inserted pair, and the second is
        *           a bool that is true if the pair was actually inserted.
        *
        *  This function attempts to insert a (key, value) %pair into the
        *  %hash_map. An %hash_map relies on unique keys and thus a
        *  %pair is only inserted if its first element (the key) is not already
        *  present in the %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        std::pair<iterator, bool> insert(const value_type& x);

        std::pair<iterator, bool> insert(value_type&& x);

        //@}

        /**
         *  @brief A template function that attempts to insert a range of
         *  elements.
         *  @param  first  Iterator pointing to the start of the range to be
         *                   inserted.
         *  @param  last  Iterator pointing to the end of the range.
         *
         *  Complexity similar to that of the range constructor.
         */
        template<typename _InputIterator>
        void insert(_InputIterator first, _InputIterator last);

        /**
         *  @brief Attempts to insert a list of elements into the %hash_map.
         *  @param  l  A std::initializer_list<value_type> of elements
         *               to be inserted.
         *
         *  Complexity similar to that of the range constructor.
         */
        void insert(std::initializer_list<value_type> l);


        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param k    Key to use for finding a possibly existing pair in
         *                the map.
         *  @param obj  Argument used to generate the .second for a pair
         *                instance.
         *
         *  @return  A pair, of which the first element is an iterator that
         *           points to the possibly inserted pair, and the second is
         *           a bool that is true if the pair was actually inserted.
         *
         *  This function attempts to insert a (key, value) %pair into the
         *  %hash_map. An %hash_map relies on unique keys and thus a
         *  %pair is only inserted if its first element (the key) is not already
         *  present in the %hash_map.
         *  If the %pair was already in the %hash_map, the .second of
         *  the %pair is assigned from obj.
         *
         *  Insertion requires amortized constant time.
         */
        template <typename _Obj>
        std::pair<iterator, bool> insert_or_assign(const key_type& k, _Obj&& obj);

        // move-capable overload
        template <typename _Obj>
        std::pair<iterator, bool> insert_or_assign(key_type&& k, _Obj&& obj);

        //@{
        /**
         *  @brief Erases an element from an %hash_map.
         *  @param  position  An iterator pointing to the element to be erased.
         *  @return An iterator pointing to the element immediately following
         *          @a position prior to the element being erased. If no such
         *          element exists, end() is returned.
         *
         *  This function erases an element, pointed to by the given iterator,
         *  from an %hash_map.
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator position);

        // LWG 2059.
        iterator erase(iterator position);
        //@}

        /**
         *  @brief Erases elements according to the provided key.
         *  @param  x  Key of element to be erased.
         *  @return  The number of elements erased.
         *
         *  This function erases all the elements located by the given key from
         *  an %hash_map. For an %hash_map the result of this function
         *  can only be 0 (not present) or 1 (present).
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
        size_type erase(const key_type& x);

        /**
         *  @brief Erases a [first,last) range of elements from an
         *  %hash_map.
         *  @param  first  Iterator pointing to the start of the range to be
         *                  erased.
         *  @param last  Iterator pointing to the end of the range to
         *                be erased.
         *  @return The iterator @a last.
         *
         *  This function erases a sequence of elements from an %hash_map.
         *  Note that this function only erases the elements, and that if
         *  the element is itself a pointer, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator first, const_iterator last);

        /**
         *  Erases all elements in an %hash_map.
         *  Note that this function only erases the elements, and that if the
         *  elements themselves are pointers, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        void clear() noexcept;

        /**
         *  @brief  Swaps data with another %hash_map.
         *  @param  x  An %hash_map of the same element and allocator
         *  types.
         *
         *  This exchanges the elements between two %hash_map in constant
         *  time.
         *  Note that the global std::swap() function is specialized such that
         *  std::swap(m1,m2) will feed to this function.
         */
        void swap(hash_map& x);

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>& source);

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>&& source);

        // observers.

        ///  Returns the hash functor object with which the %hash_map was
        ///  constructed.
        Hash hash_function() const;

        ///  Returns the key comparison object with which the %hash_map was
        ///  constructed.
        Pred key_eq() const;

        // lookup.

        //@{
        /**
         *  @brief Tries to locate an element in an %hash_map.
         *  @param  x  Key to be located.
         *  @return  Iterator pointing to sought-after element, or end() if not
         *           found.
         *
         *  This function takes a key and tries to locate the element with which
         *  the key matches.  If successful the function returns an iterator
         *  pointing to the sought after element.  If unsuccessful it returns the
         *  past-the-end ( @c end() ) iterator.
         */
        iterator find(const key_type& x);

        const_iterator find(const key_type& x) const;
        //@}

        /**
         *  @brief  Finds the number of elements.
         *  @param  x  Key to count.
         *  @return  Number of elements with specified key.
         *
         *  This function only makes sense for %unordered_multimap; for
         *  %hash_map the result will either be 0 (not present) or 1
         *  (present).
         */
        size_type count(const key_type& x) const;

        /**
         *  @brief  Finds whether an element with the given key exists.
         *  @param  x  Key of elements to be located.
         *  @return  True if there is any element with the specified key.
         */
        bool contains(const key_type& x) const;

        //@{
        /**
         *  @brief  Subscript ( @c [] ) access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data of the (key,data) %pair.
         *
         *  Allows for easy lookup with the subscript ( @c [] )operator.  Returns
         *  data associated with the key specified in subscript.  If the key does
         *  not exist, a pair with that key is created using default values, which
         *  is then returned.
         *
         *  Lookup requires constant time.
         */
        mapped_type& operator[](const key_type& k);

        mapped_type& operator[](key_type&& k);
        //@}

        //@{
        /**
         *  @brief  Access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data whose key is equal to @a k, if
         *           such a data is present in the %hash_map.
         *  @throw  std::out_of_range  If no such data is present.
         */
        mapped_type& at(const key_type& k);

        const mapped_type& at(const key_type& k) const;
        //@}

        // bucket interface.

        /// Returns the number of buckets of the %hash_map.
        size_type bucket_count() const noexcept;

        /*
        * @brief  Returns the bucket index of a given element.
        * @param  _K  A key instance.
        * @return  The key bucket index.
        */
        size_type bucket(const key_type& _K) const;

        // hash policy.

        /// Returns the average number of elements per bucket.
        float load_factor() const noexcept;

        /// Returns a positive number that the %hash_map tries to keep the
        /// load factor less than or equal to.
        float max_load_factor() const noexcept;

        /**
         *  @brief  Change the %hash_map maximum load factor.
         *  @param  z The new maximum load factor.
         */
        void max_load_factor(float z);

        /**
         *  @brief  May rehash the %hash_map.
         *  @param  n The new number of buckets.
         *
         *  Rehash will occur only if the new number of buckets respect the
         *  %hash_map maximum load factor.
         */
        void rehash(size_type n);

        /**
         *  @brief  Prepare the %hash_map for a specified number of
         *          elements.
         *  @param  n Number of elements required.
         *
         *  Same as rehash(ceil(n / max_load_factor())).
         */
        void reserve(size_type n);

        bool operator==(const hash_map& other) const;
    private:
        allocator_type m_alloc;
        hasher m_hash;
        key_equal m_key_eq;
        value_type* m_data;
        std::vector<char> m_set;
        size_type m_size;
        size_type m_bucket_count;
        float m_max_load_factor = 0.75;
    };

} // namespace fefu