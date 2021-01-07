<?php
    //Start session
    session_start();
    
    //Connect to the database
    include "connection.php";


//Check user input
    //Define error messages
    
    $missingEmail = "<p><strong>Please Enter Your Email Address</strong></p>";
    $missingPassword = "<p><strong>Please Enter Your Password</strong></p>";
//Get email and password
    
    $email = null;
    $password = null;
    $errors = "";

//Store errors in errors variable
    
    if (empty($_POST["email"]))
    {
        $errors .= $missingEmail;
    }
    else
    {
        $email = filter_var($_POST["email"], FILTER_SANITIZE_EMAIL);
    }
    
    if (empty($_POST["password"]))
    {
        $errors .= $missingPassword;
    }
    else
    {
        $password = filter_var($_POST["password"], FILTER_SANITIZE_STRING);
    }
    
    
    ////there are any errors
    
    //print error message
    
    if ($errors != "")
    {
        echo "<div class='alert alert-danger'>$errors</div>";
        
        exit();
    }
    //else: No errors
    //Prepare variables for the query
    
    $email = mysqli_real_escape_string($link, $email);
    $password = mysqli_real_escape_string($link, $password);
    $password = hash('sha256', $password);
    $checked = $_POST['check'];
    
    //Run query: Check combinaton of email & password exists
    
    $sql = "select * from users where email = '$email' and password = '$password'";
    
    $result = mysqli_query($link, $sql);
    
    $count = mysqli_num_rows($result);
    
    if ($count == 1)
    {
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
        $_SESSION["user_id"] = $row['id'];
        $_SESSION["username"] = $row['username'];
        $_SESSION["email"] = $row['email'];
        
        if ($checked == "false")
        {
            echo "success";
        }
        else
        {
        
        }
        
    }
    
    else
    {
        echo "<div class='alert alert-danger'>Email and Password not matched</div>";
    }