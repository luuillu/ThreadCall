#define LOG_DEBUG(...) printf(__VA_ARGS__), printf("\n")

#include "threadCall.h"
#include <vector>

struct ThreadCallTest {
	ThreadCallTest(): m_MsgId(0){}

	~ThreadCallTest()
	{
		// 模拟post消息异步执行
		for (LIST_PTHREAD_CALL::iterator it = m_listPThreadCall.begin(); it != m_listPThreadCall.end(); ++it)
		{
			ThreadCallManager::ThreadCall* pThreadCall = *it;
			pThreadCall->execute();
			delete pThreadCall;
		}
		m_listPThreadCall.clear();
	}

	TDC_GET_FUNCTOR(postCall, &ThreadCallTest::OnCreatePostThreadCall, ThreadCallManager::PostTrait);
	TDC_GET_FUNCTOR(sendCall, &ThreadCallTest::OnCreateSendThreadCall, ThreadCallManager::SendTrait);

	int64_t OnCreatePostThreadCall(ThreadCallManager::ThreadCall* pThreadCall, const char* file, int32_t line, void* pRet)
	{
		//模拟异步执行
		m_listPThreadCall.push_back(pThreadCall);
		return ++m_MsgId;
	}

	int64_t OnCreateSendThreadCall(ThreadCallManager::ThreadCall* pThreadCall, const char* file, int32_t line, void* pRet)
	{
		pThreadCall->execute(pRet);
		delete pThreadCall;
		return ++m_MsgId;
	}

	void test_0()
	{
		LOG_DEBUG("ThreadCallTest test_0() running");
	}

	int test_2(const int& a, const int& b)
	{
		LOG_DEBUG("ThreadCallTest test_2() running a=[%d], b=[%d]", a, b);
		return 10086;
	}

	int64_t test_string(std::string& s, void *addr){
		LOG_DEBUG("ThreadCallTest test_string() running s=[%s], addr of s:[%p], orgin addr:[%p]", s.c_str(), &s, addr);
		return 1234567890;
	}

	static void test()
	{
		LOG_DEBUG("***ThreadCallTest test() Send Begin***");

		ThreadCallTest test;
		int ret = -1;
		int64_t msgId = test.sendCall(&test, &ThreadCallTest::test_0, __FILE__, __LINE__, &ret)();
		LOG_DEBUG("ThreadCallTest test() sendCall test_0, msgId=[%lld], ret = [%d]\n", msgId, ret);

		ret = -1;
		msgId = test.sendCall(&test, &ThreadCallTest::test_2, __FILE__, __LINE__, &ret)(0, 6);
		LOG_DEBUG(" ThreadCallTest test() sendCall test_2, msgId=[%lld], ret = [%d]\n", msgId, ret);

		int64_t llRet = -1;
		std::string str = "Hello send call";
		msgId = test.sendCall(&test, &ThreadCallTest::test_string, __FILE__, __LINE__, &llRet)(str, &str);
		str.clear();
		LOG_DEBUG("ThreadCallTest test() sendCall test_string, msgId=[%lld], llRet = [%lld]\n", msgId, llRet);

		LOG_DEBUG("***ThreadCallTest test() Send End***");

		//PostCall
		LOG_DEBUG("***ThreadCallTest test() Post Begin***");

		msgId = test.postCall(&test, &ThreadCallTest::test_0, __FILE__, __LINE__)();
		LOG_DEBUG("ThreadCallTest test() postCall test_0, msgId=[%lld], ret = [%d]\n", msgId, ret);

		ret = -1;
		msgId = test.postCall(&test, &ThreadCallTest::test_2, __FILE__, __LINE__, &ret)(0, 6);
		LOG_DEBUG(" ThreadCallTest test() postCall test_2, msgId=[%lld], ret = [%d]\n", msgId, ret);

		str = "Hello post call";
		msgId = test.postCall(&test, &ThreadCallTest::test_string, __FILE__, __LINE__)(str, &str);
		str.clear();
		LOG_DEBUG("ThreadCallTest test() postCall test_string, msgId=[%lld], llRet = [%lld]\n", msgId, llRet);

		LOG_DEBUG("***ThreadCallTest test() Post End***");

	}

	typedef std::vector<ThreadCallManager::ThreadCall*> LIST_PTHREAD_CALL;
	LIST_PTHREAD_CALL m_listPThreadCall;
	int64_t m_MsgId;

};

#define TDC_TO_STRING_(...) #__VA_ARGS__
#define TDC_TO_STRING(x) "expand [ "#x" ]is:[" TDC_TO_STRING_(x)"]"

int main()
{
	ThreadCallTest::test();
	return 0;
}
