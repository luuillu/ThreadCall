#pragma once
#include <iostream>
//macro prefix TDC_
/***
 * 这个类主要目的是方便成员函数跨线程调用，将成员函数调用包装成ThreadCall对象，发给消息线程，以供调用。支持Send和Post两种线程消息机制。
 * 所提供的接口是一个宏函数TDC_GET_FUNCTOR(FUNCTION_NAME, FN_ON_CREATE, Trait)。
 * 使用方法：在一个类（通常是消息线程类）中用宏 TDC_GET_FUNCTOR 声明一组成员函数。这组成员函数的签名是：
 * Functor_n FUNCTION_NAME(C* pInstance, C::*pMf, const char* file, int32_t line, void* pRet=NULL)
 * FUNCTION_NAME 为成员函数名， 可以随便起个名字，比如PostCall。
 * pInstance 只想一个类的对象， pMf 指向这个对象中的某个成员函数。
 * file，line 这两个参数用于调试。
 * 这个函数的目的是把 (pInstance->*pMf)(param1, ..., paramn) 这样的调用包装成ThreadCall对象。然而这个函数并没有把调用pMf需要的参数传进来，
 * 这项工作是由这个函数的返回值Functor_n 完成的。
 *
 * Functor_n 是一个C++ Functor 因此可以这样调用Functor_n(param1, ..., paramn) ,Functor_n的参数类型和个数是根据上一步操作中的参数pMf推导出来的。
 * 所以Functor_n 的作用是接受参数，以供pMf 调用。由于Functor_n拥有调用 (pInstance->*pMf)(param1, ..., paramn) 的全部数据，所以它可以生成ThreadCall对象。
 * ThreadCall有一个成员函数：void execute(void* pRet = NULL)=0; 调用这个execute函数就会执行(pInstance->*pMf)(param1, ..., paramn)。
 * 参数pRet 用于接收返回值， 只对Send有效， Post时会忽略这个参数；传递null 表示不想接收返回值，如果不传NULL，但函数的返回类型为void，那么也会忽略这个参数。
 * Functor_n 生成的ThreadCall对象需要传给外面处理，所用的方式就是这个宏的第二个参数FN_ON_CREATE，这个成员函数需要按如下的签名实现：
 *
 * int64_t (OWNER::*OnCreateThreadCall)(ThreadCallManager::ThreadCall* pThreadCall, const char* file , int32_t line , void* pRet)
 * 这个签名有四个参数：1. pThreadCall 就是是Functor_n产生的对象的指针，Functor_n 只负责生成这个指针，并不释放，所以OnCreateThreadCall使用完pThreadCall 对象后需要释放内存。
 * 	参数 2和3 用于调试， 参数4 的目的是接收返回值，只对Send有效， 调用pThreadCall->execute(pRet) 时直接传入即可。OnCreateThreadCall 需要返回一个int64_t 类型的msgId。
 *
 *这个宏的最后一个参数Trait,有两个可取值：ThreadCallManager::PostTrait 和ThreadCallManager::SendTrait 分别代表Post方式和Send方式，这两种方式的主要区别是:
 *1. Post 是异步执行的，所以通过Functor_n 的到的参数在执行时，内存可能已经失效了，为了避免内存错误，对于引用参数类型，Functor_n 实际上会把参数的值复制一份。而Send是同步执行的，在传引用参数时直接按引用传递。
 *2. Send方式可以获取执行后的返回值，Post不支持获取返回值。
 *
 * ***/

//最大支持31 个参数的成员函数
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

#define TDC_FUNCTION_PARAM(i) , typename AddRefrence<TDC_TYPE_NAME(i)>::TYPE TDC_PARAM_NAME(i)
#define TDC_FUNCTION_PARAM_N(n)	TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_FUNCTION_PARAM, n))

#define TDC_CLASS_MEMBER_DEFINE(i) typename Trait<TDC_TYPE_NAME(i)>::MEMBER_TYPE TDC_PARAM_NAME(i);
#define TDC_CLASS_MEMBER_DEFINE_N(n) TDC_FOR_EACH_N(TDC_CLASS_MEMBER_DEFINE, n)

#define TDC_CONSTRUCT_INIT_PARAM(i) ,param_##i(param_##i)
#define TDC_CONSTRUCT_INIT_PARAM_N(n) TDC_REMOVE_FIRST_COMMA(TDC_FOR_EACH_N(TDC_CONSTRUCT_INIT_PARAM, n))

struct ThreadCallManager{
	template <typename T>
	struct PostTrait
	{
		template <typename U>
		struct RemoveRefrence
		{
			typedef U TYPE;
		};

		template <typename U>
		struct RemoveRefrence<U&>
		{
			typedef U TYPE;
		};
		typedef typename RemoveRefrence<T>::TYPE MEMBER_TYPE;
	};

	template <typename T>
	struct SendTrait
	{
		typedef T MEMBER_TYPE;
	};

	template <typename T>
	struct AddRefrence
	{
		typedef const T& TYPE;
	};

	template <typename T>
	struct AddRefrence<T&>
	{
		typedef T& TYPE;
	};

	struct ThreadCall
	{
		virtual void execute(void* pRet = NULL)=0;

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
		typedef int64_t (OWNER::*PFUN)(ThreadCallManager::ThreadCall*, const char*, int32_t, void* pRet);
		OnCreateT(OWNER* owner, PFUN pfnOncreate, const char* file, int32_t line, void* pRet):m_pOwner(owner), m_pfnOnCreate(pfnOncreate), m_szFile(file), m_nLine(line), m_pRet(pRet){}
		virtual int64_t onCreateThreadCall(ThreadCallManager::ThreadCall* threadCall)
		{
			return (m_pOwner->*m_pfnOnCreate)(threadCall, m_szFile, m_nLine, m_pRet);
		}
		OWNER* const m_pOwner;
		const PFUN m_pfnOnCreate;
        const char* m_szFile;
        const int32_t m_nLine;
        void* m_pRet;
	};

	// 0 个参数
	template<template<typename> class Trait, typename C, typename RET>
	struct  Functor_0
	{
		typedef RET (C::*P_MF_TYPE)();
		struct ThreadCall: ThreadCallManager::ThreadCall
		{
			 ThreadCall(C* pInstance, P_MF_TYPE pMf) : m_pInstance(pInstance), m_pMf(pMf) {}

			 //此函数在其他线程执行
			 void execute(void* pRet)
			 {
				 doExecute((RET*)pRet);
			 }

			 template<typename T>
			 void doExecute(T* pRet)
			 {
				 if (NULL == pRet)
				 {
					 (m_pInstance->*m_pMf)();
				 }
				 else
				 {
					 *pRet = (m_pInstance->*m_pMf)();
				 }
			 }

			 void doExecute(void* pRet)
			 {
				 (m_pInstance->*m_pMf)();
			 }

			 C* m_pInstance;
			 P_MF_TYPE m_pMf;
		};

		template<typename OWNER>
		Functor_0(C* pInstance, P_MF_TYPE pMf, const char* file, int32_t line, void* pRet, OWNER* owner, typename OnCreateT<OWNER>::PFUN pfnOncreate): m_pInstance(pInstance), m_pMf(pMf), m_pOnCreate(new OnCreateT<OWNER>(owner, pfnOncreate, file, line, pRet)){}

		int64_t operator()()
		{

			if (NULL != m_pOnCreate)
			{
				int64_t ret = m_pOnCreate->onCreateThreadCall(new ThreadCall(m_pInstance, m_pMf));
				delete m_pOnCreate;
				m_pOnCreate = NULL;
				return ret;
			}
			return -1;
		}

		C* m_pInstance;
		P_MF_TYPE m_pMf;
		OnCreate *m_pOnCreate;
	};

#define TDC_Functor_N(n, ...) \
	template<template<typename> class Trait, typename C, typename RET, TDC_TEMPLATE_TYPE_NAME_N(n)> \
	struct  Functor_##n\
	{\
		typedef RET (C::*P_MF_TYPE)(TDC_TYPE_NAME_N(n));\
		struct ThreadCall: ThreadCallManager::ThreadCall\
		{\
			ThreadCall(C* pInstance, P_MF_TYPE pMf, TDC_FUNCTION_PARAM_N(n)) : m_pInstance(pInstance), m_pMf(pMf), TDC_CONSTRUCT_INIT_PARAM_N(n){}\
			 void execute(void* pRet)\
			 {\
				doExecute((RET*)pRet);\
			 }\
			 template<typename T>\
			 void doExecute(T* pRet)\
			 {\
				 if (NULL == pRet)\
				 {\
					 (m_pInstance->*m_pMf)(TDC_PARAM_NAME_N(n));\
				 }\
				 else\
				 {\
					 *pRet = (m_pInstance->*m_pMf)(TDC_PARAM_NAME_N(n));\
				 }\
			 }\
			 void doExecute(void* pRet)\
			 {\
				 (m_pInstance->*m_pMf)(TDC_PARAM_NAME_N(n));\
			 }\
			 C* m_pInstance;\
			 P_MF_TYPE m_pMf;\
			 TDC_CLASS_MEMBER_DEFINE_N(n)\
		};\
		template<typename OWNER>\
		Functor_##n(C* pInstance, P_MF_TYPE pMf, const char* file, int32_t line, void* pRet, OWNER* owner, typename OnCreateT<OWNER>::PFUN pfnOncreate): m_pInstance(pInstance), m_pMf(pMf), m_pOnCreate(new OnCreateT<OWNER>(owner, pfnOncreate, file, line, pRet)){}\
		int64_t operator()(TDC_FUNCTION_PARAM_N(n))\
		{\
			if (NULL != m_pOnCreate)\
			{\
				int64_t ret = m_pOnCreate->onCreateThreadCall(new ThreadCall(m_pInstance, m_pMf, TDC_PARAM_NAME_N(n)));\
				delete m_pOnCreate;\
				m_pOnCreate = NULL;\
				return ret;\
			}\
			return -1;\
		}\
		C* m_pInstance;\
		P_MF_TYPE m_pMf;\
		OnCreate *m_pOnCreate;\
	};\

	TDC_DEFINE_ALL(TDC_Functor_N);
};

#define TDC_GET_FUNCTOR_0(FUNCTION_NAME, FN_ON_CREATE, Trait) \
template<typename C, typename RET>\
typename ThreadCallManager::Functor_0<Trait, C, RET> FUNCTION_NAME(C* pInstance, RET (C::*pMf)(), const char* file, int32_t line, void* pRet=NULL)\
{\
	return ThreadCallManager::Functor_0<Trait, C, RET>(pInstance, pMf, file, line, pRet, this, FN_ON_CREATE);\
}

#define TDC_GET_FUNCTOR_N(n, FUNCTION_NAME, FN_ON_CREATE, Trait) \
template<typename C, typename RET, TDC_TEMPLATE_TYPE_NAME_N(n)>\
typename ThreadCallManager::Functor_##n<Trait, C, RET, TDC_TYPE_NAME_N(n)> FUNCTION_NAME(C* pInstance, RET (C::*pMf)(TDC_TYPE_NAME_N(n)), const char* file, int32_t line, void* pRet=NULL)\
{\
	return ThreadCallManager::Functor_##n<Trait, C, RET, TDC_TYPE_NAME_N(n)>(pInstance, pMf, file, line, pRet, this, FN_ON_CREATE);\
}

#define TDC_GET_FUNCTOR(FUNCTION_NAME, FN_ON_CREATE, Trait) \
		TDC_GET_FUNCTOR_0(FUNCTION_NAME, FN_ON_CREATE, Trait) TDC_DEFINE_ALL(TDC_GET_FUNCTOR_N, FUNCTION_NAME, FN_ON_CREATE, Trait)




