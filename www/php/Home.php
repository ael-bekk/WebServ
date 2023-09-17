<?php

   setcookie("user", "aaaa", time() + (8600));
    if (isset($_COOKIE["user"]))
        echo "Welcome " . $_COOKIE["user"] . "!<br />";
    else
        echo "Welcome guest!<br />";
    while(1);