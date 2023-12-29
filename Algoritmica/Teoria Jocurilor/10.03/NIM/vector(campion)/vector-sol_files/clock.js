var currentTime;
var strServerTime;

function setDate(sCurrentTime, strSrvTime)
{
	currentTime = sCurrentTime;
	strServerTime = strSrvTime;
}

function time()
{
	var today = new Date();
	currentTime += 1000;
	today.setTime(currentTime);
	var hrs = today.getHours();
	var min = today.getMinutes();
	var alsohrs = today.getHours();
	var dayNumber = today.getDate();
	var year = today.getFullYear();
	var ampm = "";
	var zero = "0";
	var month = today.getMonth() + 1;
	//Statement that puts '0's in front of single minutes or seconds.
	if (min < 10)
	{
		min = zero + min;
	}
	//Statement that eliminates Metric Time
	if (hrs > 12)
	{
		hrs = eval(hrs - 12);
	}
	if (hrs>=0 && hrs<1)
	{
		hrs = 12
	}
	if (hrs < 10)
	{
		hrs = zero + hrs;
	}
	//P.M. Statement
	if (alsohrs>=12 && alsohrs<24)
	{
		ampm="P.M.";
	}
	//A.M. Statement
	if (alsohrs<12 && alsohrs>=0)
	{
		ampm="A.M.";
	}
	tmp = '<span>' + strServerTime + ': ' + dayNumber + '/' + month + '/' + year + ' ' + hrs + '<span id="blinker">:</span>' + min + ' ' + ampm + '<span>';
	document.getElementById("clock").innerHTML = tmp;
	clocktime=setTimeout("time()", "1000");
}

function blink()
{
	var obj = document.getElementById("blinker");
	if (obj.style.visibility == "visible")
	{
		obj.style.visibility="hidden";
	}
	else 
	{
		obj.style.visibility="visible";
	}
	eachsecond=setTimeout("blink()", "500");
}
