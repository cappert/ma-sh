package com.modernalchemists.maof.android;

public class AchievementInfo {
	
	public String id;
	float progress;
	boolean showNotification;
	boolean deferred;
	
	public AchievementInfo(String id, float progress, boolean showNotification, boolean deferred) {
		this.id = id;
		this.progress = progress;
		this.showNotification = showNotification;
		this.deferred = deferred;
	}
}
