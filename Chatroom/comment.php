<?php
    
    session_start();
    
    include "connection.php";
    
    $user_id = $_SESSION['user_id'];
    $image_id = $_POST['image_id'];
    $comment = $_POST['comment'];
    
    if ($comment != "")
    {
        $sql = "insert into comments (image_id, user_id, comment) values ('$image_id', '$user_id', '$comment')";
    
        $result = mysqli_query($link, $sql);
    
        if (!$result)
        {
            echo "error";
        }
    }
    else
    {
        echo "empty";
        exit();
    }
    
    $sql = "select * from comments where image_id = '$image_id'";
    $result = mysqli_query($link, $sql);
    
    while ($row = mysqli_fetch_array($result))
    {
        $sql = "select username from users where id = '$row[user_id]'";
    
        $user = mysqli_query($link, $sql);
        $namerow = mysqli_fetch_array($user);
        $name = $namerow['username'];
        
        echo "<p><strong style='color: indianred'>$name : </strong> $row[comment] </p>";
    }