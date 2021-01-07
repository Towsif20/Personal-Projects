// click on start reset
//     are we playing?
//         yes
//             reload page
//         no
//             show trails left
//             change button text to reset game
//             1.crate a random fruit
//             define a random step
//             2.move fruit one step down every 30sec
//                  is fruit too low
//                      no --> repeat 2
//                      yes --> any trials left?
//                          yes --> repeat 1
//                          no --> game over
// 
// mouse over a fruit
//      slice
//          play sound
//          explode



$(function ()
{
    var playing = false;
    var score = 0;
    var trialsLeft = 3;

    function addLives()
    {
        $("#trialsLeft").html("");

        for (var i = 0; i < trialsLeft; i++)
        {
            $("#trialsLeft").append('<img src="images/heart.png" class="life">');
        }
    }

    function startAction()
    {
        chooseFruit();


        var step = Math.round(Math.random() * 5) + 6;

        action = setInterval(function ()
        {
            $("#fruit1").css('top', $("#fruit1").position().top + step);

            if ($("#fruit1").position().top > $("#fruitContainer").height())
            {
                if (trialsLeft > 1)
                {
                    trialsLeft--;
                    chooseFruit();
                    addLives();

                    step = Math.round(Math.random() * 5) + 1;
                }
                else
                {
                    playing = false;

                    $("#scoreValue2").html(score);

                    $("#start").html("Start Game");
                    $("#gameover").show();
                    $("#trialsLeft").hide();
                    $("#score").hide();
                    clearInterval(action);
                }


            }
        }, 10);
    }

    var fruits = ['apple', 'banana', 'cherries', 'grapes', 'mango', 'orange', 'peach', 'pear', 'watermelon'];

    function chooseFruit()
    {
        var index = Math.floor(Math.random() * 9);
        $("#fruit1").attr('src', 'images/' + fruits[index] + '.png');

        $("#fruit1").show();
        $("#fruit1").css(
            {
                'left': Math.round(Math.random() * 550),
                'top': -50
            }
        );


    }
    $("#start").click(function ()
    {


        if (playing)
        {
            window.location.reload();
        }

        else
        {
            playing = true;

            $("#gameover").hide();

            trialsLeft = 3;
            score = 0;
            $("#scoreValue").html(score);
            $("#score").show();
            $("#trialsLeft").show();

            addLives();

            $("#start").html("Reset Game");

            //start sending fruits

            startAction();

        }
    });

    $("#fruit1").mouseover(function ()
    {
        score++;
        $("#scoreValue").html(score);
        // document.getElementById("audio").play();
        $("#audio")[0].play();

        clearInterval(action);
        $("#fruit1").hide("explode", 500);
        // $("#fruit1").hide();

        setTimeout(startAction, 500);
        // startAction();
    });
});











