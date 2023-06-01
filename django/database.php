<?php
// Check if the keys exist in the $_POST array
if (!isset($_POST['temperature'], $_POST['humidity'], $_POST['pressure'], $_POST['altitude'])) {
    echo "Missing key: temperature, humidity, pressure, altitude";
    exit;
}

// Retrieve the data sent from the ESP8266
$temperature = $_POST['temperature'];
$humidity = $_POST['humidity'];
$pressure = $_POST['pressure'];
$altitude = $_POST['altitude'];

// Connect to the MySQL database
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "esp32_mc_db";
$table = "esp32_table_test";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check the connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Prepare the SQL statement to insert the data into the table
$sql = "INSERT INTO $table (temperature, humidity, pressure, altitude) VALUES (?, ?, ?, ?)";

// Prepare the statement
$stmt = $conn->prepare($sql);

// Bind the parameters
$stmt->bind_param("dddd", $temperature, $humidity, $pressure, $altitude);

// Execute the statement
if ($stmt->execute()) {
    echo "Data inserted successfully";
} else {
    echo "Error inserting data: " . $stmt->error;
}

// Close the statement
$stmt->close();

// Close the database connection
$conn->close();
?>

