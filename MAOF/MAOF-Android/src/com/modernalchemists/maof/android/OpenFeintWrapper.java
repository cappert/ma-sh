package com.modernalchemists.maof.android;

import java.util.LinkedList;

import com.openfeint.api.OpenFeint;
import com.openfeint.api.OpenFeintDelegate;
import com.openfeint.api.OpenFeintSettings;
import com.openfeint.api.resource.Achievement;
import com.openfeint.api.resource.Leaderboard;
import com.openfeint.api.resource.Score;
import com.openfeint.api.resource.Score.SubmitToCB;
import com.openfeint.api.ui.Dashboard;


import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.widget.Toast;


public class OpenFeintWrapper {

	// Logging
	public static final String LOG_TAG = "MAOF-JAVA";
	
	// singleton instance storage
    private static OpenFeintWrapper instance = null;
    private Context context;
    private LinkedList<AchievementInfo> achievements = new LinkedList<AchievementInfo>();
    //private Activity activity;
    
    private OpenFeintWrapper() {}

    public static OpenFeintWrapper getInstance()
    {
        if (instance == null)
            instance = new OpenFeintWrapper();
        
        return instance;
    }
    
    //Needs to be called first! (e.g. in onCreate of main class) 
    public void initWrapper(Activity a, Context c)
    {
    	log( "initWrapper" );
    	//OpenFeintWrapper.getInstance().activity = a;
    	OpenFeintWrapper.getInstance().context = c;
    	achievements.clear(); 
    }
    
    //-------------------------------------------------------------------------------
    //MAOF Shiva callbacks:
    //-------------------------------------------------------------------------------
    public static void initOF(String productKey, String secret, String name, String clientId)
	{
		//TODO: this currently must be called from the onCreate method! Workaround?
    	// log
		OpenFeintWrapper.getInstance().log("init("+productKey+"/"+secret+"/"+name+")");
		
		OpenFeintSettings settings = new OpenFeintSettings(name, productKey, secret, clientId); 
		OpenFeint.initialize( OpenFeintWrapper.getInstance().context, settings, new OpenFeintDelegate() {} );
  	}
    
    public static void shutdownOF()
    {
    	OpenFeintWrapper.getInstance().log("shutdownOF");
    	//Dashboard.close();
    	//OpenFeint.logoutUser();
    }
    
    public static void launchDashboard()
    {
    	OpenFeintWrapper.getInstance().log("launchDashboard");
    	Dashboard.open();
    }
    
    public static void launchDashboardWithHighscorePage(String id)
    {
    	OpenFeintWrapper.getInstance().log("launchDashboardWithHighscorePage");
    	Dashboard.openLeaderboard(id);
    }
	
    public static void submitHighscore(float score, String id)
    {
    	OpenFeintWrapper.getInstance().log("submitHighscore:" + score);
    	
    	long scoreValue = (long)score;
    	// Second parameter is null to indicate that custom display text is not used.
    	Score s = new Score(scoreValue, null);
    	Leaderboard l = new Leaderboard(id);
    	SubmitToCB cb = new SubmitToCB() {
			
			@Override
			public void onSuccess(boolean newHighScore) {
			}
			
			@Override public void onFailure(String exceptionMessage) {
				OpenFeintWrapper.getInstance().log(exceptionMessage);
				Toast.makeText(OpenFeintWrapper.getInstance().context,
   	               "Error (" + exceptionMessage + ") posting score.",
   	               Toast.LENGTH_SHORT).show();
			}
		};
    	s.submitTo(l, cb);
    }
    
    public static void unlockAchievement(String id, float progress, boolean showNotification, boolean deferred)
    {
    	OpenFeintWrapper.getInstance().log("unlockAchievement:"+ id + "/" + progress + "/" + showNotification + "/" + deferred);
    	
    	AchievementInfo ai = new AchievementInfo(id, progress, showNotification, deferred);
    	
    	Achievement.UpdateProgressionCB cb = new Achievement.UpdateProgressionCB() {
			
			@Override
			public void onSuccess(boolean newUnlock) {
			}

			@Override public void onFailure(String exceptionMessage) {
				OpenFeintWrapper.getInstance().log(exceptionMessage);
				Toast.makeText(OpenFeintWrapper.getInstance().context,
   	               "Error (" + exceptionMessage + ") unlocking achievement.",
   	               Toast.LENGTH_SHORT).show();
			}
    	};
		
    	if(deferred)
    	{
    		OpenFeintWrapper.getInstance().achievements.add(ai);
    	}
    	else
    	{
    		new Achievement(id).updateProgression(progress, cb);
    	}
    }  
    
    public static void flushUnlockedAchievements() 
    {
    	OpenFeintWrapper.getInstance().log("flushUnlockedAchievements");
    	
		for (AchievementInfo ai : OpenFeintWrapper.getInstance().achievements)
		{
			unlockAchievement(ai.id, ai.progress, ai.showNotification, false);
		}
		OpenFeintWrapper.getInstance().achievements.clear();
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

}
