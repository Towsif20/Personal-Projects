var running = false;
var gameover = false;
var score = 0;
var answerIndex;
var correctAnswerIndex;
var correct = document.getElementById("correct");
var wrong = document.getElementById("wrong");
var totalTime = 60;
var timeRemainingValue = document.getElementById("timeRemainingValue");
var question = document.getElementById("question");

function generateQuestion()
{
    var a = Math.floor(Math.random() * 10) + 1;
    var b = Math.floor(Math.random() * 10) + 1;

    var q = a + "x" + b;

    question.innerHTML = q;
    correctAnswerIndex = Math.floor(Math.random() * 4) + 1;

    list = [-1, -1, -1, -1];

    var k = 0;

    while (k < 4)
    {
        var t;
        if (k == correctAnswerIndex - 1)
        {
            t = a * b;
            list[k] = t;
            k++;
            continue;
        }

        else
            t = Math.floor(Math.random() * 10 + 1) * Math.floor(Math.random() * 10 + 1);

        var flag = false;

        for (var i = 0; i < 4; i++)
        {
            if (list[i] == t)
                flag = true;
        }

        if (!flag)
        {
            list[k] = t;
            k++;
        }

    }

    for (var i = 1; i <= 4; i++)
    {
        document.getElementById("box" + i).innerHTML = list[i - 1];
    }




}

document.getElementById("start").onclick = function ()
{
    var timeRemaining = document.getElementById("timeRemaining");



    if (running)
    {
        {
            running = false;
            gameover = false;

            window.location.reload();
        }
    }

    else if (!running || gameover)
    {
        running = true;
        document.getElementById("start").innerHTML = "Reset Game";
        document.getElementById("gameover").style.display = "none";


        var time = totalTime;
        timeRemainingValue.innerHTML = time;
        timeRemaining.style.display = "inline";

        generateQuestion();


        var timer = setInterval(function ()
        {

            time--;
            timeRemainingValue.innerHTML = time;

            question = document.getElementById("question");

            if (time == 0)
            {
                clearInterval(timer);
                document.getElementById("start").innerHTML = "Start Game";
                document.getElementById("scoreValue2").innerHTML = score;
                document.getElementById("gameover").style.display = "inline";

                gameover = true;
                running = false;
                time = totalTime;
                score = 0;

                timeRemaining.style.display = "none";
                timeRemainingValue.innerHTML = time;

            }
        }, 1000);

        document.getElementById("scoreValue").innerHTML = score;



    }


}


function answerQuestion(i)
{
    document.getElementById("box" + i).onclick = function ()
    {
        if (correctAnswerIndex == i)
        {
            wrong.style.display = "none";
            correct.style.display = "inline";
            score++;
            document.getElementById("scoreValue").innerHTML = score;
            generateQuestion();

            var timer = setInterval(function ()
            {
                {
                    clearInterval(timer);
                    correct.style.display = "none";
                }
            }, 1000);
        }

        else
        {
            correct.style.display = "none";
            wrong.style.display = "inline";

            var timer = setInterval(function ()
            {
                {
                    clearInterval(timer);
                    wrong.style.display = "none";
                }
            }, 1000);
        }
    }
}

for (var i = 1; i <= 4; i++)
{
    answerQuestion(i);
}