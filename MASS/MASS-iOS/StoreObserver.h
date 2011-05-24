
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>


@interface StoreObserver : NSObject<SKPaymentTransactionObserver> {

	
}
	
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void) failedTransaction: (SKPaymentTransaction *)transaction;
- (void) completeTransaction: (SKPaymentTransaction *)transaction;
- (void) restoreTransaction: (SKPaymentTransaction *)transaction;

@end
