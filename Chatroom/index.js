$(function ()
{

    $.ajax(
        {
            url: "loadimages.php",
            type: 'post',
            success: function (data)
            {
                if (data)
                {
                    $("#images").html(data);
                    like();
                    comment();
                    showComments();
                }
            }
        }
    );

    function like()
    {
        $(".buttons").click(function (event)
        {
            event.preventDefault();

            var image_id = $(this).attr("id").split("_")[1];
            var likes = parseInt($("#button_" + image_id).siblings().html());
            var button = $(this);

            $.ajax(
                {
                    url: "like.php",
                    type: 'post',
                    data : {
                      image_id: image_id
                    },
                    success: function (data)
                    {
                        if (data == "liked")
                        {
                            $("#button_" + image_id).html("Unlike");
                            $("#button_" + image_id).siblings().html(likes + 1);
                        }
                        else if (data == "unliked")
                        {
                            $("#button_" + image_id).html("Like");
                            $("#button_" + image_id).siblings().html(likes - 1);
                        }
                        else
                            $("#likeerror").html("error liking the photo");

                    }
                }
            );
        });
    }

    function comment()
    {
        $(".comments").click(function (event)
        {
            event.preventDefault();

            var image_id = $(this).attr("id").split("_")[1];
            var comment = $("#comment_" + image_id).siblings(".commentArea").val();
            var count = parseInt($("#comment_" + image_id).siblings(".commentsCount").html());

            $.ajax(
                {
                    url: "comment.php",
                    type: 'post',
                    data : {
                        image_id: image_id,
                        comment : comment
                    },
                    success: function (data)
                    {
                        if (data == "empty")
                        {
                            $("#commenterror").html("Please write something in the comment box");
                        }

                        else if(data == "error")
                        {
                            $("#commenterror").html(data);
                        }

                        else
                        {
                            $("#comment_" + image_id).siblings(".commentsCount").html(count + 1);
                            $("#allComments_" + image_id).html(data);
                            $("#showComments_" + image_id).html("Hide Comments");
                            $("#comment_" + image_id).siblings(".commentArea").text('');
                        }

                    }
                }
            );
        });
    }

    function showComments()
    {
        $(".showComments").click(function ()
        {
            var image_id = $(this).attr("id").split("_")[1];
            var text = $(this).html();

            if (text == "Show All Comments")
            {
                $.ajax(
                    {
                        url: "showComments.php",
                        type: 'post',
                        data : {
                            image_id: image_id,
                        },
                        success: function (data)
                        {
                            if(data == "error")
                            {
                                $("#commenterror").html("no comments yet");
                            }

                            else
                            {
                                $("#allComments_" + image_id).html(data);
                                $("#showComments_" + image_id).html("Hide Comments");
                            }

                        }
                    }
                );
            }

            else
            {
                $("#allComments_" + image_id).html("");
                $("#showComments_" + image_id).html("Show All Comments");
            }


        });
    }
})