<?php


if (isset($_COOKIE["back"]))
    echo "<style> body {background-color:" .$_COOKIE["back"] . "} </style>";

if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    if (isset($_GET["bg"]))
        setcookie("back", $_GET["bg"]);
}   
?>

<form  method="GET">
    <input type="color" name="bg">
    <input type="submit"  value="pick color">
</form>