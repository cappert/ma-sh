
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "StoreObserver.h"
#import "maslib.h"


@protocol StoreKitDelegate <NSObject>
@optional
- (void)productPurchased:(NSString *)productId;
@end


@interface StoreManager: NSObject <SKProductsRequestDelegate>
{
	NSMutableArray	*registeredProducts_;
	int				cIndex_;
	
	StoreObserver *storeObserver;
}

- (void) checkHandle: (int) productHandle;

- (NSString*) getProductID: (int) productHandle;

- (void) requestProductDetails: (int) productHandle;

- (void) buyProduct: (int) productHandle;

- (void) failedTransaction: (SKPaymentTransaction *) transaction;

- (void) processTransaction: (NSString*) productID;

- (void) setProductInfoCallback: (ProductInfoCallback) arg;

- (void) setProductBoughtCallback: (ProductBoughtCallback) arg;

- (void) setTransactionFailedCallback: (TransactionFailedCallback) arg;

- (int) registerProduct: (NSString*) productID;

+ (StoreManager*) getSharedInstance;

@end
