
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <deque>

#ifdef FT
#define NSP ft
#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#else
#define NSP std
#endif
#define PLN(txt) std::cout << txt << std::endl
#define PB(txt) PLN(((txt)?"yes":"no"))
#define START  begin = std::clock()
#define STOP PLN("time: " <<static_cast<double>((std::clock() - begin)) /CLOCKS_PER_SEC << "s")

template <class T>
struct tmore : std::binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {return x>y;}
};

// template <typename T, typename Alloc>
// std::ostream &operator<< (std::ostream &s, const NSP::vector<T, Alloc>& vec){
// 	for (typename NSP::vector<T, Alloc>::size_type i = 0; i < vec.size(); ++i)
// 		s << "[" << vec[i] << "] ";
// 	return (s);
// };

//#define COUNT 100000000
template<class T>
void printVec(NSP::vector<T> a) {
	for (typename NSP::vector<T>::size_type i = 0; i < a.size(); ++i) {
		PLN(a[i]);
	}
}
template<class T, class U, class V, class W>
void printMap(NSP::map<T, U, V, W> m) {
	for (typename NSP::map<T, U, V, W>::iterator iter = m.begin();
		iter != m.end(); ++iter) {
			PLN("[" << iter->first << ", " << iter->second << "]");
		}
}

template<class T, class U, class V>
void printSet(NSP::set<T, U, V> m) {
	for (typename NSP::set<T, U, V>::iterator iter = m.begin();
		iter != m.end(); ++iter) {
			PLN("[" << *iter << "]");
		}
}

int main(int argc, char **argv) {

	#ifdef FT
	PLN("OWN");
	#else
	PLN("STL");
	#endif
	clock_t	begin;

/*Vector----------------------------------------------------------------------*/
{
	//Constructors + assignment
	PLN("VECTOR: constructor + assignment");
	NSP::vector<int> firstVec;
	NSP::vector<int> secondVec(9, 42);
	printVec(firstVec);
	printVec(secondVec);
	firstVec = secondVec;
	printVec(firstVec);
	NSP::vector<int> thirdVec;
	for (int i = 1; i < 1000; i *= 2)
		thirdVec.push_back(i);
	printVec(thirdVec);	
	NSP::vector<int> forthVec(thirdVec.begin(), thirdVec.end());
	printVec(forthVec);
	NSP::vector<std::string> fifthVec(42, "LOL");
	NSP::vector<std::string> sixthVec(fifthVec);
	printVec(fifthVec);
	printVec(sixthVec);
	//iterators
	PLN("VECTOR: iterators");
	for (NSP::vector<int>::iterator iter = secondVec.begin();
		iter != secondVec.end(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::reverse_iterator iter = secondVec.rbegin();
		iter != secondVec.rend(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::const_iterator iter = secondVec.begin();
		iter != secondVec.end(); ++iter)
		PLN(*iter);
	for (NSP::vector<int>::const_reverse_iterator iter = secondVec.rbegin();
		iter != secondVec.rend(); ++iter)
		PLN(*iter);
	//Capacity
	PLN("VECTOR: capacity");

	PLN(fifthVec.size());
	fifthVec.pop_back();
	PLN(fifthVec.size());
	PLN(fifthVec.max_size());
	fifthVec.resize(300, "Hello");
	printVec(fifthVec);
	fifthVec.resize(10);
	PLN(fifthVec.capacity());
	printVec(fifthVec);
	PLN(fifthVec.capacity());
	fifthVec.reserve(5000);
	PLN(fifthVec.capacity());
	fifthVec.reserve(325);
	PLN(fifthVec.capacity());
	PLN((fifthVec.empty()?"Empty":"Not empty"));
	//access
	PLN("VECTOR: access");

	PLN(firstVec[1]);
	PLN(firstVec[2]);
	try{
		PLN(firstVec.at(300));
	}
	catch (std::exception & e)
	{
		PLN("Exception: " << e.what());
	}
	PLN(firstVec.front() << " " << firstVec.back());
	firstVec.push_back(99);
	PLN(firstVec.front() << " " << firstVec.back());
	//Modifiers
	printVec(thirdVec);
	thirdVec.assign(55, 55);
	printVec(thirdVec);
	thirdVec.assign(forthVec.begin(), --forthVec.end());
	printVec(thirdVec);
	thirdVec.assign(forthVec.rbegin(), forthVec.rend());
	printVec(thirdVec);
	for (size_t i = 0; i < 10000; ++i)
		thirdVec.push_back(i % 42);
	printVec(thirdVec);
	for (size_t i = 0; i < 10000; ++i)
		thirdVec.pop_back();
	printVec(thirdVec);
	thirdVec.insert(thirdVec.end(), 99);
	printVec(thirdVec);
	thirdVec.insert(--thirdVec.end(), 55);
	printVec(thirdVec);
	thirdVec.insert(++thirdVec.begin(), secondVec.begin(), secondVec.end());
	printVec(thirdVec);
	thirdVec.erase(thirdVec.begin());
	printVec(thirdVec);
	thirdVec.erase(thirdVec.begin(), thirdVec.begin() + thirdVec.size() - 9);
	printVec(thirdVec);
	thirdVec.clear();
	forthVec.swap(thirdVec);
	PLN((thirdVec.empty()?"Empty":"Not empty"));
	//allocator
	PLN("VECTOR: allocator");

	NSP::vector<int> dummyVec(5, 3, thirdVec.get_allocator());
	printVec(dummyVec);
	//relational Operators
	PLN("VECTOR: relational operators");

	PLN(((firstVec == secondVec)?"yes":"no"));
	PLN(((thirdVec != forthVec)?"yes":"no"));
	PLN(((firstVec > forthVec)?"yes":"no"));
	PLN(((secondVec >= firstVec)?"yes":"no"));
	PLN(((thirdVec < forthVec)?"yes":"no"));
	PLN(((fifthVec <= sixthVec)?"yes":"no"));
	START;
	PLN("VECTOR: SpeedTest");

	NSP::vector<int> speedVec;
	for (size_t i = 0; i < 100000000; ++i) {
		speedVec.push_back(i);
	}
	for (size_t i = 0; i < 100000000; ++i) {
		speedVec.pop_back();
	}
	STOP;
}

/*Map-------------------------------------------------------------------------*/
{
	//Constructor
	PLN("MAP: constructor");
	NSP::map<char, int> first;
	for(char i = 'a'; i < 'z'; ++i) {
		first[i] = i - 'a';
	}
	NSP::map<char, int> second(first);
	NSP::map<char, int, tmore<char> > third(++first.begin(), --first.end());
	printMap(first);
	printMap(second);
	printMap(third); 
	second = first;
	printMap(second);


	// // //Iterators
	PLN("MAP: Iterators");
	NSP::map<char, int>::iterator iter = first.begin();
	PLN(iter->first);
	PLN((++iter)->first);
	for (NSP::map<char, int>::const_reverse_iterator riter = second.rbegin();
		riter != second.rend(); ++riter) {
			PLN(riter->first);
	}
	//Capacity
	PLN("MAP: capacity");
	PLN(first.size());
	first['?'] = 42;
	PLN(first.size());
	PLN((first.empty()?"empty":"not empty"));

	PLN(first.max_size());

	//Modifiers
	PLN(first.insert(NSP::make_pair('@', 99)).first->first);
	first.insert(first.begin(), NSP::make_pair('T', 67));
	NSP::vector<NSP::pair<char, int> > valVec;
	for (int i = 0; i < 10; ++i)
		valVec.push_back(NSP::make_pair('A' + i, 42 + i));
	first.insert(valVec.begin(), valVec.end());
	printMap(first);

	printMap(second);
	second.erase(++second.begin());
	printMap(second);
	PLN(second.erase('a'));
	second.erase(++second.begin(), --second.end());
	PLN((second.empty()?"empty":"not empty"));
	second.clear();
	PLN((second.empty()?"empty":"not empty"));

	//Observers
	PLN("MAP: observers");
	NSP::map<char ,int>::key_compare a = second.key_comp();
	NSP::map<char,int>::value_compare b = second.value_comp(); 

	PLN((a('c', 'y')?"Yes":"No"));
	PLN((b(NSP::make_pair('b', 13), NSP::make_pair('c', 12))?"Yes":"No"));

	//Operations
	PLN("MAP: operations");
	NSP::map<char, int>::iterator ifind = first.find('a');
	NSP::map<char, int>::const_iterator icfind = first.find('b');

	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	ifind = first.lower_bound('t');
	icfind = first.upper_bound('t');

	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	ifind = first.equal_range('t').first;
	icfind = first.equal_range('t').second;
	PLN(ifind->first << " " << ifind->second);
	PLN(icfind->first << " " << icfind->second);

	//allocator
	PLN("MAP: allocator");

	NSP::map<char, int>::allocator_type allo = first.get_allocator();
	PLN(allo.max_size());

	START;
	PLN("MAP: speedTest");
	int y;
	NSP::map<int , int>	speedMap; 
	for (int i = 0; i < 1000000; ++i)
		speedMap.insert(NSP::make_pair(i, i * 10));
	for (int i = 0; i < 1000000; ++i)
	{
		y = speedMap.find(i)->second;
		y = y - 1;
	}
	for (int i = 0; i < 1000000; ++i)
		speedMap.erase(i);
	STOP;
}

/*stack-----------------------------------------------------------------------*/
{
	PLN("STACK: operations");
	NSP::stack<std::string> first;
	NSP::stack<std::string, std::deque<std::string> > second;

	PLN((first.empty()?"empty":"not empty"));
	PLN((second.empty()?"empty":"not empty"));

	first.push("Hello");
	first.push("world");

	PLN(first.size());
	PLN(first.top());

	for (int i = 0; i < 100; ++i)
		second.push("Hello");
	PLN(second.size() << " " << second.top());
	for (; !second.empty();)
		second.pop();
	PLN(second.size());
	START;
	PLN("STACK: SpeedTest");
	NSP::stack<int> speedStack;
	for (int i = 0; i < 10000000; ++i)
		speedStack.push(i);
	for (int i = 0; i < 10000000; ++i)
		speedStack.pop();
	STOP;
}

/*set-------------------------------------------------------------------------*/
{
	//Constructors
	PLN("SET: constructors");
	NSP::set<int>	first;

	for (int i = 1; i < 10000; i *= 2)
		first.insert(i);
	NSP::set<int, tmore<int> > second(first.begin(), first.end());
	NSP::set<int> third = first;
	printSet(first);
	printSet(second);
	printSet(third);

	// //Iterators
	PLN("SET: iterators");
	NSP::set<int>::const_reverse_iterator crite = first.rend();
	NSP::set<int>::iterator ite = first.begin();
	PLN(*(--(--(--crite))));
	PLN(*(++ite));

	//Capacity
	PLN("SET: capacity");
	PLN(first.size());
	first.erase(128);
	PLN(first.size());
	PLN(first.max_size());

	PLN((first.empty()?"empty":"not empty"));
	first.clear();
	PLN((first.empty()?"empty":"not empty"));

	//Modifiers
	PLN("SET: Modifiers");
	first.insert(third.rbegin(), third.rend());		
	for (NSP::set<int>::iterator iter = third.begin(); iter != third.end(); ++iter)
	{
		PLN(((first.insert((*iter) * 3).second)?"yes":"no"));
		PLN(((first.insert((*iter)).second)?"yes":"no"));
	}
	printSet(first);

	first.erase(++first.begin(), --first.end());
	printSet(first);

	first.erase(first.begin());
	PLN(first.size());

	NSP::swap(first, third);
	printSet(first);
	printSet(third);
	third.clear();

	//Observers
	PLN("SET: observers");
	NSP::set<int>::key_compare a = first.key_comp();
	NSP::set<int>::value_compare b = first.value_comp();

	PLN(((a(9, 10))?"Yes":"No"));
	PLN(((b(10, 9))?"Yes":"No"));

	//Operations
	PLN("SET: Operations");
	PB(first.find(-99) == first.end());
	PB(first.count(-42));
	PB(first.count(64));

	PLN(*first.lower_bound(1024));
	PLN(*first.upper_bound(1024));
	PLN(*(first.equal_range(1024).first));
	PLN(*(first.equal_range(1024).second));

	// //Allocator
	PLN("SET: allocator");

	PLN(first.get_allocator().max_size());

	//speedTest
	PLN("SET: speedTest");
	START;
	NSP::set<int> speedSet;
	for (int i = 0; i < 1000000; ++i)
	{
		speedSet.insert(i);
	}
	PLN(speedSet.size());
	for (int i = 0; i < 1000000; ++i)
	{
		speedSet.erase(i);
	}
	speedSet.clear();

	STOP;
}

{
	if (argc > 0)
	{
		std::string leakscmd = "leaks ";
		leakscmd.append(argv[0] + 2);
		PLN(leakscmd);
		system(leakscmd.c_str()); 
	}
}
};

