/*
 *  maslib.h
 *  Modern Alchemists Store Library
 *
 *  Created by Stein0r on 11/23/10.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */


#ifndef MASLIB_H
#define MASLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		int		handle;
		char	*sId;
		char	*name;
		char	*price;
		char	*description;
	}
	ProductDescriptor_t;


	typedef void	(*ProductInfoCallback)		(ProductDescriptor_t *arg);

	typedef void	(*ProductBoughtCallback)		(ProductDescriptor_t *arg);
	typedef void	(*TransactionFailedCallback)		(ProductDescriptor_t *arg);
	//typedef void	(*ProductBoughtCallback)	(int productHandle);


	int maslib_registerProductByString(const char *arg);

	void maslib_requestProductInfo(int productHandle);

	void maslib_setProductInfoCallback(ProductInfoCallback arg);

	void maslib_buyProduct(int productHandle);

	void maslib_setProductBoughtCallback(ProductBoughtCallback arg);
	
	void maslib_setTransactionFailedCallback(TransactionFailedCallback arg);

#ifdef __cplusplus
}
#endif
	
#endif