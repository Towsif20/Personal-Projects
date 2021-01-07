<?php
    
    include "connection.php";
    
    $image_id = $_POST['image_id'];
    
    $sql = "select * from comments where image_id = '$image_id'";
    $result = mysqli_query($link, $sql);
    
    if (mysqli_num_rows($result) == 0)
    {
        echo "error";
        exit();
    }
    
    while ($row = mysqli_fetch_array($result))
    {
        $sql = "select username from users where id = '$row[user_id]'";
        
        $user = mysqli_query($link, $sql);
        $namerow = mysqli_fetch_array($user);
        $name = $namerow['username'];
        
        echo "<p><strong style='color: indianred'>$name : </strong> $row[comment] </p>";
    }
