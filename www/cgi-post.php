<?php

session_start();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['note'])) {
        $note = $_POST['note'];

        // Initialize an empty array for notes if not already done
        if (!isset($_SESSION['notes'])) {
            $_SESSION['notes'] = array();
        }

        // Add the new note to the user's list of notes
        if (strlen($note))
            $_SESSION['notes'][] = $note;

    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Notes App</title>
</head>
<body>
    <h1>Notes App</h1>
    <form  method="POST">
        <textarea name="note" rows="5" cols="40"></textarea><br>
        <input type="submit" value="Save Note">
    </form>
    <hr>
    <h2>Your Notes:</h2>
    <p>
        <?php

            if (isset($_SESSION['notes']) && count($_SESSION['notes']) > 0) {
                foreach ($_SESSION['notes'] as $note) {
                    echo "- " . htmlspecialchars($note) . "<br>";
                }
            } else {
                echo "No notes found.";
            }
        ?>

    </p>

</body>
</html>