<?php
// attendance.php

header('Content-Type: application/json');

// Set timezone to IST (or your desired timezone)
date_default_timezone_set('Asia/Kolkata');

// Database configuration
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "attendance_db";

// Response array
$response = array();

// Create database connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check database connection
if ($conn->connect_error) {
    $response['status'] = 'error';
    $response['message'] = 'Database connection failed.';
    echo json_encode($response);
    exit();
}

// Only process POST requests
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Retrieve and sanitize POST data
    $fingerID = filter_input(INPUT_POST, 'fingerID', FILTER_SANITIZE_NUMBER_INT);
    $name = filter_input(INPUT_POST, 'name', FILTER_SANITIZE_STRING);

    // Generate current server time in IST
    $timestamp = date("Y-m-d H:i:s");

    // Check if required data is present
    if (!empty($fingerID) && !empty($name)) {
        // Directly insert a new record for time-in
        $stmt = $conn->prepare("INSERT INTO attendance_records (fingerID, name, timein) VALUES (?, ?, ?)");
        $stmt->bind_param("iss", $fingerID, $name, $timestamp);
        
        if ($stmt->execute()) {
            $response['status'] = 'success';
            $response['message'] = 'Time-in recorded successfully.';
        } else {
            $response['status'] = 'error';
            $response['message'] = 'Database insertion failed.';
        }
        $stmt->close();
    } else {
        // Missing data response
        $response['status'] = 'error';
        $response['message'] = 'Missing required parameters.';
    }
} else {
    // Invalid request method response
    $response['status'] = 'error';
    $response['message'] = 'Invalid request method.';
}

// Close the database connection
$conn->close();

// Output the response in JSON format
echo json_encode($response);
?>
