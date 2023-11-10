Action()
{
	int randNumber;
	lr_start_transaction("UC5_ReservView");

	lr_start_transaction("StartWebTours");
	/*Correlation comment - Do not change!  Original value='137628.499311462HAHQczfpQDDDDDDDtctHfpfQfz' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=http://pki.goog/repo/certs/gts1c3.der", "Referer=", ENDITEM, 
		LAST);
		
	lr_end_transaction("StartWebTours", LR_AUTO);

	lr_start_transaction("LogIn");

	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);
	web_reg_find("Text=Using the menu to the left, you can search for new flights to book",LAST);
	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=61", ENDITEM,
		"Name=login.y", "Value=10", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("LogIn",LR_AUTO);
		
	lr_start_transaction("ViewAllTicket");

	web_reg_find("Text=Itinerary",LAST);
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
		lr_end_transaction("ViewAllTicket",LR_AUTO);

		lr_end_transaction("UC5_ReservView", LR_AUTO);

	return 0;
}
