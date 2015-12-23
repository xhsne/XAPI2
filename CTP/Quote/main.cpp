#include "stdafx.h"
#include "../../include/ApiHeader.h"
#include "../../include/QueueEnum.h"

#include "MdUserApi.h"

#include "Include.h"

inline CMdUserApi* GetApi(void* pApi)
{
	return static_cast<CMdUserApi*>(pApi);
}

void* __stdcall XRequest(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	RequestType rt = (RequestType)type;
	switch (rt)
	{
	case RequestType_GetApiType:
		return (void*)(ApiType::ApiType_MarketData | ApiType::ApiType_QuoteRequest);
	case RequestType_GetApiVersion:
		return (void*)API_VERSION;
	case RequestType_GetApiName:
		return (void*)API_NAME;
	case RequestType_Create:
		return new CMdUserApi();
	default:
		break;
	}

	if (pApi1 == nullptr)
	{
		return nullptr;
	}

	CMdUserApi* pApi = GetApi(pApi1);

	switch (rt)
	{
	case RequestType_Release:
		delete pApi;
		return 0;
	case RequestType_Register:
		pApi->Register(ptr1,ptr2);
		break;
	case RequestType_Config:
		return (void*)pApi->Config((ConfigInfoField*)ptr1);
	case RequestType_Connect:
		pApi->Connect((const char*)ptr3, (ServerInfoField*)ptr1, (UserInfoField*)ptr2,size2);
		break;
	case RequestType_Disconnect:
		pApi->Disconnect();
		break;
	case RequestType_Subscribe:
		pApi->Subscribe((const char*)ptr1, (const char*)ptr2);
		break;
	case RequestType_Unsubscribe:
		pApi->Unsubscribe((const char*)ptr1, (const char*)ptr2);
		break;
	case RequestType_SubscribeQuote:
		pApi->SubscribeQuote((const char*)ptr1, (const char*)ptr2);
		break;
	case RequestType_UnsubscribeQuote:
		pApi->UnsubscribeQuote((const char*)ptr1, (const char*)ptr2);
		break;
	default:
		break;
	}

	return pApi1;
}
