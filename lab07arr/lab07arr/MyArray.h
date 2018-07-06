#pragma once

#include "stdafx.h"

namespace arrayenv
{
	
	template<typename IteratorType, typename Container>
	class general_iterator
	{
		using iterator_traits = std::iterator_traits<IteratorType>;
	public:
		using iterator_category = typename iterator_traits::iterator_category;
		using iterator_type = IteratorType;
		using value_type = typename iterator_traits::value_type;
		using difference_type = typename iterator_traits::difference_type;
		using pointer = typename iterator_traits::pointer;
		using reference = typename iterator_traits::reference;

		general_iterator() noexcept
			:m_current(IteratorType{})
		{
		}

		general_iterator(IteratorType const & src) noexcept 
			:m_current(src)
		{
		}

		template<typename SourceIterator>
		general_iterator(general_iterator<SourceIterator, typename std::enable_if<std::is_same<
			SourceIterator, typename Container::pointer>::value, Container>::type> const& src)
			:m_current(src.base())
		{
		}

		reference operator*() const noexcept
		{
			return *m_current;
		}
		pointer operator->() const noexcept
		{
			return m_current;
		}

		general_iterator& operator++() noexcept
		{
			++m_current;
			return *this;
		}

		general_iterator operator++(int) noexcept
		{
			general_iterator old(m_current);
			++m_current;
			return old;
		}

		general_iterator& operator--() noexcept
		{
			--m_current;
			return *this;
		}

		general_iterator operator--(int) noexcept
		{
			general_iterator old(m_current);
			--m_current;
			return old;
		}

		general_iterator operator+(difference_type diff) const noexcept
		{
			return m_current + diff;
		}

		general_iterator& operator+=(difference_type diff) noexcept
		{
			m_current += diff;
			return *this;
		}

		general_iterator operator-(difference_type diff) const noexcept
		{
			return m_current - diff;
		}

		general_iterator& operator-=(difference_type diff) noexcept
		{
			m_current -= diff;
			return *this;
		}


		iterator_type const& base() const noexcept
		{
			return m_current;
		}


	private:
		IteratorType m_current;

	}; //class general_iterator


	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator==(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() == right.base();
	}

	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator!=(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() != right.base();
	}


	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator<(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() < right.base();
	}

	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator<=(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() <= right.base();
	}

	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator>(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() > right.base();
	}

	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		bool operator>=(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			)
	{
		return left.base() >= right.base();
	}


	template<
		typename IteratorTypeLeft,
		typename IteratorTypeRight,
		typename Container
	>
		auto operator-(
			general_iterator<IteratorTypeLeft, Container> const & left,
			general_iterator<IteratorTypeRight, Container> const & right
			) -> decltype(left.base() - right.base())
	{
		return left.base() - right.base();
	}



	template<typename T>
	void destroy_at(T* ptr) noexcept
	{
		ptr->~T();
	}

	template<typename ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last) noexcept
	{
		for (; first != last; ++first) 
		{
			::arrayenv::destroy_at(std::addressof(*first));
		}
	}

	template<typename T, typename ... Args>
	void construct_at(T* p, Args && ...args)
	{
		::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
	}


	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator start, InputIterator finish, ForwardIterator destination)
	{
		ForwardIterator current = destination;
		try 
		{
			for (; start != finish; ++start) 
			{
				::arrayenv::construct_at(std::addressof(*current), *start);
				++current;
			}
			return current;
		}
		catch (...) 
		{
			::arrayenv::destroy(destination, current);
			throw;
		}
	}

	template<typename T, typename ForwardIterator>
	ForwardIterator uninitialized_fill(ForwardIterator start, ForwardIterator finish, T const& source)
	{
		ForwardIterator current = start;
		try 
		{
			for (; current != finish; ++current) 
			{//Создаем элементы в указанном участке памяти
				::arrayenv::construct_at(std::addressof(*current), source);
			}
			return current;
		}
		catch (...) 
		{
			::arrayenv::destroy(start, current);
			throw;
		}
	}


	template<typename T, typename ForwardIterator>
	ForwardIterator uninitialized_fill_n(ForwardIterator start, std::size_t count, T const& source)
	{
		ForwardIterator current = start;
		try 
		{
			for (; count != 0; --count) 
			{
				::arrayenv::construct_at(std::addressof(*current), source);
				++current;
			}
			return current;
		}
		catch (...) 
		{
			::arrayenv::destroy(start, current);
			throw;
		}
	}


	template<typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator source_begin, InputIterator source_end, OutputIterator dest_begin)
	{
		for (; source_begin != source_end; ++source_begin) 
		{
			*dest_begin = *source_begin;
			++dest_begin;
		}
		return dest_begin;
	}


	template<typename IteratorCategory, typename IteratorType>
	constexpr bool minimal_iterator_category =
		std::is_base_of<IteratorCategory, typename std::iterator_traits<IteratorType>::iterator_category>::value;
	
	namespace iterdist  // реализация разности итераторов в зависимости от категории итератора
	{
		template<typename Iterator,	bool IsRandomAccess = 
			minimal_iterator_category<std::random_access_iterator_tag, Iterator>
		>
			struct distance_impl
		{
			typename std::iterator_traits<Iterator>::difference_type
				operator()(Iterator first, Iterator last)
			{
				typename std::iterator_traits<Iterator>::difference_type count = 0;
				for (; first != last; ++first) 
				{
					++count;
				}
				return count;
			}
		};

		template<typename Iterator>
		struct distance_impl<Iterator, true>
		{
			typename std::iterator_traits<Iterator>::difference_type
				operator()(Iterator first, Iterator last)
			{
				return last - first;
			}
		};
	}//namespace iterdist


	template<typename Iterator>
	typename std::iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last)
	{
		return ::arrayenv::iterdist::distance_impl<Iterator>()(first, last);
	}

	template<typename ForwardIterator>
	void rotate(ForwardIterator begin, ForwardIterator first, ForwardIterator end)
	{
		while (begin != first && first != end) 
		{
			ForwardIterator beginCopy = first;
			for (; begin != first && beginCopy != end; ++begin, ++beginCopy) 
			{
				std::iter_swap(begin, beginCopy);
			}
			if (begin == first) 
			{
				first = beginCopy;
			}
		}
	}


	template<typename T, typename = void>
	struct is_iterator
	{
		static constexpr bool value = false;
	};

	template<typename T>
	struct is_iterator<T, typename std::enable_if<!std::is_same<
		typename std::iterator_traits<T>::value_type, void>::value, void>::type>
	{
		static constexpr bool value = true;
	};

	
	template<typename T, typename Alloc = std::allocator<T>>
	class CMyArray
	{
	public:
		using allocator_type = typename Alloc::template rebind<T>::other;
		using value_type = typename allocator_type::value_type;//Тип хранящихся элементов
		using reference = typename allocator_type::reference;//Ссылка на тип хранящихся элементов
		using const_reference = typename allocator_type::const_reference;//Ссылка на константный тип хранящихся элементов
		using pointer = typename allocator_type::pointer;//Указатель на тип хранящихся элементов
		using const_pointer = typename allocator_type::const_pointer;//Указатель на константный тип хранящихся элементов
		using size_type = typename allocator_type::size_type;//Тип для размера и индексов
		using difference_type = typename allocator_type::difference_type;//Тип для разницы указателей и итераторов
		using iterator = general_iterator<pointer, CMyArray>;
		using const_iterator = general_iterator<const_pointer, CMyArray>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;


		/* интерфейс СMyArray

		 MyArray() noexcept

		 MyArray(MyArray const & src)

		 MyArray(size_type size, const_reference src = value_type{})
		 
		 template<typename InputIterator>
		 MyArray(InputIterator first, InputIterator last)

		 MyArray& operator=(MyArray const & rhv)

		 ~MyArray()

		 size_type max_size() const noexcept

		 size_type size() const noexcept
		 
		 bool empty() const noexcept
		 
		 size_type capacity() const noexcept
		 
		 pointer data() noexcept
		
		 const_pointer data() const noexcept
		 
		 reference operator[](size_type index) noexcept
		 
		 const_reference operator[](size_type index) const noexcept
		 
		 reference front() noexcept
		 
		 const_reference front() const noexcept
		 
		 reference back() noexcept
		 
		 const_reference back() const noexcept
		 
		 void swap(MyArray & src) noexcept
		 
		 void reserve(size_type new_capacity)
		 
		 void resize(size_type new_size)

		 void resize(size_type new_size, const_reference value)

		 void push_back(const_reference value)

		 void pop_back()

		 iterator erase(const_iterator first) noexcept(std::is_nothrow_assignable<value_type, value_type>::value)

		 iterator erase(const_iterator first, const_iterator last) noexcept(std::is_nothrow_assignable<value_type, value_type>::value)
		 
		 void clear() noexcept

		 template<typename InputIterator>
		 typename std::enable_if<::arrayenv::is_iterator<InputIterator>::value, iterator>::type
		 insert(const_iterator insert_position, InputIterator first, InputIterator last)

		 iterator insert(const_iterator insert_position, T const & value)

		 iterator insert(const_iterator insert_position, size_type count, T const& value)

		 iterator begin() noexcept
		 
		 const_iterator begin() const noexcept
		 
		 const_iterator cbegin() const noexcept
		 
		 iterator end() noexcept
		 
		 const_iterator end() const noexcept 

		 const_iterator cend() const noexcept
		 
		 reverse_iterator rbegin() noexcept
		 
		 const_reverse_iterator rbegin() const noexcept
		 
		 const_reverse_iterator crbegin() const noexcept
		 
		 reverse_iterator rend() noexcept
		 
		 const_reverse_iterator rend() const noexcept
		 
		 const_reverse_iterator crend() const noexcept
		 
		 */

		CMyArray() noexcept
			:m_impl()
		{
		}

		CMyArray(CMyArray const & src)
			: m_impl(src.size())
		{
			m_impl.set_finish(::arrayenv::uninitialized_copy(src.m_impl.start(), src.m_impl.finish(), m_impl.start()));
		}

		CMyArray(size_type size, const_reference src = value_type{})
			: m_impl(size)
		{
			m_impl.set_finish(::arrayenv::uninitialized_fill_n(m_impl.start(), size, src));
		}

		template<typename InputIterator>
		CMyArray(InputIterator first, InputIterator last)
		{
			create_copy_from(first, last);
		}

		CMyArray& operator=(CMyArray const& carr)
		{
			if (this == &carr) 
			{
				return *this;
			}
			if (carr.empty()) 
			{
				clear();
				return *this;
			}
			size_type new_size = carr.size();
			if (capacity() < new_size) 
			{
				create_copy_from(carr.m_impl.start(), carr.m_impl.finish(), new_size);
			}
			else 
			{
				pointer dest_current = m_impl.start();
				pointer dest_finish = m_impl.finish();
				pointer dest_middle = dest_current + std::min(new_size, m_impl.size());
				const_pointer source_current = carr.m_impl.start();
				const_pointer source_finish = carr.m_impl.finish();
				for (; dest_current != dest_middle; ++dest_current) 
				{
					*dest_current = *source_current;
					++source_current;
				}
				if (new_size != m_impl.size()) 
				{
					if (source_current == source_finish) 
					{
						destroy(dest_current, dest_finish);
					}
					else 
					{
						dest_current = ::arrayenv::uninitialized_copy(source_current, source_finish, dest_current);
					}
					m_impl.set_finish(dest_current);
				}
			}
			return *this;
		}

		~CMyArray()
		{
			clear();
		}

		size_type max_size() const noexcept
		{
			return m_impl.max_size();
		}

		size_type size() const noexcept
		{
			return m_impl.size();
		}

		bool empty() const noexcept
		{
			return m_impl.empty();
		}

		size_type capacity() const noexcept
		{
			return m_impl.capacity();
		}

		pointer data() noexcept
		{
			return m_impl.start();
		}

		const_pointer data() const noexcept
		{
			return m_impl.start();
		}

		reference operator[](size_type index) noexcept
		{
			return m_impl.start()[index];
		}

		const_reference operator[](size_type index) const noexcept
		{
			return m_impl.start()[index];
		}

		reference front() noexcept
		{
			return *m_impl.start();
		}

		const_reference front() const noexcept
		{
			return *m_impl.start();
		}

		reference back() noexcept
		{
			return *(m_impl.finish() - 1);
		}

		const_reference back() const noexcept
		{
			return *(m_impl.finish() - 1);
		}

		void swap(CMyArray & src) noexcept
		{
			m_impl.swap_data(src.m_impl);
		}

		void reserve(size_type new_capacity)
		{
			if (capacity() < new_capacity) 
			{
				create_copy_from(m_impl.start(), m_impl.finish(), new_capacity);
			}
		}

		void resize(size_type new_size)
		{
			if (new_size <= size()) 
			{
				crop(new_size);
			}
			else 
			{
				resize(new_size, value_type{});
			}
		}

		void resize(size_type new_size, const_reference value)
		{
			if (new_size <= size()) 
			{
				crop(new_size);
			}
			else 
			{
				reserve(new_size);
				m_impl.set_finish(uninitialized_fill_n(m_impl.finish(), new_size - size(), value));
			}
		}

		void push_back(const_reference value)
		{
			if (m_impl.size() == m_impl.capacity()) 
			{
				reserve(get_next_size(m_impl.size()));
			}
			m_impl.set_finish(::arrayenv::uninitialized_fill_n(m_impl.finish(), 1, value));
		}

		void pop_back()
		{
			m_impl.set_finish(m_impl.finish() - 1);
			m_impl.destroy(m_impl.finish());
		}

		iterator erase(const_iterator first) noexcept(std::is_nothrow_assignable<value_type, value_type>::value)
		{
			return erase(first, first + 1);
		}

		iterator erase(const_iterator first, const_iterator last) noexcept(std::is_nothrow_assignable<value_type, value_type>::value)
		{
			iterator destination = begin() + ::example::distance(cbegin(), first);
			iterator new_end = ::arrayenv::copy(last, cend(), destination);
			crop(static_cast<size_type>(new_end - begin()));
			return new_end;
		}

		void clear() noexcept
		{
			crop(0);
		}

		template<typename InputIterator>
		typename std::enable_if<::arrayenv::is_iterator<InputIterator>::value, iterator>::type
			insert(const_iterator insert_position, InputIterator first, InputIterator last)
		{
			size_type insert_index = static_cast<size_type>(::arrayenv::distance(cbegin(), insert_position));
			size_type old_size = m_impl.size();
			try 
			{
				while (first != last) 
				{
					push_back(*first);
					++first;
				}
				::arrayenv::rotate(m_impl.start() + insert_index, m_impl.start() + old_size, m_impl.finish());
			}
			catch (...) 
			{
				crop(old_size);
				throw;
			}
			return iterator(m_impl.start() + static_cast<difference_type>(insert_index));
		}

		iterator insert(const_iterator insert_position, T const & value)
		{
			return insert(insert_position, std::addressof(value), std::addressof(value) + 1);
		}

		iterator insert(const_iterator insert_position, size_type count, T const& value)
		{
			size_type insert_index = static_cast<size_type>(::arrayenv::distance(cbegin(), insert_position));
			size_type old_size = m_impl.size();
			try 
			{
				reserve(m_impl.size() + count);
				m_impl.set_finish(::arrayenv::uninitialized_fill_n(m_impl.finish(), count, value));
				::arrayenv::rotate(m_impl.start() + insert_index, m_impl.start() + old_size, m_impl.finish());
			}
			catch (...) 
			{
				crop(old_size);
				throw;
			}
			return iterator(m_impl.start() + static_cast<difference_type>(insert_index));
		}

		iterator begin() noexcept
		{
			return m_impl.start();
		}

		const_iterator begin() const noexcept
		{
			return m_impl.start();
		}

		const_iterator cbegin() const noexcept
		{
			return begin();
		}

		iterator end() noexcept
		{
			return m_impl.finish();
		}

		const_iterator end() const noexcept 
		{
			return m_impl.finish();
		}

		const_iterator cend() const noexcept
		{
			return end();
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(m_impl.finish());
		}

		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(m_impl.finish());
		}

		const_reverse_iterator crbegin() const noexcept
		{
			return rbegin();
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(m_impl.start());
		}

		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(m_impl.start());
		}

		const_reverse_iterator crend() const noexcept
		{
			return rend();
		}

	private:
		struct vector_data
		{
			vector_data() :
				m_start(),
				m_finish(),
				m_end_of_storage()
			{
			}

			size_type size() const noexcept
			{
				return static_cast<size_type>(m_finish - m_start);//Разница между указателем на конец и начало
			}

			pointer start() noexcept
			{
				return m_start;
			}

			const_pointer start() const noexcept
			{
				return m_start;
			}

			pointer finish() noexcept
			{
				return m_finish;
			}

			const_pointer finish() const noexcept
			{
				return m_finish;
			}

			bool is_null() const noexcept
			{
				return m_start == nullptr;
			}

			void set_finish(pointer p) noexcept
			{
				m_finish = p;
			}

			void swap_data(vector_data& src) noexcept
			{
				std::swap(m_start, src.m_start);
				std::swap(m_finish, src.m_finish);
				std::swap(m_end_of_storage, src.m_end_of_storage);
			}

			void set_null() noexcept
			{
				m_start = m_finish = m_end_of_storage = nullptr;
			}

			bool empty() const noexcept
			{
				return m_start == m_finish;
			}

			constexpr size_type max_capacity() const noexcept
			{
				return static_cast<size_type>(std::numeric_limits<difference_type>::max() / sizeof(value_type) - sizeof(value_type));
			}

			size_type capacity() const noexcept
			{
				return static_cast<size_type>(m_end_of_storage - m_start);
			}

			pointer m_start;//Начало вектора
			pointer m_finish;//Конец вектора
			pointer m_end_of_storage;//Конец выделенной памяти
		};//struct vector_data

		struct vector_impl : allocator_type, vector_data 
		{
			vector_impl() 
			{
			}

			vector_impl(size_type size) 
				:vector_impl() 
			{
				create_storage(size);
			}

			~vector_impl()
			{
				destroy_storage();
			}


			void set_finish(pointer p) noexcept
			{
				vector_data::m_finish = p;
			}

			void create_storage(size_type size)
			{
				if (size == 0) 
				{
					vector_data::set_null();
				}
				else 
				{
					vector_data::m_start = allocator_type::allocate(size);
					vector_data::m_finish = vector_data::m_start;
					vector_data::m_end_of_storage = vector_data::m_start + size;
				}
			}

			void create_storage_to(vector_data& data, size_type size)
			{
				if (size == 0) 
				{
					data.set_null();
				}
				else 
				{
					data.m_start = allocator_type::allocate(size);
					data.m_finish = data.m_start;
					data.m_end_of_storage = data.m_start + size;
				}
			}
			
			void destroy_storage()
			{
				if (!vector_data::is_null()) 
				{
					destroy_storage(*this);
				}
			}

			void destroy_storage(vector_data& data)
			{
				allocator_type::deallocate(data.m_start, data.size());
				data.set_null();
			}

			vector_impl& operator=(vector_data const & data) noexcept
			{
				destroy_storage();
				static_cast<vector_data&>(*this) = data;
				return *this;
			}


		};//struct vector_impl

		size_type get_next_size(size_type old_size) const noexcept
		{
			return static_cast<size_type>(old_size * 1.6) + 1u;
		}

		vector_data reserve_storage(size_type new_capacity)
		{
			vector_data data;
			if (m_impl.max_capacity() < new_capacity) {
				throw std::length_error("vector::reserve: invalid size");
			}
			if (m_impl.capacity() < new_capacity) {
				m_impl.create_storage_to(data, new_capacity);
			}
			return data;
		}

		void crop(size_type new_size)
		{
			destroy(m_impl.start() + new_size, m_impl.finish());
			m_impl.set_finish(m_impl.start() + new_size);
		}

		template<typename Iterator>
		void create_copy_from(Iterator start, Iterator finish, size_type new_capacity)
		{
			vector_data new_data = create_initialized_storage(start, finish, new_capacity);
			destroy(m_impl.start(), m_impl.finish());
			m_impl = new_data;
		}

		template<typename Iterator>
		typename std::enable_if<::arrayenv::minimal_iterator_category<
			std::forward_iterator_tag, Iterator>, void>::type
			create_copy_from(Iterator start, Iterator finish)
		{
			size_type new_capacity = static_cast<size_type>(::arrayenv::distance(start, finish));
			create_copy_from(start, finish, new_capacity);
		}

		template<typename Iterator>
		typename std::enable_if<!::arrayenv::minimal_iterator_category<
			std::forward_iterator_tag, Iterator>, void>::type
			create_copy_from(Iterator start, Iterator finish)
		{
			while (start != finish) 
			{
				push_back(*start);
			}
		}


		template<typename Iterator>
		vector_data create_initialized_storage(Iterator start, Iterator finish, size_type new_capacity)
		{
			vector_data result;
			if (new_capacity) 
			{
				result = reserve_storage(new_capacity);
				try 
				{
					result.set_finish(::arrayenv::uninitialized_copy(start, finish, result.start()));
				}
				catch (...) 
				{
					m_impl.destroy_storage(result);
					throw;
				}
			}
			return result;
		}

		vector_impl m_impl;
	};//class CMyArray

}//namespace example