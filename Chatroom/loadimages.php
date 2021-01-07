<?php
    session_start();
    
    include "connection.php";
    
    $sql = "select * from images order by id desc ";
    
    $result = mysqli_query($link, $sql);
    
    while ($row = mysqli_fetch_array($result)) {
        echo "<div id='img_div'>";
        
        $sql = "select username from users where id = '$row[owner_id]'";
        
        $namerow = mysqli_query($link, $sql);
        $name = mysqli_fetch_array($namerow);
        
        echo "<div style='font-weight: bold; font-size: 25px; color: black'>$name[username]</div>";
        if ($row['image'] != "")
            echo "<a href='images/$row[image]'><img src='images/".$row['image']."' ></a>";
        echo "<div style='clear:both;'>";
        echo "<p style='font-size: 20px'>".$row['image_text']."</p>";
        
        $sql = "select * from likes where image_id = '$row[id]' and user_id = '$_SESSION[user_id]'";
        
        $likes = mysqli_query($link, $sql);
        $count = mysqli_num_rows($likes);
        
        $value = "Like";
        
        if ($count > 0)
            $value = "Unlike";
        
        $sql = "select * from likes where image_id = '$row[id]'";
        $likes = mysqli_query($link, $sql);
        
        $count = mysqli_num_rows($likes);
        
        echo "<p style='margin: 10px'>
                    <button class='buttons btn btn-dark' id='button_$row[id]' style='cursor:pointer;'>$value</button>
                    <button class='btn btn-light'>$count</button>
                    
                
              </p>";
        
        echo "<div id='commenterror'></div>";
    
        $sql = "select * from comments where image_id = '$row[id]'";
        $comments = mysqli_query($link, $sql);
    
        $count = mysqli_num_rows($comments);
        
        echo "<div style='margin: 10px'>
                    <textarea type='text' class='commentArea' placeholder='Write a comment' style='width: 60%; height: 50px'></textarea><br>
                    <button class='comments btn btn-info btn-sm' id='comment_$row[id]'>Comment</button>
                    <button class='commentsCount btn btn-info btn-sm'>$count</button>
                    <button class='showComments btn btn-dark btn-sm' id='showComments_$row[id]' style='cursor:pointer;
'>Show All Comments</button>
              </div>";
        
//        while ($commentsrow = mysqli_fetch_array($comments))
//        {
//            $sql = "select username from users where id = '$commentsrow[user_id]'";
//
//            $user = mysqli_query($link, $sql);
//            $namerow = mysqli_fetch_array($user);
//            $name = $namerow['username'];
//
//            echo "<div id='allcomments_$row[id]' >
//                    <p><strong style='color: indianred'>$name : </strong> $commentsrow[comment] </p>
//              </div>";
//        }
        
        echo "<div id='allComments_$row[id]'></div>";
        
        
        echo "</div></div>";
        echo "<hr>";
    }
    
    
    
