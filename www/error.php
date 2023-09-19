<?php


// Access an invalid memory location (This can lead to a segmentation fault)
// $invalid_memory_location = null;
// $invalid_memory_location->property = 'This will cause a segfault';

echo "This will not be reached if a segmentation fault occurs.\n";
?>