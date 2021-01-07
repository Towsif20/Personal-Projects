$(function ()
{
    $("#login").click(function ()
    {
        var email = $("#loginEmail").val();
        var password = $("#loginPassword").val();
        var checked = "false";
        if($("#check").prop('checked') == true)
        {
            checked = "true";
        }

        $.ajax(
            {
                url : "login.php",
                type : "post",
                data :
                    {
                        email : email,
                        password : password,
                        check : checked
                    },
                success : function (data)
                {
                    if (data == "success")
                    {
                        window.location = "index.php";
                    }
                    else
                    {
                        $("#loginMessage").html(data)
                    }

                },
                error: function ()
                {
                    $("#loginMessage").html("<div class='alert alert-danger'>An error occurred</div>")
                }

            }
        );
    });

    $("#signUp").click(function ()
    {
        var email = $("#email").val();
        var password = $("#password").val();
        var password2 = $("#password2").val();
        var username = $("#username").val();

        $.ajax(
            {
                url : "signup.php",
                type : "post",
                data :
                    {
                        email : email,
                        password : password,
                        password2 : password2,
                        username : username
                    },
                success : function (data)
                {

                    $("#signUpMessage").html(data)


                },
                error: function ()
                {
                    $("#signUpMessage").html("<div class='alert alert-danger'>An error occurred</div>")
                }

            }
        );
    });
})