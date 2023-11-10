Action()
{
	lr_start_transaction("UC5_ReservView");

	
	lr_start_transaction("StartWebTours");

	startWebTours();
		
	lr_end_transaction("StartWebTours", LR_AUTO);

	
	
	
	lr_start_transaction("LogIn");

	logIn(lr_eval_string("{userSession}"),lr_eval_string("{login}"),lr_eval_string("{password}"));

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


	
	
	lr_start_transaction("LogOut");

	lr_think_time(5);

	logOut();

	lr_end_transaction("LogOut",LR_AUTO);
	

	
	lr_end_transaction("UC5_ReservView", LR_AUTO);

	return 0;
}
