/*
 * Copyright (C) 2010 Modern Alchemists OG
 */

package com.modernalchemists.mass.android;

import java.util.Locale;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;

import com.modernalchemists.mass.android.BillingService.RestoreTransactions;
import com.modernalchemists.mass.android.Consts.ResponseCode;
import com.modernalchemists.mass.android.config.Config;
import com.modernalchemists.mass.android.config.Config.ProductDescriptor;

import com.modernalchemists.aeonracerlite.R;

/*
 * Store class, implemented as Singleton
 * 
 * Handles all Android In-App-Billing related things.
 */
public class Store
{
	// request type
	public static final String REQUEST_TYPE_BUY_PRODUCT = "buy_product";
	
	// Logging
	public static final String LOG_TAG = "MASS-JAVA";
	
	// singleton instance storage
    private static Store instance = null;
    
    // dialogues
    public static final int DIALOG_CANNOT_CONNECT_ID = 1;
    public static final int DIALOG_BILLING_NOT_SUPPORTED_ID = 2;
    
    // vars
    //private Context context;
    private Activity activity; //Test by and for Zog.
    private String mPayloadContents = null;
    private String mReceivedData = null;
    
    public void setReceivedData(String signedData)
    {
    	if(Consts.DEBUG)
    	{
    		Log.d("Blubbbb", "signedData in setRecievedData: " + signedData);
    	}
		this.mReceivedData = signedData;
	}
    
    

    
    public String getReceivedData()
    {
    	if(Consts.DEBUG)
    	{
    		Log.d("Blubbbb", "signedData in getRecievedData: " + this.mReceivedData);
    	}
    	return this.mReceivedData;
    }

	// flag whether or not the "already purchased items" action has been performed
    private static final String DATA_INITIALIZED = "data_initialized";

    // services, listeners, handlers
    private BillingService mBillingService;    
    private MassPurchaseObserver mMassPurchaseObserver;
    private Handler mHandler;
    
    // current product
    private ProductDescriptor cProduct;
    
    private Store() {}

    public static Store getInstance()
    {
        if (instance == null)
            instance = new Store();
        
        return instance;
    }
    
    // -- MASS API Methods - REQUESTS ----------------------------------------------
	public static void requestProductInfo(String productId)
	{
		// log
		Store.getInstance().log("requestProductInfo("+productId+")");
        
		//Store.getInstance().mReceivedData = null;
		
		// do request (sync)
		Store.getInstance().onProductInfoReceived( Config.getInstance().getProductById(productId) );
	}
	
	public static void buyProduct(String productId)
	{
		// log
		Store.getInstance().log("buyProduct("+productId+")");
		
		Store.getInstance().mReceivedData = null;
		Store.getInstance().mPayloadContents = Store.REQUEST_TYPE_BUY_PRODUCT;
		
		Store.getInstance().cProduct = Config.getInstance().getProductById(productId);
		
		if (!Store.getInstance().mBillingService.requestPurchase(productId, Store.getInstance().mPayloadContents))
		{
			Store.getInstance().showDialog(DIALOG_BILLING_NOT_SUPPORTED_ID);
        }
	}
	
	// -- MASS API Methods - RESPONSES ----------------------------------------------
	
	private void onProductInfoReceived( Config.ProductDescriptor product )
	{
		// log
		log("onProductInfoReceived("+product+")");
		
		try{
			if(product != null)
			{
				// log
				log("Requested Infos result: " + product.title + " / " + product.productId);
				
				// native call
				productInfoCallback(product.productId, product.title, product.description, product.price);
			}
			else
			{
				// log
				log("Requested Infos result: '' / ''");
				
				// native call
				productInfoCallback("", "", "", "");
			}
		} catch(Error e)
		{
			log("Error while calling native function 'onProductInfoCallback': " + e.getMessage());
		}
	}
	
	/**
	 * This function is called whenever a buy request has been sent successfully to the server.
	 * You may use this to unlock items before google actually confirms the purchase (which may take days).
	 */
	public void onPurchaseSent()
	{
		// log
		log("onPurchaseSent(" + ((cProduct != null) ? cProduct.productId : null) + ")");
		if(cProduct == null) log(" Product is null, it probably is the result of a restore transaction request.");
		
		// todo
		log("TODO: onPurchaseSent() ends in Java context: java > c > ShiVa implementation is still missing.");
	}
	
	public void onProductBought()
	{
		// log
		log("onProductBought(" + ((cProduct != null) ? cProduct.productId : null) + ")");
		if(cProduct == null) log(" Product is null, it probably is the result of a restore transaction request.");
		
		// native call
		try{
			if(cProduct != null) {
				productBoughtCallback(cProduct.productId, cProduct.title, cProduct.description, cProduct.price);
			} else {
				// productBoughtCallback("", "", "", ""); // request transaction response
			}
		} catch(Error e)
		{
			log("Error while calling native function 'onProductBoughtCallback': " + e.getMessage());
		}
	}
	
	public void onProductBought(String productId, String title, String description, String price)
	{
		// log
		log("onProductBought("+productId+","+title+","+description+","+price+") - called by onRestoreTransactionResponse()");
		
		productBoughtCallback(productId, title, description, price);
	}
	
	public void onProductRefunded()
	{
		// log
		log("onProductRefunded");
		
		// native call
		try{
			if(cProduct != null) {
				productRefundedCallback(cProduct.productId, cProduct.title, cProduct.description, cProduct.price);
			} else {
				productRefundedCallback("", "", "", "");
			}
		} catch(Error e)
		{
			log("Error while calling native function 'onProductRefundedCallback': " + e.getMessage());
		}
	}
	
	public void onProductRefunded(String productId, String title, String description, String price)
	{
		// log
		log("onProductRefunded("+productId+","+title+","+description+","+price+") - called by onRestoreTransactionResponse()");
		
		productRefundedCallback(productId, title, description, price);
	}
	
	public void onTransactionFailed()
	{
		// log
		log("onTransactionFailed()");
		
		// native call
		try{
			if(cProduct != null) {
				transactionFailedCallback(cProduct.productId, cProduct.title, cProduct.description, cProduct.price);
			} else {
				transactionFailedCallback("", "", "", "");
			}	
		} catch(Error e)
		{
			log("Error while calling native function 'onTransactionFailedCallback': " + e.getMessage());
		}
		
		this.cProduct = null;
	}
	
	// -- native functions
	public native void productInfoCallback( String id, String title, String description, String price );
	public native void productBoughtCallback( String id, String title, String description, String price );
	public native void transactionFailedCallback( String id, String title, String description, String price );
	public native void productRefundedCallback( String id, String title, String description, String price );
	
	// -- persist information about purchases -------------------------------------------------
    private void restoreDataIfNecessary()
    {
    	mReceivedData = null;
    	
        SharedPreferences prefs = this.activity.getPreferences(Context.MODE_PRIVATE);
        boolean initialized = prefs.getBoolean(DATA_INITIALIZED, false);
        if(true)  // (!initialized) // fix for Googles nasty API
        {
            mBillingService.restoreTransactions();
            // log
            log("Restoring Purchase-Data");
        }
        else
        {
        	log("Not restoring transaction data because it is already restored.");
        }
    }
	
    public void onRestoreTransactionsResponse()
    {
		// log
		log("onRestoreTransactionsResponse()");
		
        // Update the shared preferences so that we don't perform
        // a RestoreTransactions again.
        SharedPreferences prefs = this.activity.getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor edit = prefs.edit();
        edit.putBoolean(DATA_INITIALIZED, true);
        edit.commit();
        
        // send product bought requests to ShiVa for every product found
        log(this.getReceivedData());
        
        JSONObject dataAsJson = null;
    	try
    	{
    		dataAsJson = new JSONObject(this.getReceivedData());
    		
    		JSONArray orders = dataAsJson.getJSONArray("orders");
    		int purchaseState = 0;
    		String purchaseId = null; 
    		ProductDescriptor product = null;
    		for(int i=0; i<orders.length(); ++i)
    		{
    			purchaseState = orders.getJSONObject(i).getInt("purchaseState");
    			purchaseId = orders.getJSONObject(i).getString("productId");
    			product = Config.getInstance().getProductById(purchaseId);
    			
    			// purchased
    			if( purchaseState == 0 )
    				this.onProductBought(product.productId, product.title, product.description, product.price);
    			
    			// canceled
    			if( purchaseState == 1 ){}
    				
    			// refunded
    			if( purchaseState == 2 )
    				this.onProductRefunded(product.productId, product.title, product.description, product.price);
    		}
        }
    	catch(JSONException e){}
        
    }
	
    // -- Lifecycle (mirrors activity lifecycle) ------------------------------------
    public void init(Activity act)
    {
    	log("MA InAppBilling STORE: v1.7");
    	log("Debug log messages are:" + (Consts.DEBUG ? "on" : "off"));
    	
    	// log
    	log("init("+act+")");
    	
    	this.activity = act;
    	
    	mHandler = new Handler();
        mMassPurchaseObserver = new MassPurchaseObserver(this.activity, mHandler);
        mBillingService = new BillingService();
        mBillingService.setContext(this.activity);

        // Check if billing is supported.
        ResponseHandler.register(mMassPurchaseObserver);
        if (!mBillingService.checkBillingSupported()) {
        	log("BillingService.checkBillingSupported() failed.");
            showDialog(DIALOG_CANNOT_CONNECT_ID);
        }
        else
        {
        	restoreDataIfNecessary();
        }
    }
    
    /**
     * Called when the context activity becomes visible.
     */
    public void start()
    {
    	// log
    	log("start()");
        
        ResponseHandler.register(mMassPurchaseObserver);
    }

    /**
     * Called when the context activity is no longer visible.
     */
    public void stop()
    {
    	// log
    	log("stop()");
        
        ResponseHandler.unregister(mMassPurchaseObserver);
    }

    /**
     * Called when the context activity is being destroyed.
     */
    public void destroy()
    {
    	// log
    	log("destroy()---");
        
    	ResponseHandler.unregister(mMassPurchaseObserver);
    	mBillingService.unbind();
    	
    	
        activity.stopService(new Intent(activity, BillingService.class));
        //mService = null;
        activity = null;
        //complete = null;
    	
    	//mBillingService.stopSelf();
    }
    
    public void log( String msg )
    {
    	if(Consts.DEBUG)
    	{
	    	Log.d(LOG_TAG, "----------------------------");
	        Log.d(LOG_TAG, msg);
	        Log.d(LOG_TAG, "----------------------------");
    	}
    }
    
    // -- getter & setter
    public Context getContext()
    {
    	return this.activity;
    }
    
    // -- display Dialog stuff ---------------------------------------------------------------------
    protected void showDialog(int id)
    {
    	// log
    	log("showDialog("+id+")");
    	
    	// we need runnables because dialogs need to be created IN the UI Thread
        switch (id)
        {
	        case DIALOG_CANNOT_CONNECT_ID:
	            this.activity.runOnUiThread(new RunnableDialog(R.string.cannot_connect_title, R.string.cannot_connect_message));
	        	break;
	        case DIALOG_BILLING_NOT_SUPPORTED_ID:
	        	this.activity.runOnUiThread(new RunnableDialog(R.string.cannot_connect_title, R.string.cannot_connect_message));
	        	break;
        }
    }
    // -- display Dialog stuff end -----------------------------------------------------------------
    
}
