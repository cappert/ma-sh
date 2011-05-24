/*
 * Copyright (C) 2010 Modern Alchemists OG
 */

package com.modernalchemists.mass.android.config;

public class Config
{
	// Singleton
    private static Config instance = null;
    
	//TODO: your public key here!
    public String base64EncodedPublicKey = YOUR_BASE64_PUBLIC_KEY;
    
    public static Config getInstance()
    {
        if (instance == null)
            instance = new Config();
        
        return instance;
    }
    
    // Classes and Enums
    public enum Managed { MANAGED, UNMANAGED }
    
    public static class ProductDescriptor
    {
    	public String productId;
        public String title;
        public String description;
        public String price;
        public Managed managed;

        public ProductDescriptor(String productid, String title, String description, String price, Managed managed)
        {
            this.productId = productid;
            this.title = title;
            this.description = description;
            this.price = price;
            this.managed = managed;
        }
    }

    // Class
    private Config() {}    

    // items
    public ProductDescriptor[] PRODUCTS = new ProductDescriptor[]
    {
    	// google test items ()
        //new ProductDescriptor("android.test.purchased", "android_test_purchased", "", "$0.99", Managed.UNMANAGED),
        //new ProductDescriptor("android.test.canceled", "android_test_canceled", "", "$0.99", Managed.UNMANAGED),
        //new ProductDescriptor("android.test.refunded", "android_test_refunded", "", "$0.99", Managed.UNMANAGED),
        //new ProductDescriptor("android.test.item_unavailable", "android_test_item_unavailable", "", "$0.99", Managed.UNMANAGED),
        
    	// in app items (need to be defined by the developer)
    	new ProductDescriptor("com.modernalchemists.inappbilling.sword", "MAI - Sword", "Sword, Lorem Ipsum si amet ...", "0.99€", Managed.MANAGED),
    	new ProductDescriptor("com.modernalchemists.inappbilling.drink", "MAI - Drink", "Drink, Lorem Ipsum si amet ...", "0.50€", Managed.UNMANAGED),
    	new ProductDescriptor("com.modernalchemists.inappbilling.glove", "MAI - Glove", "Glove, Lorem Ipsum si amet ...", "0.95€", Managed.MANAGED),
    };
    
    public ProductDescriptor getProductById(String productId)
    {
		int numOfProducts = PRODUCTS.length;
		for( int i=0; i<numOfProducts; ++i )
		{
			if( PRODUCTS[i].productId.equals(productId) )
			{
				return PRODUCTS[i];
			}				
		}
		
		return null;
    }
        
}
