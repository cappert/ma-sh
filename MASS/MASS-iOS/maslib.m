/*
 *  maslib.h
 *  Modern Alchemists Store Library
 *
 *  Created by Stein0r on 11/23/10.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */


#import "maslib.h"
#import "Store.h"


void maslib_requestProductInfo(int productHandle)
{
	[[StoreManager getSharedInstance] requestProductDetails: productHandle];
}

void maslib_buyProduct(int productHandle)
{
	[[StoreManager getSharedInstance] buyProduct: productHandle];
}

void maslib_setProductInfoCallback(ProductInfoCallback arg)
{
	[[StoreManager getSharedInstance] setProductInfoCallback: arg];
}

void maslib_setProductBoughtCallback(ProductBoughtCallback arg)
{
	[[StoreManager getSharedInstance] setProductBoughtCallback: arg];
}

void maslib_setTransactionFailedCallback(TransactionFailedCallback arg)
{
	[[StoreManager getSharedInstance] setTransactionFailedCallback: arg];
}

int maslib_registerProductByString(const char *arg)
{
	return [[StoreManager getSharedInstance]
	 registerProduct:[NSString stringWithUTF8String:arg]];
}

