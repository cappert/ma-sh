package com.modernalchemists.maad.android;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

public class AdMobWrapper {
	// Logging
	public static final String LOG_TAG = "MAAD-JAVA";
	public static final int MSG_ADMOB 	= 400 ;
	public static final int MSG_ADMOB_LAYOUT 	= 401 ;
	
	// singleton instance storage
    private static AdMobWrapper instance = null;
    private Context context;
    private Activity activity;
    public AdView adView = null;
    //private boolean isInitialized = false;
    private Handler oUIHandler = null;
    private RelativeLayout oViewGroup = null;
    private static String PUID = "";
    
    private AdMobWrapper() {}

    public static AdMobWrapper getInstance()
    {
        if (instance == null)
            instance = new AdMobWrapper();
        
        return instance;
    }
    
    
    //Needs to be called first! (e.g. in onCreate of main class) 
    public void initWrapper(Activity a, Context c, Handler h)
    {
    	log( "initWrapper" );
    	
    	this.activity = a;
    	this.context = c;
    	this.oUIHandler = h;
    }
    
    //Needs to be called first! (e.g. in onCreate of main class) 
    public void startWrapper(RelativeLayout oViewGroup)
    {
    	this.oViewGroup = oViewGroup;
    	
    	AdMobWrapper.getInstance().log("registerPublisher");
    	
    	AdMobWrapper.getInstance().adView = new AdView(AdMobWrapper.getInstance().activity, AdSize.BANNER, PUID);
    	
    	RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
    	lp.addRule( RelativeLayout.ALIGN_PARENT_BOTTOM );
    	AdMobWrapper.getInstance().oViewGroup.addView(AdMobWrapper.getInstance().adView, lp);


    	// request ad
    	showAds();
    }
    
    public void hideAds()
    {
    	AdMobWrapper.getInstance().adView.setVisibility(View.INVISIBLE);
    }
    
    public void showAds()
    {
		AdMobWrapper.getInstance().adView.setVisibility(View.VISIBLE);
		
		AdRequest request = new AdRequest();
		request.addTestDevice(AdRequest.TEST_EMULATOR);
		request.addTestDevice("E83D20734F72FB3108F104ABC0FFC738");    // My T-Mobile G1 test phone
		
		AdMobWrapper.getInstance().adView.loadAd(request); //requestFreshAd();
		AdMobWrapper.getInstance().adView.bringToFront();    	
    }
    
    
    //-------------------------------------------------------------------------------
    //MAOF Shiva callbacks:
    //-------------------------------------------------------------------------------
    public static void registerPublisher(String publisherId)
	{
    	AdMobWrapper.getInstance().PUID = publisherId;

    	Message msg     = new Message ( ) ;

		msg.what        = MSG_ADMOB_LAYOUT ;

    	AdMobWrapper.getInstance().oUIHandler.sendMessage( msg ) ;  
  	}
    
    public static void setVisible(boolean bVisible)
	{
    	Message msg     = new Message ( ) ;

    	if( bVisible )
    	{
    		msg.what        = MSG_ADMOB ;
    		msg.obj         = null ;
    		msg.arg1 = View.VISIBLE;
    	}
    	else
    	{
    		msg.what        = MSG_ADMOB ;
    		msg.obj         = null ;
    		msg.arg1 = View.INVISIBLE;
    	}

    	AdMobWrapper.getInstance().oUIHandler.sendMessage( msg ) ;    	   	
  	}    
    
    public void log( String msg )
    {
	    	Log.d(LOG_TAG, "----------------------------");
	        Log.d(LOG_TAG, msg);
	        Log.d(LOG_TAG, "----------------------------");
    }	

}
