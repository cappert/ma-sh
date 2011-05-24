
#import "Store.h"


static StoreManager				*storeManager			= nil;
static ProductInfoCallback		productInfoCallback		= nil;
static ProductBoughtCallback	productBoughtCallback	= nil;
static TransactionFailedCallback	transactionFailedCallback	= nil;

@implementation StoreManager

- (void) checkHandle: (int) productHandle
{
	if (productHandle == 0)
	{
		[NSException raise:@"Invalid Handle" format:@"The specified handle is ZERO."];
	}
	
	if (productHandle < 0)
	{
		[NSException raise:@"Invalid Handle" format:@"The specified handle is NEGATIVE."];
	}
	
	if (productHandle > cIndex_)
	{
		[NSException raise:@"Invalid Handle" format:@"The specified handle is UNKNOWN."];
	}
}

- (NSString*) getProductID: (int) productHandle
{
	[self checkHandle: productHandle];
	
	return [registeredProducts_ objectAtIndex:productHandle];
}

- (void) dealloc
{
	storeManager = nil;
	
	[storeObserver release];
	[super dealloc];
}

+ (StoreManager*) getSharedInstance
{
    @synchronized(self)
    {
        if (storeManager == nil)
		{
			storeManager = [[StoreManager alloc] init];
		}
    }
    return storeManager;
}

+ (id)allocWithZone:(NSZone *)zone {
    @synchronized(self) {
        if (storeManager == nil) {
            storeManager = [super allocWithZone:zone];
            return storeManager;  // assignment and return on first allocation
        }
    }
    return nil; // on subsequent allocation attempts return nil
}

- (id) copyWithZone:(NSZone *)zone
{
    return self;
}

- (id) retain {
    return self;
}

/*
 - (NSUInteger) retainCount {
 {
 return UINT_MAX;  // denotes an object that cannot be released
 }
 */

- (void)release
{
    //do nothing
}

- (id)autorelease
{
    return self;
}

- (id) init
{
	self = [super init];
	
	if (self)
	{
		cIndex_ = 0;
		registeredProducts_ = [[NSMutableArray alloc] init];
		[registeredProducts_ addObject:@""];	//there is no zero handle
		
		//NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
		
		storeObserver = [[StoreObserver alloc] init];
		[[SKPaymentQueue defaultQueue] addTransactionObserver:storeObserver];
	}
	
	return self;
}

- (void) setProductInfoCallback: (ProductInfoCallback) arg
{
	productInfoCallback = arg;
}

- (void) setProductBoughtCallback: (ProductBoughtCallback) arg
{
	productBoughtCallback = arg;
}

- (void) setTransactionFailedCallback: (TransactionFailedCallback) arg
{
	transactionFailedCallback = arg;
}

- (int) registerProduct: (NSString*) productID
{
	int tIndex = [registeredProducts_ indexOfObject:productID];
	if (tIndex != NSNotFound) return tIndex;	//the product is already registered
	
	++cIndex_;
	[registeredProducts_ addObject:productID];
	
	return cIndex_;
}

- (void) requestProductDetails: (int) productHandle
{
	//NSLog(@"requestProductDetails: productHandle is %i .", productHandle);
	
	NSString *product = [self getProductID:productHandle];
	
	SKProductsRequest *request = [
		[SKProductsRequest alloc] initWithProductIdentifiers: [
			NSSet setWithObject: product]];
	
	request.delegate = self;
	
	//NSLog(@"requesting %@ . . .", product);
	[request start];
}

- (void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	NSLog(@"called back . . .");
	
	NSMutableArray *purchasableObjects;
	purchasableObjects = [[NSMutableArray alloc] init];
	
	[purchasableObjects addObjectsFromArray:response.products];
	
	int count = [purchasableObjects count];
	
	// populate UI
	int i = 0;				//C99 not supportet ... ?
	for(; i < count; ++i)
	{
		SKProduct *product = [purchasableObjects objectAtIndex:i];
		NSString *title = [product localizedTitle];
		NSString *sId = [product productIdentifier];
		NSString *description = [product localizedDescription];
	
		
		NSNumberFormatter *numberFormatter = [[[NSNumberFormatter alloc] init] autorelease];
		[numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
		[numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
		[numberFormatter setLocale:product.priceLocale];
		NSString *formattedString =  [numberFormatter stringFromNumber:product.price];
		
		if (productInfoCallback)
		{
			//ProductDescriptor_t productDesc = {0, [sId UTF8String], [title UTF8String], [[product price] doubleValue]};
			ProductDescriptor_t productDesc;
			productDesc.handle = 0;
			productDesc.sId = [sId UTF8String];
			productDesc.name = [title UTF8String];
			productDesc.price = [formattedString	UTF8String];
			productDesc.description = [description UTF8String];
			
			productInfoCallback(&productDesc);
		}
	}
	
	[request autorelease];
	[purchasableObjects autorelease];
}


- (void) buyProduct: (int) productHandle
{	
	if ([SKPaymentQueue canMakePayments])
	{
		NSString *product = [self getProductID:productHandle];
		
		//NSLog(@"buying %@ . . .", product);
		SKPayment *payment = [SKPayment paymentWithProductIdentifier:product];
		[[SKPaymentQueue defaultQueue] addPayment:payment];
	}
	else
	{
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Store" message:@"You are not authorized to purchase from AppStore"
													   delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
		[alert show];
		[alert release];
	}
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{
	//NSLog(@"Failed Transe");
	
	SKPayment *payment = transaction.payment;
	NSString *sId = payment.productIdentifier;
	
	if (transactionFailedCallback)
	{
		ProductDescriptor_t productDesc;
		productDesc.handle = -1;
		productDesc.sId = [sId UTF8String];
		productDesc.name = "UNASSIGNED";
		productDesc.price = "UNASSIGNED";
		productDesc.description = "UNASSIGNED";
		
		transactionFailedCallback(&productDesc);
	}	
	
	
//	if (transaction.error.code != SKErrorPaymentCancelled)		
  //  {
//		NSString *messageToBeShown = [NSString stringWithFormat:@"Reason: %@, You can try: %@", [transaction.error localizedFailureReason], [transaction.error localizedRecoverySuggestion]];
//		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Unable to complete your purchase" message:messageToBeShown
//													   delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
//		[alert show];
//		[alert release];
//	}
	
	NSLog(@"Failed transaction: %@",transaction.transactionIdentifier);
	//if transaction is not cancelled by user - parse and log error
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
		if(transaction.error.code == SKErrorUnknown) {
			NSLog(@"Unknown Error (%d), product: %@", (int)transaction.error.code, transaction.payment.productIdentifier);
			UIAlertView *failureAlert = [[UIAlertView alloc] initWithTitle :@"In-App-Purchase Error:"
																	message: @"There was an error purchasing this item please try again."
																  delegate : self cancelButtonTitle:@"OK"otherButtonTitles:nil];
			[failureAlert show];
			[failureAlert release];
		}
		
		else if(transaction.error.code == SKErrorClientInvalid) {
			NSLog(@"Client invalid (%d), product: %@", (int)transaction.error.code, transaction.payment.productIdentifier);
			UIAlertView *failureAlert = [[UIAlertView alloc] initWithTitle :@"In-App-Purchase Error:"
																	message: @"There was an error purchasing this item please try again."
																  delegate : self cancelButtonTitle:@"OK"otherButtonTitles:nil];
			[failureAlert show];
			[failureAlert release];
		}
		
		else if(transaction.error.code == SKErrorPaymentInvalid) {
			NSLog(@"Payment invalid (%d), product: %@", (int)transaction.error.code, transaction.payment.productIdentifier);
			UIAlertView *failureAlert = [[UIAlertView alloc] initWithTitle :@"In-App-Purchase Error:"
																	message: @"There was an error purchasing this item please try again."
																  delegate : self cancelButtonTitle:@"OK"otherButtonTitles:nil];
			[failureAlert show];
			[failureAlert release];
		}
		
		else if(transaction.error.code == SKErrorPaymentNotAllowed) {
			NSLog(@"Payment not allowed (%d), product: %@", (int)transaction.error.code, transaction.payment.productIdentifier);
			UIAlertView *failureAlert = [[UIAlertView alloc] initWithTitle :@"In-App-Purchase Error:"
																	message: @"There was an error purchasing this item please try again."
																  delegate : self cancelButtonTitle:@"OK"otherButtonTitles:nil];
			[failureAlert show];
			[failureAlert release];
		}
		
		else {
			NSString *messageToBeShown = [NSString stringWithFormat:@"Reason: %@, You can try: %@", [transaction.error localizedFailureReason], [transaction.error localizedRecoverySuggestion]];
			UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Unable to complete your purchase" message:messageToBeShown
														   delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
			[alert show];
			[alert release];
		}

    }
	
}

-(void) processTransaction: (NSString*) productID
{	
	int index = [registeredProducts_ indexOfObject:productID];
	
	//NSLog(@"process transaction: %@", productID);
	
	//NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	if(index != NSNotFound)
	{
		if (productBoughtCallback)
		{
			//productBoughtCallback(index);
			
			//TODO: fix this ugly hack!!!!
			ProductDescriptor_t productDesc;
			productDesc.handle = index;
			productDesc.sId = [productID UTF8String];
			productDesc.name = "UNASSIGNED";
			productDesc.price = "UNASSIGNED";
			productDesc.description = "UNASSIGNED";
			
			productBoughtCallback(&productDesc);

			
			
		}
	}
}

@end