<?php
    
    session_start();
    include "connection.php";

    $user_id = $_SESSION['user_id'];
    $image_id = $_POST['image_id'];
    
    $sql = "select * from likes where image_id = '$image_id' and user_id = '$user_id'";
    
    $result = mysqli_query($link, $sql);
    $count = mysqli_num_rows($result);
    
    if ($count == 1)
    {
        $sql = "delete from likes where image_id = '$image_id' and user_id = '$user_id'";
        $result = mysqli_query($link, $sql);
        
        echo "unliked";
        exit();
    }
    
    $sql = "insert into likes (user_id, image_id) values ('$user_id', '$image_id')";
    
    $result = mysqli_query($link, $sql);
    
    if (!$result)
    {
        echo "error in query";
        exit();
    }
    
    echo "liked";