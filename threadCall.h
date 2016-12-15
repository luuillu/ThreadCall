#pragma once
#include <iostream>
//macro prefix TDC_

//最大支持31 个参数
#define TDC_FOR_EACH_1(f) f(1)
#define TDC_FOR_EACH_2(f) TDC_FOR_EACH_1(f) f(2)
#define TDC_FOR_EACH_3(f) TDC_FOR_EACH_2(f) f(3)
#define TDC_FOR_EACH_4(f) TDC_FOR_EACH_3(f) f(4)
#define TDC_FOR_EACH_5(f) TDC_FOR_EACH_4(f) f(5)
#define TDC_FOR_EACH_6(f) TDC_FOR_EACH_5(f) f(6)
#define TDC_FOR_EACH_7(f) TDC_FOR_EACH_6(f) f(7)
#define TDC_FOR_EACH_8(f) TDC_FOR_EACH_7(f) f(8)
#define TDC_FOR_EACH_9(f) TDC_FOR_EACH_8(f) f(9)
#define TDC_FOR_EACH_10(f) TDC_FOR_EACH_9(f) f(10)
#define TDC_FOR_EACH_11(f) TDC_FOR_EACH_10(f) f(11)
#define TDC_FOR_EACH_12(f) TDC_FOR_EACH_11(f) f(12)
#define TDC_FOR_EACH_13(f) TDC_FOR_EACH_12(f) f(13)
#define TDC_FOR_EACH_14(f) TDC_FOR_EACH_13(f) f(14)
#define TDC_FOR_EACH_15(f) TDC_FOR_EACH_14(f) f(15)
#define TDC_FOR_EACH_16(f) TDC_FOR_EACH_15(f) f(16)
#define TDC_FOR_EACH_17(f) TDC_FOR_EACH_16(f) f(17)
#define TDC_FOR_EACH_18(f) TDC_FOR_EACH_17(f) f(18)
#define TDC_FOR_EACH_19(f) TDC_FOR_EACH_18(f) f(19)
#define TDC_FOR_EACH_20(f) TDC_FOR_EACH_19(f) f(20)
#define TDC_FOR_EACH_21(f) TDC_FOR_EACH_20(f) f(21)
#define TDC_FOR_EACH_22(f) TDC_FOR_EACH_21(f) f(22)
#define TDC_FOR_EACH_23(f) TDC_FOR_EACH_22(f) f(23)
#define TDC_FOR_EACH_24(f) TDC_FOR_EACH_23(f) f(24)
#define TDC_FOR_EACH_25(f) TDC_FOR_EACH_24(f) f(25)
#define TDC_FOR_EACH_26(f) TDC_FOR_EACH_25(f) f(26)
#define TDC_FOR_EACH_27(f) TDC_FOR_EACH_26(f) f(27)
#define TDC_FOR_EACH_28(f) TDC_FOR_EACH_27(f) f(28)
#define TDC_FOR_EACH_29(f) TDC_FOR_EACH_28(f) f(29)
#define TDC_FOR_EACH_30(f) TDC_FOR_EACH_29(f) f(30)
#define TDC_FOR_EACH_31(f) TDC_FOR_EACH_30(f) f(31)

#define TDC_DEFINE_ALL(f, ...) f(1, __VA_ARGS__) f(2, __VA_ARGS__) f(3, __VA_ARGS__) f(4, __VA_ARGS__) f(5, __VA_ARGS__)\
		f(6, __VA_ARGS__) f(7, __VA_ARGS__) f(8, __VA_ARGS__) f(9, __VA_ARGS__) f(10, __VA_ARGS__) f(11, __VA_ARGS__)\
		f(12, __VA_ARGS__) f(13, __VA_ARGS__) f(14, __VA_ARGS__) f(15, __VA_ARGS__) f(16, __VA_ARGS__) f(17, __VA_ARGS__)\
		f(18, __VA_ARGS__) f(19, __VA_ARGS__) f(20, __VA_ARGS__) f(21, __VA_ARGS__) f(22, __VA_ARGS__) f(23, __VA_ARGS__) f(24, __VA_ARGS__) \
		f(25, __VA_ARGS__) f(26, __VA_ARGS__) f(27, __VA_ARGS__) f(28, __VA_ARGS__) f(29, __VA_ARGS__) f(30, __VA_ARGS__) f(31, __VA_ARGS__)

#define TDC_CONNECT_N_(f, n) f##n
#define TDC_CONNECT_N(f, n) TDC_CONNECT_N_(f, n)

#define TDC_CALL_FUNCTION(f, ...)  f(__VA_ARGS__)
#define TDC_CALL_F_N(f, n, ...) TDC_CALL_FUNCTION(TDC_CONNECT_N(f, n), __VA_ARGS__)
#define TDC_FOR_EACH_N(f, n) TDC_CALL_F_N(TDC_FOR_EACH_, n, f)

#define TDC_REMOVE_FIRST_COMMA_(x, ...)  __VA_ARGS__
#define TDC_REMOVE_FIRST_COMMA(...) TDC_REMOVE_FIRST_COMMA_(__VA_ARGS__)


#define TDC_TYPE_NAME(i) Class_##i
#define TDC_TYPE_NAME_(i) ,TDC_TYPE_NAME(i)
#define TDC_TYPE_NAME_N(n) TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_TYPE_NAME_, n))

#define TDC_TEMPLATE_TYPE_NAME(i) ,typename TDC_TYPE_NAME(i)
#define TDC_TEMPLATE_TYPE_NAME_N(n) TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_TEMPLATE_TYPE_NAME, n))

#define TDC_PARAM_NAME(i) param_##i
#define TDC_PARAM_NAME_(i) ,TDC_PARAM_NAME(i)
#define TDC_PARAM_NAME_N(n) TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_PARAM_NAME_, n))

#define TDC_FUNCTION_PARAM(i) , const TDC_TYPE_NAME(i)& TDC_PARAM_NAME(i)
#define TDC_FUNCTION_PARAM_N(n)	TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_FUNCTION_PARAM, n))

#define TDC_CLASS_MEMBER_DEFINE(i) typename RemoveRefrence<TDC_TYPE_NAME(i)>::TYPE TDC_PARAM_NAME(i);
#define TDC_CLASS_MEMBER_DEFINE_N(n) TDC_FOR_EACH_N(TDC_CLASS_MEMBER_DEFINE, n)

#define TDC_CONSTRUCT_INIT_PARAM(i) ,param_##i(param_##i)
#define TDC_CONSTRUCT_INIT_PARAM_N(n) TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_CONSTRUCT_INIT_PARAM, n))

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlocal-type-template-args"
#endif

struct ThreadCallManager{
	template <typename T>
	struct RemoveRefrence
	{
		typedef T TYPE;
	};

	template <typename T>
	struct RemoveRefrence<T&>
	{
		typedef T TYPE;
	};

	struct ThreadCall
	{
		virtual void execute()=0;
		virtual ~ThreadCall(){}
	};

	struct OnCreate
	{
		virtual int64_t onCreateThreadCall(ThreadCallManager::ThreadCall*)=0;
		virtual ~OnCreate(){};
	};

	template<typename OWNER>
	struct OnCreateT: OnCreate
	{
		typedef int64_t (OWNER::*PFUN)(ThreadCallManager::ThreadCall*, const char*, int32_t);
		OnCreateT(OWNER* owner, PFUN pfnOncreate, const char* file, int32_t line):m_pOwner(owner), m_pfnOnCreate(pfnOncreate), m_szFile(file), m_nLine(line){}
		virtual int64_t onCreateThreadCall(ThreadCallManager::ThreadCall* threadCall)
		{
			return (m_pOwner->*m_pfnOnCreate)(threadCall, m_szFile, m_nLine);
		}
		OWNER* const m_pOwner;
		const PFUN m_pfnOnCreate;
        const char* m_szFile;
        const int32_t m_nLine;
	};

	// 0 个参数
	template<typename C, typename RET>
	struct  Functor_0
	{
		typedef RET (C::*P_MF_TYPE)();

		C* m_pInstance;
		P_MF_TYPE m_pMf;
		OnCreate *m_pOnCreate;
		template<typename OWNER>
		Functor_0(C* pInstance, P_MF_TYPE pMf, const char* file, int32_t line, OWNER* owner, typename OnCreateT<OWNER>::PFUN pfnOncreate): m_pInstance(pInstance), m_pMf(pMf), m_pOnCreate(new OnCreateT<OWNER>(owner, pfnOncreate, file, line)){}

		int64_t operator()()
		{
			struct ThreadCall: ThreadCallManager::ThreadCall
			{
				C* m_pInstance;
				P_MF_TYPE m_pMf;

				 ThreadCall(C* pInstance, P_MF_TYPE pMf) : m_pInstance(pInstance), m_pMf(pMf) {}

				 //此函数在其他线程执行
				 void execute(){
				   (m_pInstance->*m_pMf)();
				 }
			};
			if (NULL != m_pOnCreate)
			{
				int64_t ret = m_pOnCreate->onCreateThreadCall(new ThreadCall(m_pInstance, m_pMf));
				delete m_pOnCreate;
				m_pOnCreate = NULL;
				return ret;
			}
			return -1;
		}
	};

#define TDC_Functor_N(n, ...) \
	template<typename C, typename RET, TDC_TEMPLATE_TYPE_NAME_N(n)> \
	struct  Functor_##n\
	{\
		typedef RET (C::*P_MF_TYPE)(TDC_TYPE_NAME_N(n));\
		C* m_pInstance;\
		P_MF_TYPE m_pMf;\
		OnCreate *m_pOnCreate;\
		template<typename OWNER>\
		Functor_##n(C* pInstance, P_MF_TYPE pMf, const char* file, int32_t line, OWNER* owner, typename OnCreateT<OWNER>::PFUN pfnOncreate): m_pInstance(pInstance), m_pMf(pMf), m_pOnCreate(new OnCreateT<OWNER>(owner, pfnOncreate, file, line)){}\
		int64_t operator()(TDC_FUNCTION_PARAM_N(n))\
		{\
			struct ThreadCall: ThreadCallManager::ThreadCall\
			{\
				C* m_pInstance;\
				P_MF_TYPE m_pMf;\
				TDC_CLASS_MEMBER_DEFINE_N(n)\
				ThreadCall(C* pInstance, P_MF_TYPE pMf, TDC_FUNCTION_PARAM_N(n)) : m_pInstance(pInstance), m_pMf(pMf), TDC_CONSTRUCT_INIT_PARAM_N(n){}\
				void execute(){\
					(m_pInstance->*m_pMf)(TDC_PARAM_NAME_N(n));\
				}\
			};\
			if (NULL != m_pOnCreate)\
			{\
				int64_t ret = m_pOnCreate->onCreateThreadCall(new ThreadCall(m_pInstance, m_pMf, TDC_PARAM_NAME_N(n)));\
				delete m_pOnCreate;\
				m_pOnCreate = NULL;\
				return ret;\
			}\
			return -1;\
		}\
	};\

	TDC_DEFINE_ALL(TDC_Functor_N);
};

#define TDC_GET_FUNCTOR_0(FUNCTION_NAME, FN_ON_CREATE) \
template<typename C, typename RET>\
typename ThreadCallManager::Functor_0<C, RET> FUNCTION_NAME(C* pInstance, RET (C::*pMf)(), const char* file, int32_t line)\
{\
	return ThreadCallManager::Functor_0<C, RET>(pInstance, pMf, file, line, this, FN_ON_CREATE);\
}

#define TDC_GET_FUNCTOR_N(n, FUNCTION_NAME, FN_ON_CREATE) \
template<typename C, typename RET, TDC_TEMPLATE_TYPE_NAME_N(n)>\
typename ThreadCallManager::Functor_##n<C, RET, TDC_TYPE_NAME_N(n)> FUNCTION_NAME(C* pInstance, RET (C::*pMf)(TDC_TYPE_NAME_N(n)), const char* file, int32_t line)\
{\
	return ThreadCallManager::Functor_##n<C, RET, TDC_TYPE_NAME_N(n)>(pInstance, pMf, file, line, this, FN_ON_CREATE);\
}

#define TDC_GET_FUNCTOR(FUNCTION_NAME, FN_ON_CREATE) \
		TDC_GET_FUNCTOR_0(FUNCTION_NAME, FN_ON_CREATE) TDC_DEFINE_ALL(TDC_GET_FUNCTOR_N, FUNCTION_NAME, FN_ON_CREATE)

