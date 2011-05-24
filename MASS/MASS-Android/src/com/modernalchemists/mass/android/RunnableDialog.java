package com.modernalchemists.mass.android;

import java.util.Locale;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import com.modernalchemists.inappbilling.R;

public class RunnableDialog implements Runnable
{

	private int titleId;
	private int messageId;
	
	public RunnableDialog(int titleId, int messageId)
	{
		this.titleId = titleId;
		this.messageId = messageId;
	}	
	
	@Override
	public void run()
	{
		createAndShowDialog(this.titleId, this.messageId);
	}
	
    private Dialog createAndShowDialog(int titleId, int messageId)
    {
    	Context context = Store.getInstance().getContext();
        String helpUrl = replaceLanguageAndRegion(context.getString(R.string.help_url));
        if (Consts.DEBUG) {
            Log.i("MASS-STORE", helpUrl);
        }
        final Uri helpUri = Uri.parse(helpUrl);
        
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(titleId)
            .setIcon(android.R.drawable.stat_sys_warning)
            .setMessage(messageId)
            .setCancelable(false)
            .setPositiveButton(android.R.string.ok, null)
            .setNegativeButton(R.string.learn_more, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    Intent intent = new Intent(Intent.ACTION_VIEW, helpUri);
                    Store.getInstance().getContext().startActivity(intent);
                }
            });
        return builder.show();
    }

    /**
     * Replaces the language and/or country of the device into the given string.
     * The pattern "%lang%" will be replaced by the device's language code and
     * the pattern "%region%" will be replaced with the device's country code.
     *
     * @param str the string to replace the language/country within
     * @return a string containing the local language and region codes
     */
    private String replaceLanguageAndRegion(String str) {
        // Substitute language and or region if present in string
        if (str.contains("%lang%") || str.contains("%region%")) {
            Locale locale = Locale.getDefault();
            str = str.replace("%lang%", locale.getLanguage().toLowerCase());
            str = str.replace("%region%", locale.getCountry().toLowerCase());
        }
        return str;
    }

}
