<?php
    
    session_start();
    
    if (isset($_SESSION['user_id']))
    {
        header("location:index.php");
    }
    
    include "connection.php";
    
    include "logout.php";
?>


<html>
    <head>
        <meta charset="utf-8">
        
        <title>
            Welcome!
        </title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css"
              integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">
        <link rel="stylesheet" href="style.css">
    </head>

    <body>

    <div class="container">
        <div class="login-wrap">
            <div class="login-html">
                <input id="tab-1" type="radio" name="tab" class="sign-in" checked><label for="tab-1" class="tab">Log
                    In</label>
                <input id="tab-2" type="radio" name="tab" class="sign-up"><label for="tab-2" class="tab">Sign Up</label>
                <div class="login-form">
                    <div class="sign-in-htm">
                        <div id="loginMessage" style="color: #1d2124"></div>
                        <div class="group">
                            <label for="loginEmail" class="label">Email</label>
                            <input id="loginEmail" name="loginEmail" type="email" class="input">
                        </div>
                        <div class="group">
                            <label for="loginPassword" class="label">Password</label>
                            <input id="loginPassword" name="loginPassword" type="password" class="input" data-type="password">
                        </div>
                        <div class="group sr-only">
                            <input id="check" type="checkbox" class="check">
                            <label for="check"><span class="icon"></span> Keep me Signed in</label>
                        </div>
                        <div class="group">
                            <input type="submit" class="button" id="login" name="login" value="Log In">
                        </div>
                        <div class="hr"></div>
                        <div class="foot-lnk">
                            <a href="#forgot">Forgot Password?</a>
                        </div>
                    </div>
                    
                    <div class="sign-up-htm">

                        <div id="signUpMessage"></div>
                        <div class="group">
                            <label for="email" class="label">Email Address</label>
                            <input id="email" name="email" type="email" class="input">
                        </div>
                        <div class="group">
                            <label for="username" class="label">Username</label>
                            <input id="username" name="username" type="text" class="input">
                        </div>
                        <div class="group">
                            <label for="password" class="label">Password</label>
                            <input id="password" name="password" type="password" class="input" data-type="password">
                        </div>
                        <div class="group">
                            <label for="password2" class="label">Confirm Password</label>
                            <input id="password2" name="password2" type="password" class="input" data-type="password">
                        </div>
                        
                        <div class="group">
                            <input type="submit" id="signUp" name="signUp" class="button" value="Sign Up">
                        </div>
                        <div class="hr"></div>
                        <div class="foot-lnk">
                            <label for="tab-1">Already Member?</label>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js'></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script src="landing.js"></script>
    </body>
</html>