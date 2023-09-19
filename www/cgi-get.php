<?php


if (isset($_COOKIE["back"]))
    echo "<style> body {background-color:" .$_COOKIE["back"] . "} </style>";

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    if (isset($_POST["bg"]))
        setcookie("back", $_POST["bg"]);
}   
?>

<form  method="POST">
    <input type="color" name="bg">
    <input type="submit"  value="pick color">
</form>