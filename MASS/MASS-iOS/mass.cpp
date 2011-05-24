/*
 *  mass.h
 *  Modern Alchemists Store for Shiva
 *
 *  Created by Stein0r on 11/23/10.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */


#include "mass.h"
#include "maslib.h"
#include "S3DXAIVariable.h"
#include "S3DClient_Wrapper.h"


void onRequestProductHandle(unsigned char argumentCount, const void *arguments, void *userData )
{
    if ( arguments && ( argumentCount == 1 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			//ObjectiveC_LogMessage(variables[0].GetStringValue());
        }
    }
}

void onRequestProductInfo(unsigned char argumentCount, const void *arguments, void *userData )
{
    if ( arguments && ( argumentCount == 1 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			//ObjectiveC_LogMessage(variables[0].GetStringValue());
			int handle = maslib_registerProductByString(variables[0].GetStringValue());
			maslib_requestProductInfo(handle);
        }
    }
}

void onRequestProductPurchase(unsigned char argumentCount, const void *arguments, void *userData)
{
    if ( arguments && ( argumentCount == 1 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			//ObjectiveC_LogMessage(variables[0].GetStringValue());
			
			S3DX::AIVariable variable;
			
			int handle = maslib_registerProductByString(variables[0].GetStringValue());
			variable.SetNumberValue(handle);
			
			//ObjectiveC_LogMessage("buying item with handle:");
			//ObjectiveC_LogMessage(variable.GetStringValue());
			
			maslib_buyProduct(handle);
			//S3DClient_SendEventToCurrentUser("MASS", "onDeliverProductHandle", 1, &variable);
        }
    }
}

void productInfoCallback(ProductDescriptor_t *arg)
{
	//ObjectiveC_LogMessage("productInfoCallback");
	S3DX::AIVariable variables[5];
	
	// nHandle, sId, sName, nPrice 
	variables[0].SetNumberValue(arg->handle);
	variables[1].SetStringValue(arg->sId);
	variables[2].SetStringValue(arg->name);
	variables[3].SetStringValue(arg->price);
	variables[4].SetStringValue(arg->description);
	
	S3DClient_SendEventToCurrentUser("MASS", "onDeliverProductInfo", 5, &variables);
}

void productBoughtCallback(ProductDescriptor_t *arg)
//int productHandle
{
	/*ObjectiveC_LogMessage("productBoughtCallback");
	S3DX::AIVariable variable;
	
	//don't do this at home, especially not with a c-style cast . . .
	variable.SetHandleValue((void*) productHandle);
	
	S3DClient_SendEventToCurrentUser("MASS", "onPerformProductPurchase", 1, &variable);
	 */
	//ObjectiveC_LogMessage("productBoughtCallback");
	S3DX::AIVariable variables[5];
	
	// nHandle, sId, sName, nPrice 
	variables[0].SetNumberValue(arg->handle);
	variables[1].SetStringValue(arg->sId);
	variables[2].SetStringValue(arg->name);
	variables[3].SetStringValue(arg->price);
	variables[4].SetStringValue(arg->description);
	
	S3DClient_SendEventToCurrentUser("MASS", "onPerformProductPurchase", 5, &variables);	
	
}

void transactionFailedCallback(ProductDescriptor_t *arg)
{
	//ObjectiveC_LogMessage("transactionFailedCallback");
	S3DX::AIVariable variables[5];
	
	// nHandle, sId, sName, nPrice 
	variables[0].SetNumberValue(arg->handle);
	variables[1].SetStringValue(arg->sId);
	variables[2].SetStringValue(arg->name);
	variables[3].SetStringValue(arg->price);
	variables[4].SetStringValue(arg->description);
	
	S3DClient_SendEventToCurrentUser("MASS", "onTransactionFailed", 5, &variables);	
	
}

void mass_registerCallbacks()
{
	ObjectiveC_LogMessage("MASS REGISTER CALLBACKS");
	S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductHandle",		onRequestProductHandle,		NULL);
	S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductInfo",		onRequestProductInfo,		NULL);
	S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductPurchase",	onRequestProductPurchase,	NULL);
	
	maslib_setProductInfoCallback(productInfoCallback);
	maslib_setProductBoughtCallback(productBoughtCallback);
	maslib_setTransactionFailedCallback(transactionFailedCallback);
	
}
