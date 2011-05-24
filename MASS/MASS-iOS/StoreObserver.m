
#import "StoreObserver.h"
#import "Store.h"


@implementation StoreObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
	for (SKPaymentTransaction *transaction in transactions)
	{
		switch (transaction.transactionState)
		{
			case SKPaymentTransactionStatePurchased:
				
                [self completeTransaction:transaction];
				
                break;
				
            case SKPaymentTransactionStateFailed:
				
                [self failedTransaction:transaction];
				
                break;
				
            case SKPaymentTransactionStateRestored:
				
                [self restoreTransaction:transaction];
				
            default:
				
                break;
		}			
	}
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{	
	//NSString* errorStr = [transaction.error localizedFailureReason];
	//NSLog(@"Errrror: %@", *errorStr );

	
	
	
	[[StoreManager getSharedInstance] failedTransaction:transaction]; 
	/*
    if (transaction.error.code != SKErrorPaymentCancelled)		
    {		
        UIAlertView *alert = [
							  [UIAlertView alloc]
							  initWithTitle:		@"Error"
							  message:				@"Transaction failed."
							  delegate:				self
							  cancelButtonTitle:	@"OK"
							  otherButtonTitles:	nil];
		
		[alert show];
		
		[alert release];		
    
	 }	*/
	
	
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];	
}

- (void) completeTransaction: (SKPaymentTransaction *)transaction
{		
    [[StoreManager getSharedInstance] processTransaction: transaction.payment.productIdentifier];	
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];	
}

- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{	
    [[StoreManager getSharedInstance] processTransaction: transaction.originalTransaction.payment.productIdentifier];	
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];	
}

@end
