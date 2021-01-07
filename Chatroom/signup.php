<?php
    
    include "connection.php";
//
//check user inputs
//    define error messages
    
    $missingUserName = "<p><strong>Please provide User name</strong></p>";
    $missingEmail = "<p><strong>Please provide your email</strong></p>";
    $invalidEmail = "<p><strong>Please provide a valid email</strong></p>";
    $missingPassword = "<p><strong>Please provide a password</strong></p>";
    $missingPassword2 = "<p><strong>Please confirm your password</strong></p>";
    $invalidPassword = "<p><strong>Your password should contain at least 6 characters including at least one capital and at least one digit</strong></p>";
    $differentPassword = "<p><strong>Sorry, your passwords don't match</strong></p>";
    
    $username = null;
    $email = null;
    $password = null;
    $password2 = null;
    $errors = "";
    //    get username, email, password, password2
    //    store errors in error variable
    if (empty($_POST["username"]))
    {
        $errors .= $missingUserName;
    }
    else
    {
        $username = filter_var($_POST["username"], FILTER_SANITIZE_STRING);
    }
    
    if (empty($_POST["email"]))
    {
        $errors .= $missingEmail;
    }
    else
    {
        $email = filter_var($_POST["email"], FILTER_SANITIZE_EMAIL);
        
        if (!filter_var($email, FILTER_VALIDATE_EMAIL))
        {
            $errors .= $invalidEmail;
        }
    }
    
    if (empty($_POST["password"]))
    {
        $errors .= $missingPassword;
    }
    
    else
    {
        if (!(strlen($_POST["password"]) >= 6 and
            preg_match('/[A-Z]/', $_POST["password"]) and
            preg_match('/[0-9]/', $_POST["password"])))
        {
            $errors .= $invalidPassword;
        }
        else
        {
            $password = filter_var($_POST["password"], FILTER_SANITIZE_STRING);
        }
        
    }
    
    if (empty($_POST["password2"]))
    {
        $errors .= $missingPassword2;
    }
    
    else
    {
        $password2 = filter_var($_POST["password2"], FILTER_SANITIZE_STRING);
        
        if ($password != $password2)
        {
            $errors .= $differentPassword;
        }
    }
    
    //    if any errors, print them
    
    if ($errors != "")
    {
        $resultMessage = "<div class='alert alert-danger'>$errors</div>";
        echo $resultMessage;
        
        exit();
    }




//
//No error =>
//  Prepare variables for queries
    $username = mysqli_real_escape_string($link, $username);
    $email = mysqli_real_escape_string($link, $email);
    $password = mysqli_real_escape_string($link, $password);
    //$password = md5($password);
    $password = hash('sha256', $password);
    //output is 128 bits long = 32 characters hex
    
    $sql = "select * from users where username = '$username'";
    
    $result = mysqli_query($link, $sql);
    
    if (!$result)
    {
        echo "<div class='alert alert-danger'>Error running the query</div>";
        
        exit();
    }
    
    $results = mysqli_num_rows($result);
    
    //    if username exists, print error
    if($results)
    {
        echo "<div class='alert alert-danger'>Username already registered</div>";
        
        exit();
    }
    
    $sql = "select * from users where email = '$email'";
    
    $result = mysqli_query($link, $sql);
    
    if (!$result)
    {
        echo "<div class='alert alert-danger'>Error running the query</div>";
        echo "<div class='alert alert-danger'>". mysqli_error($link)."</div>";
        
        exit();
    }
    
    $results = mysqli_num_rows($result);
    
    //        if email exists, print error
    
    if($results)
    {
        echo "<div class='alert alert-danger'>Email already registered</div>";
        
        exit();
    }



//            create a unique activation code
    
   
    
    $sql = "insert into users (username, email, password) values ('$username', '$email', '$password')";
    
    $result = mysqli_query($link, $sql);
    if (!$result)
    {
        echo "<div class='alert alert-danger'>Error inserting the data</div>";
        echo "<div class='alert alert-danger'>". mysqli_error($link)."</div>";
        
        exit();
    }
    
    echo "<div class='alert alert-success'>Signed up successfully!</div>";
    
//
//

?>