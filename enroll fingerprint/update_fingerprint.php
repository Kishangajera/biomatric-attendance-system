<?php
// update_fingerprint.php

header('Content-Type: application/json');

// Set timezone if required
// date_default_timezone_set('Asia/Kolkata');

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

// Only handle POST requests
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Get sr_no from POST request and sanitize it
    $sr_no = filter_input(INPUT_POST, 'sr_no', FILTER_SANITIZE_NUMBER_INT);

    // Ensure sr_no is provided
    if (empty($sr_no)) {
        $response['status'] = 'error';
        $response['message'] = 'Missing required parameter: sr_no.';
        echo json_encode($response);
        exit();
    }

    // Prepare an SQL statement to update the fingerprint status
    $sql = "UPDATE users SET fingerprint = 'yes' WHERE sr_no = ?";
    $stmt = $conn->prepare($sql);
    if (!$stmt) {
        $response['status'] = 'error';
        $response['message'] = 'Failed to prepare the SQL statement.';
        echo json_encode($response);
        exit();
    }

    $stmt->bind_param("i", $sr_no);
    $stmt->execute();

    if ($stmt->affected_rows > 0) {
        // Fingerprint updated successfully
        $response['status'] = 'success';
        $response['message'] = 'Fingerprint updated successfully.';
    } else {
        // No record found with the given sr_no
        $response['status'] = 'error';
        $response['message'] = "No record found with sr_no: $sr_no";
    }

    $stmt->close();
} else {
    // Invalid request method
    $response['status'] = 'error';
    $response['message'] = 'Invalid request method. Only POST is allowed.';
}

// Close the database connection
$conn->close();

// Output the response in JSON format
echo json_encode($response);
