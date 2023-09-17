<?php


if (isset($_COOKIE["user"]))
echo "Welcome " . $_COOKIE["user"] . "!<br />";
else {
    setcookie("user", "aaaa", time() - 1);
    echo "Welcome guest!<br />";
}