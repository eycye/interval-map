#include <iostream>
using namespace std;
#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin; // default min
	std::map<K,V> m_map;
public:
	// constructor associates whole range of < K with default min val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	/** 
	   Assign value val to interval [keyBegin, keyEnd).
	   Overwrite previous values in this interval.
	   Conforming to the C++ Standard Library conventions, the interval
	   includes keyBegin, but excludes keyEnd.
	   If !( keyBegin < keyEnd ), this designates an empty interval,
	   and assign must do nothing.
	**/	
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		// effectively operator=( K const& key )
		// INSERT YOUR SOLUTION HERE

		if ( keyBegin >= keyEnd ) return;
		
		// base case: empty m_map
		if (!m_map.size()) {
			m_map[keyBegin] = val;
			m_map[keyEnd] = m_valBegin;
			return;
		}

		auto itBegin=m_map.lower_bound(keyBegin);
		auto itEnd = m_map.upper_bound(keyEnd);

		// CASE 1: keyStart > maxKey
		if (itBegin == m_map.end() || keyBegin > m_map.rbegin()->first) {
			auto prevVal = (--(itBegin))->second;
			if (prevVal != val) {
				m_map[keyEnd] = prevVal;
				m_map[keyBegin] = val;
			}
			return;
		}
		// CASE 2: keyBegin <= minKey
		if (itBegin == m_map.begin() || keyBegin < m_map.begin()->first) {
			auto prevVal = this->operator[](keyEnd);
			m_map.erase(itBegin, itEnd);
			if (prevVal != val) {
				m_map[keyEnd] = prevVal ;
				m_map[keyBegin] = val;
			} 
			return;
		}
		
		// CASE 3: minKey < keyBegin <= maxKey
		auto itBeginPrev = itBegin;
		itBeginPrev--;
		// case 3(a): previous key maps to != val
		auto prevVal = this->operator[](keyEnd);
		if (itBeginPrev->second != val) {
			m_map.erase(itBegin, itEnd);
			m_map[keyBegin] = val;
			m_map[keyEnd] = prevVal;
			return;
		}
		// case 3(b): previous key maps to val, make canonical
		
		while(itBegin != itEnd && itBegin->second == val) {
			itBegin = m_map.erase(itBegin);
		}
		if (itBegin != itEnd) {m_map[itBegin->first] = val;}
		m_map[keyEnd] = prevVal;
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.
void IntervalMapTest() {
	interval_map<char,int> test1('A');
	test1.assign(1,3,'B');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(-2,0,'C');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(4,5,'D');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(2,4,'A');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(-3,-1,'E');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(-1,-1,'F');
	for (int i = -5; i <= 5; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(10,15,'/');
	for (int i = -5; i <= 20; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(-10,-5,'G');
	for (int i = -11; i <= 0; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"******\n";
	test1.assign(-6,-2,'+');
	for (int i = -11; i <= 0; i++) {
		cout << "Key = " << i << ". Value: "<< static_cast<char>(test1[i])<< '\n';
	}
	cout<<"Done.";
}

int main() {
	IntervalMapTest();

	return 0;
}