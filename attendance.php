<?php
// attendance.php

header('Content-Type: application/json');

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
    $timestamp = filter_input(INPUT_POST, 'timestamp', FILTER_SANITIZE_STRING);

    // Validate timestamp format (YYYY-MM-DD HH:MM:SS)
    $dateTime = DateTime::createFromFormat('Y-m-d H:i:s', $timestamp);
    if (!$dateTime || $dateTime->format('Y-m-d H:i:s') !== $timestamp) {
        $response['status'] = 'error';
        $response['message'] = 'Invalid timestamp format.';
        echo json_encode($response);
        exit();
    }

    // Check if all required data is present
    if (!empty($fingerID) && !empty($name) && !empty($timestamp)) {
        // Check if entry for today already exists
        $date_only = $dateTime->format('Y-m-d');
        $stmt = $conn->prepare("SELECT * FROM attendance_records WHERE fingerID=? AND DATE(timein)=?");
        $stmt->bind_param("is", $fingerID, $date_only);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows == 0) {
            // First entry of the day: record 'timein'
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
            // Entry exists: update 'timeout'
            $stmt = $conn->prepare("UPDATE attendance_records SET timeout=? WHERE fingerID=? AND DATE(timein)=?");
            $stmt->bind_param("sis", $timestamp, $fingerID, $date_only);
            if ($stmt->execute()) {
                $response['status'] = 'success';
                $response['message'] = 'Time-out recorded successfully.';
            } else {
                $response['status'] = 'error';
                $response['message'] = 'Database update failed.';
            }
            $stmt->close();
        }
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
