#include <iostream>
#include <assert.h>
#include <map>
#include <tuple>

using namespace std;

namespace InfMatrix {

    template<typename T, T defval>
    class InfMatrix;

    using Index = pair<size_t, size_t>;

    template<typename T, T defval>
    class IndexHelper {
    public:
        ~IndexHelper() {
            if((*m_data)[m_index] == defval)
                m_data->erase(m_index);
        }

        T& operator [](size_t y) {
            m_index.second = y;
            ;
            if(m_data->find(m_index) == m_data->end())
                (*m_data)[m_index] = defval;
            return (*m_data)[m_index];
        }

    private:
        friend class InfMatrix<T, defval>;
        IndexHelper(map<Index, T>* data, size_t x) : m_data(data) {
            m_index.first = x;
        }
    private:
        map<Index, T>*  m_data;
        Index           m_index;
    };



    template<typename T, T defval>
    class InfMatrix {
    public:
        // iterator
        class iterator
        {
        public:
            iterator(map<Index, T>& data, size_t index = 0) : m_data(data), m_index(index), m_it(data.begin()) {}

            iterator operator++() { m_index++; ++m_it; return *this; }

            auto operator*() {
                Index index = m_it->first;
                T val = m_it->second;
                return make_tuple(index.first, index.second, val);
            }
            bool operator==(const iterator& rhs) { return m_index == rhs.m_index; }
            bool operator!=(const iterator& rhs) { return m_index != rhs.m_index; }
        private:
            map<Index, T>&  m_data;
            size_t          m_index;
            typename map<Index,T>::iterator m_it;
        };
        iterator begin()        { return iterator(m_data);    }
        iterator end()          { return iterator(m_data, m_data.size());    }
        //

        InfMatrix() = default;
        ~InfMatrix() = default;

        size_t size() const     { return m_data.size();     }

        IndexHelper<T, defval> operator[](size_t x) {
            return IndexHelper<T, defval>(&m_data, x);
        }
    private:
        map<Index, T>   m_data;
    };
}

using namespace InfMatrix;

void test() {
    InfMatrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix[0][0];
    assert(a == -1);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    // выведется одна строка
    // 100100314
    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

//    matrix[100][100] = -1;
//    assert(matrix.size() == 0);
}

int main()
{
//    test();
    size_t n = 10;
    size_t a = 1;
    size_t b = 9;
    InfMatrix<int, 0> m;
    for(size_t x = 0; x < n; ++x) {
        for(size_t y = 0; y < n; ++y) {
            if(x == y)
                m[x][y] = x;
            if(x == n - 1 - y)
                m[x][y] = n-1-x;
        }
    }

    for(size_t x = a; x < b; ++x) {
        for(size_t y = a; y < b; ++y) {
            cout << m[x][y] << " ";
        }
        cout << endl;
    }
    cout << m.size() << endl;
    int x, y, v;
    for(auto it: m) {
        tie(x, y, v) = it;
        cout << "[" << x << "," << y << "] = " << v << endl;
    }
    return 0;
}
