<?php
    
    session_start();
    if (!isset($_SESSION['user_id']))
    {
        header("location:landing.php");
    }

?>

<?php /** @noinspection SqlResolve */
    
    include "connection.php";
    
    // Initialize message variable
    $msg = "";
    
    // If upload button is clicked ...
    if (isset($_POST['upload'])) {
        // Get image name
        // Get text
        
        $image = $_FILES['image']['name'];
        $image_text = mysqli_real_escape_string($link, $_POST['image_text']);
        $target = "images/".basename($image);

        $sql = "INSERT INTO images (image, image_text, owner_id) VALUES ('$image', '$image_text', '$_SESSION[user_id]')";
        // execute query
        mysqli_query($link, $sql);

        if (move_uploaded_file($_FILES['image']['tmp_name'], $target))
        {
            $msg = "Image uploaded successfully";
        }
        else
        {
            $msg = "Failed to upload image";
        }
        
        $sql = "delete from images where image_text = '' and image = ''";
        mysqli_query($link, $sql);
    
        
        // image file directory
        
    }

?>



<!doctype html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">


    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css"
          integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">

    <!-- Bootstrap CSS -->
    <!--        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css" integrity="sha384-HSMxcRTRxnN+Bdg0JdbxYKrThecOKuH5zCYotlSAcp1+c8xmyTe9GYg1l9a69psu" crossorigin="anonymous">-->

    <title>Homepage</title>

    <link rel="stylesheet" href="styling.css">

    <link href="https://fonts.googleapis.com/css2?family=Arvo&display=swap" rel="stylesheet">

    <style>
        .container
        {
            margin: 20px auto;
        }

        .footer .container
        {
            margin-top: 0px;
        }
        

        textarea
        {
            width: 100%;
            max-width: 100%;
            font-size: 16px;
            line-height: 1.5em;
            border-left-width: 20px;
            color: #ca3dd9;
            background-color: #fbefff;
            padding: 10px;
        }

        .noteheader
        {
            border: 1px solid grey;
            border-radius: 10px;
            margin-bottom: 10px;
            cursor: pointer;
            padding: 0 10px;
            background: linear-gradient(white, #eceae7);
        }

        .text, .timetext
        {

            overflow: hidden;
            white-space: nowrap;
            text-overflow: ellipsis;
        }

        .text
        {
            font-size: 20px;
        }

        #content{
            width: 50%;
            /*margin: 20px auto;*/
        }
        form{
            width: 100%;
            margin: 20px auto;
        }
        form div{
            margin-top: 5px;
        }
        #img_div{
            /*width: 80%;*/
            padding: 10px 25px;
            margin: 15px auto;
            
        }
        #img_div:after{
            content: "";
            display: block;
            clear: both;
        }
        img{
            float: left;
            margin: 5px;
            width: 40%;
        }
            /*height: 140px;*/
        }
        
        .buttons
        {
            margin: 20px;
        }

    </style>
</head>
<body>

<!--Navigation bar-->

<div class="container-fluid">
    <nav class="navbar navbar-expand-lg navbar-dark bg-light navbar-custom fixed-top">

        <a class="navbar-brand" href="#">Chatroom</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav mr-auto">
<!--                <li class="nav-item">-->
<!--                    <a class="nav-link" href="profile.php">Profile</a>-->
<!--                </li>-->
<!--                <li class="nav-item">-->
<!--                    <a class="nav-link" href="#">Help</a>-->
<!--                </li>-->
<!---->
<!--                <li class="nav-item">-->
<!--                    <a class="nav-link" href="#">Contact Us</a>-->
<!--                </li>-->

            </ul>

            <ul class="navbar-nav nav navbar-right">
                <li><a class="nav-link" href='#'><strong><?php echo
                            $_SESSION["username"]?></strong></a></li>
                <li><a class="nav-link" href="landing.php?logout=1">Log Out</a></li>
            </ul>
        </div>

    </nav>
</div>

<!--container-->

<div class="container" id="container">
    <div class="row" style="align-content: center">
        <!--        Alert message        -->
        <h1 style="text-align: center">Share your thoughts and photos with us!</h1>
        <div class="col"></div>
        <div id="content" class="col-10">
           
            <form method="POST" action="index.php" enctype="multipart/form-data">
                <input type="hidden" name="size" value="1000000">
                <div>
<!--                    <label for="imageinput" class="btn btn-success">Upload a photo</label>-->
                    <input type="file" class="btn btn-dark" id="imageinput" name="image" value="Upload a photo"
                           style="width: 50%">
                </div>
                <div>
            <textarea id="text" cols="40" rows="4" name="image_text" placeholder="Write a message"></textarea>
                </div>
                <div>
                    <button type="submit" id="upload" class="btn btn-info" name="upload">POST</button>
                </div>
            </form>

            <div id="uploadMessage">

            </div>

            <div id="likeerror">

            </div>

            <div id="images">

            </div>
        </div>
        <div class="col"></div>
    </div>
</div>



<!--footer-->

<div class="footer">
    <div class="container">
        <p>DevelopmentIsland.com Copyright &copy; <?php $today = date("Y"); echo $today?>.</p>
    </div>
</div>

<!-- Optional JavaScript -->
<!-- jQuery first, then Popper.js, then Bootstrap JS -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
<!-- Include all compiled plugins (below), or include individual files as needed -->
<script src="js/bootstrap.min.js"></script>

<script src="index.js"></script>
</body>
</html>













