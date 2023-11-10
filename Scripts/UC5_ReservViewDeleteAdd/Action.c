Action()
{
	int randNumber;
	lr_start_transaction("UC5_ReservViewDeleteAdd");

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

	web_reg_save_param("Flight",
	                   "lb=name=\"flightID\" value=\"",
	                   "rb=\"",
	                   "ord=all",
	                   LAST);
	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
		lr_end_transaction("ViewAllTicket",LR_AUTO);

	lr_start_transaction("DeleteTicket");
	
	lr_save_int(atoi(lr_eval_string("{Flight_count}")),"countFlight");

	if(atoi(lr_eval_string("{countFlight}"))>0&&atoi(lr_eval_string("{countFlight}"))<=3)
	{	
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_1}\"","fail=found",LAST);
		
		web_submit_form("itinerary.pl",
			"Snapshot=t5.inf",
			ITEMDATA,
			"Name=1", "Value=on", ENDITEM, 
			"Name=removeFlights.x", "Value=60", ENDITEM,
			"Name=removeFlights.y", "Value=11", ENDITEM,
			LAST);
		
	}
	else if(atoi(lr_eval_string("{countFlight}"))<=5)
	{
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_1}\"","fail=found",LAST);
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_2}\"","fail=found",LAST);

		web_submit_form("itinerary.pl",
			"Snapshot=t6.inf",
			ITEMDATA,
			"Name=1", "Value=on", ENDITEM, 
			"Name=2", "Value=on", ENDITEM, 
			"Name=removeFlights.x", "Value=60", ENDITEM,
			"Name=removeFlights.y", "Value=11", ENDITEM,
			LAST);
		
	}
	else if(atoi(lr_eval_string("{countFlight}"))>=6)
	{
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_1}\"","fail=found",LAST);
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_2}\"","fail=found",LAST);
		web_reg_find("Text=name=\"flightID\" value=\"{Flight_3}\"","fail=found",LAST);

		web_submit_form("itinerary.pl",
			"Snapshot=t7.inf",
			ITEMDATA,
			"Name=1", "Value=on", ENDITEM, 
			"Name=2", "Value=on", ENDITEM, 
			"Name=3", "Value=on", ENDITEM,
			"Name=removeFlights.x", "Value=60", ENDITEM,
			"Name=removeFlights.y", "Value=11", ENDITEM,
			LAST);

	}

	lr_end_transaction("DeleteTicket", LR_AUTO);

	lr_start_transaction("ToFlightsPage");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(5);

	web_reg_save_param("departcity",
	                   "lb=\">",
	                   "rb=</option>",
	                   "ord=all",
	                   "search=body",
	                   LAST);
	
	web_reg_save_param("seatPref",
	                   "lb=name=\"seatPref\" value=\"",
	                   "rb=\"",
	                   "ord=all",
	                   LAST);
	web_reg_save_param("seatType",
	                   "lb=name=\"seatType\" value=\"",
	                   "rb=\"",
	                   "ord=all",
	                   LAST);
	
	web_reg_find("Text=Find Flight",LAST);
	web_url("Search Flights Button",
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=http://pki.goog/repo/certs/gts1c3.der", "Referer=", ENDITEM, 
		"Url=http://pki.goog/repo/certs/gtsr1.der", "Referer=", ENDITEM, 
		LAST);

	lr_end_transaction("ToFlightsPage",LR_AUTO);

	lr_start_transaction("ReservTicket");

	lr_save_string(lr_paramarr_random("departcity"),"depart_City");
	lr_save_string(lr_paramarr_random("departcity"),"arrive_City");
	lr_save_string(lr_paramarr_random("seatPref"),"seat_Pref");
	lr_save_string(lr_paramarr_random("seatType"),"seat_Type");
	
	//проверка, что города отправления и прибытия разные
	while(strcmp(lr_eval_string("{depart_City}"),lr_eval_string("{arrive_City}"))==0)
	{		
		lr_save_string(lr_paramarr_random("departcity"),"arrive_City");
	}

	
	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);

	web_reg_save_param("outboundflighting",
	                   "lb=name=\"outboundFlight\" value=\"",
	                   "rb=\"",
	                   "ord=all",
	                   //"search=body",
	                   LAST);	

	
	randNumber = rand()%4 + 1;  
	lr_output_message("Random Number is %d", randNumber); 	
	lr_save_int(randNumber,"numPassengerRand");

	
	web_reg_find("Text=Find Flight",LAST);
	web_reg_find("Text=Flight departing from <B>{depart_City}</B> to <B>{arrive_City}</B> on <B>{departDate}</B>",LAST);
	
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart_City}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrive_City}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM, 
		"Name=seatPref", "Value={seat_Pref}", ENDITEM, 
		"Name=seatType", "Value={seat_Type}", ENDITEM, 
		"Name=findFlights.x", "Value=77", ENDITEM, 
		"Name=findFlights.y", "Value=6", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);



	lr_save_string(lr_paramarr_random("outboundflighting"),"outboundFlight");
	
	
	//проверка открытия нужной страницы
	web_reg_find("Text=Payment Details",LAST);
	
	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t10.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seat_Type}", ENDITEM,
		"Name=seatPref", "Value={seat_Pref}", ENDITEM,
		"Name=reserveFlights.x", "Value=50", ENDITEM,
		"Name=reserveFlights.y", "Value=11", ENDITEM,
		LAST);

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);


	//получаем формулировку данных о рейсе
	web_reg_save_param("fligting",
		"LB={departDate} : ",
		"RB=\.",
		LAST);
	
	
	//проверка открытия нужной страницы
	web_reg_find("Text=Thank you for booking through Web Tours",LAST);
	//проверка корректного использования карты клиента
	web_reg_find("Text=Total Charged to Credit Card # {creditCard}",LAST);
	//проверка верно указанных городов
	web_reg_find("Text=leaves {depart_City}  for {arrive_City}",LAST);

	if(randNumber==1)
	{
		//web_reg_find("Text=A {seat_Type} Class ticket from {depart_City} to {arrive_City}.</u></b>",LAST);
		web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={streetUser}", ENDITEM, 
		"Name=address2", "Value={cityUser}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expCreditCard}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM, 
		"Name=seatType", "Value={seat_Type}", ENDITEM, 
		"Name=seatPref", "Value={seat_Pref}", ENDITEM, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=64", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);
	}
	else if(randNumber==2)
	{
		web_reg_find("Text=<b><u>{numPassengerRand} {seat_Type} Class tickets from {depart_City} to {arrive_City}.</u></b>",LAST);
		web_submit_data("reservations.pl_4",
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={streetUser}", ENDITEM, 
		"Name=address2", "Value={cityUser}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expCreditCard}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM, 
		"Name=seatType", "Value={seat_Type}", ENDITEM, 
		"Name=seatPref", "Value={seat_Pref}", ENDITEM, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=64", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);	
	}
	else if(randNumber==3)
	{
		web_reg_find("Text=<b><u>{numPassengerRand} {seat_Type} Class tickets from {depart_City} to {arrive_City}.</u></b>",LAST);
		web_submit_data("reservations.pl_5",
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={streetUser}", ENDITEM, 
		"Name=address2", "Value={cityUser}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=pass3", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expCreditCard}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM, 
		"Name=seatType", "Value={seat_Type}", ENDITEM, 
		"Name=seatPref", "Value={seat_Pref}", ENDITEM, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=64", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);	
	}
		else if(randNumber==4)
	{
		web_reg_find("Text=<b><u>{numPassengerRand} {seat_Type} Class tickets from {depart_City} to {arrive_City}.</u></b>",LAST);
		web_submit_data("reservations.pl_5",
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={streetUser}", ENDITEM, 
		"Name=address2", "Value={cityUser}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=pass3", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=pass4", "Value={randFirstName} {randLastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expCreditCard}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={numPassengerRand}", ENDITEM, 
		"Name=seatType", "Value={seat_Type}", ENDITEM, 
		"Name=seatPref", "Value={seat_Pref}", ENDITEM, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=64", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);	
	}

	lr_end_transaction("ReservTicket",LR_AUTO);
	lr_end_transaction("UC5_ReservViewDeleteAdd", LR_AUTO);

	return 0;
}
