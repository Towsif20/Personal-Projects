$(function ()
{
    var mode = false;   //  app mode
    var timeCounter = 0;    //sentiseconds
    var lapCounter = 0;
    var action;
    var lapNumber = 0;
    var timeMin, timeSec, timeCentiSec;
    var lapMin, lapSec, lapCentiSec;

    timeMin = timeSec = timeCentiSec = 0;
    lapMin = lapSec = lapCentiSec = 0;

    hideShowButtons("#startButton", "#lapButton");


    $("#startButton").click(function ()
    {
        mode = true;

        hideShowButtons("#stopButton", "#lapButton");

        startAction();
    });

    $("#stopButton").click(function ()
    {
        mode = false;
        clearInterval(action);
        hideShowButtons("#resumeButton", "#resetButton");
    });

    $("#resetButton").click(function ()
    {
        window.location.reload();
    });

    $("#resumeButton").click(function ()
    {
        mode = true;

        hideShowButtons("#stopButton", "#lapButton");
        startAction();
    });

    $("#lapButton").click(function ()
    {
        if (!mode)
            return;

        clearInterval(action);

        lapNumber++;

        addLap();

        lapCounter = 0;

        lapMin = lapSec = lapCentiSec = 0;

        startAction();
    });

    // functons

    function hideShowButtons(x, y)
    {
        $(".control").hide();
        $(x).show();
        $(y).show();
    }

    function startAction()
    {
        action = setInterval(function ()
        {
            timeCounter++;
            lapCounter++;

            updateTime();
        }, 10);
    }

    function updateTime()
    {

        if (timeCounter > 99)
        {
            timeCounter = timeCounter % 100;
            timeSec++;

            if (timeSec < 10)
                timeSec = "0" + timeSec;

            $("#timesec").text(timeSec);
        }

        if (lapCounter > 99)
        {
            lapCounter = lapCounter % 100;
            lapSec++;

            if (lapSec < 10)
                lapSec = "0" + lapSec;

            $("#lapsec").text(lapSec);
        }

        if (timeSec > 59)
        {
            timeSec %= 60;
            timeMin++;

            if (timeMin < 10)
                timeMin = "0" + timeMin;

            $("#timemin").text(timeMin);
        }

        if (lapSec > 59)
        {
            lapSec %= 60;
            lapMin++;

            if (lapMin < 10)
                lapMin = "0" + lapMin;

            $("#lapmin").text(lapMin);
        }

        timeCentiSec = timeCounter;
        lapCentiSec = lapCounter;

        if (timeCentiSec < 10)
            timeCentiSec = "0" + timeCentiSec;

        if (lapCentiSec < 10)
            lapCentiSec = "0" + lapCentiSec;

        $("#timecentisec").text(timeCentiSec);
        $("#lapcentisec").text(lapCentiSec);



    }



    function addLap()
    {
        $("#lapsHistory").append('Lap ' + lapNumber + '<span class="right"><span>' + lapMin + ':<span>' + lapSec + ':<span>' + lapCentiSec + '</span></span></span></span><hr>');
    }

});