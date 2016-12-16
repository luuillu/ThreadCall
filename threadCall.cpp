#include "threadCall.h"
#include <vector>
struct ThreadCallTest {
	~ThreadCallTest()
	{
		for (LIST_PTHREAD_CALL::iterator it = m_listPThreadCall.begin(); it != m_listPThreadCall.end(); ++it)
		{
			ThreadCallManager::ThreadCall* pThreadCall = *it;
			pThreadCall->execute();
			delete (*it);
		}
		m_listPThreadCall.clear();
	}
	TDC_GET_FUNCTOR(getFunctor, &ThreadCallTest::OnCreateThreadCall);

	int64_t OnCreateThreadCall(ThreadCallManager::ThreadCall* pThreadCall, const char* file, int32_t line)
	{
		std::cout<<"OnCreateThreadCall() file="<<file<<",line="<<line<<std::endl;
		m_listPThreadCall.push_back(pThreadCall);
		return 0;
	}

	int f(const int& a, int b)
	{
		std::cout<<"ThreadCallTest() a="<<a<<",b="<<b<<std::endl;
		return 0;
	}

	void g()
	{
		std::cout<<"ThreadCallTest() this is g()"<<std::endl;
	}

	//for reference, only support const reference type
	int h(const std::string &s, void *addr){
		std::cout<<"ThreadCallTest() this is h() s="<<s<<", addr of s:"<<&s<<", orgin addr:"<<addr<<std::endl;
		return 0;
	}

	static void test()
	{
		ThreadCallTest a;
		a.getFunctor(&a, &ThreadCallTest::f, __FILE__, __LINE__)(0, 6);
		a.getFunctor(&a, &ThreadCallTest::g, __FILE__, __LINE__)();
		std::string str = "Hello h";
		a.getFunctor(&a, &ThreadCallTest::h, __FILE__, __LINE__)(str, &str);
		str.clear();
	}

	typedef std::vector<ThreadCallManager::ThreadCall*> LIST_PTHREAD_CALL;
	LIST_PTHREAD_CALL m_listPThreadCall;

};

#define TDC_TO_STRING_(...) #__VA_ARGS__
#define TDC_TO_STRING(x) "expand [ "#x" ]is:[" TDC_TO_STRING_(x)"]"

int main()
{

	ThreadCallTest::test();
	return 0;
}
